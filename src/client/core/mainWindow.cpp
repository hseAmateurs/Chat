#include<QDialog>
#include<QListWidget>
#include<QVBoxLayout>
#include<QtDebug>
#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "../settings/config.h"
#include "../widgets/folderWidget.h"
#include "../caching/cacher.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    renderStackLayout(0);
    ui->nameLabel->setText("Имя: " + Cacher::instance().getUserName());
    QFont font;
    font.setPointSize(12);
    ui->nameLabel->setFont(font);
}

void MainWindow::renderStackLayout(int curDirId, QWidget *parentPage) {
    qDebug() << currentFolder;
    if (currentFolder.isEmpty() || curDirId != getPos())
        currentFolder.append({curDirId, parentPage});

    QVector<QPair<int, QString>> folders;
    Cacher::instance().getSubFolders(curDirId, folders);

    QWidget *page = new QWidget();
    auto *gridLayoutRoot = new QGridLayout(page);
    gridLayoutRoot->setSpacing(cfg::foldersView::space);
    for (int row = 0; row < cfg::foldersView::rowCount; ++row)
        gridLayoutRoot->setRowStretch(row, 1);
    for (int column = 0; column < cfg::foldersView::columnCount; ++column)
        gridLayoutRoot->setColumnStretch(column, 1);

    int column = 0;
    int row = -1;
    for (const auto &folder: folders) {
        column %= cfg::foldersView::columnCount;
        if (!column) row++;

        auto *folderWidget = new FolderWidget(folder);
        gridLayoutRoot->addWidget(folderWidget, row, column);
        QObject::connect(folderWidget, &FolderWidget::clicked, [this, folderWidget, page]() {
            qDebug() << "Next folder" << folderWidget->id() << folderWidget->name();
            renderStackLayout(folderWidget->id(), page);
        });
        QObject::connect(ui->backButton, &QPushButton::clicked, folderWidget, &FolderWidget::deselect);
        QObject::connect(ui->deleteButton, &QPushButton::clicked, folderWidget, [this, folderWidget]() {
            if (!folderWidget->isSelected()) return;

            Cacher::instance().deleteFolder(folderWidget->id());
            renderStackLayout(getPos());
        });

        column++;
    }

    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_backButton_clicked() {
    if (!getPos()) return;
    ui->stackedWidget->setCurrentWidget(currentFolder.last().second);
    currentFolder.pop_back();
}

void MainWindow::on_onlineButton_clicked() {
    if (!getPos()) {
        QMessageBox::warning(nullptr, "Ошибка!", "Вы не можете добавить пользователей в корень чата. Создайте папку");
        return;
    }

    QVector<QPair<int, QString>> users;

    auto *dialogBox = new QDialog(this);
    auto *layout = new QVBoxLayout(dialogBox);
    auto *usersList = new QListWidget(dialogBox);

    Cacher::instance().getOnlineUsers(users);

    for (const auto &user: users) {
        auto *item = new QListWidgetItem(user.second, usersList);
        item->setData(Qt::UserRole, user.first);
    }
    usersList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    auto *addButton = new QPushButton("Добавить");

    QVector<int> selectedUsersIds;
    QObject::connect(addButton, &QPushButton::clicked, [&selectedUsersIds, usersList, dialogBox]() {
        QList<QListWidgetItem *> selectedItems = usersList->selectedItems();
        for (const auto &item: selectedItems)
            selectedUsersIds.append(item->data(Qt::UserRole).toInt());

        dialogBox->accept();
    });

    layout->addWidget(usersList);
    layout->addWidget(addButton);
    dialogBox->setLayout(layout);

    dialogBox->exec();

    if (!selectedUsersIds.isEmpty())
        Cacher::instance().addUsersToFolder(selectedUsersIds, getPos());
}

void MainWindow::on_addFolderButton_clicked() {
    bool ok;
    QString folderName = QInputDialog::getText(this, "Подтверждение действия", "Введите название папки",
                                               QLineEdit::Normal, "root", &ok);
    if (ok && !folderName.isEmpty()) {
        if (Cacher::instance().createFolder(getPos(), folderName))
            renderStackLayout(getPos());
        else
            QMessageBox::critical(nullptr, "Ошибка!", "Невозможно создать папку");
    }
}
