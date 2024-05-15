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
        : QMainWindow(parent), ui(new Ui::MainWindow), currentStackIndex(0) {
    ui->setupUi(this);

    renderStackLayout(0);
}

void MainWindow::renderStackLayout(int curDirId) {
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
        QObject::connect(folderWidget, &FolderWidget::clicked, [this, folderWidget]() {
            currentStackIndex++;
            qDebug() << "Next folder" << folderWidget->id() << folderWidget->name();
            renderStackLayout(folderWidget->id());
        });
        QObject::connect(ui->backButton, &QPushButton::clicked, folderWidget, &FolderWidget::deselect);

        column++;
    }

    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);
}

bool MainWindow::getUsers(int userId, int rootId, QVector<QPair<int, QString>> &subFolders) {
    subFolders.append(QPair(67, QString("Malcolm")));
    subFolders.append(QPair(4, QString("Widen")));
    subFolders.append(QPair(138, QString("Ched")));
    return true; }

MainWindow::~MainWindow() {
    delete ui;
    delete ui->stackedWidget;
}

void MainWindow::on_backButton_clicked() {
    qDebug() << "Clicked" << currentStackIndex;
    if (!currentStackIndex) return;
    ui->stackedWidget->setCurrentIndex(--currentStackIndex);
}

void MainWindow::on_onlineButton_clicked() {
    QVector<QPair<int, QString>> users;

    QDialog *dialogBox = new QDialog(this);
    QVBoxLayout* layout = new QVBoxLayout(dialogBox);
    QListWidget *usersList = new QListWidget(dialogBox);
    getUsers(user_id, current_folder_id, users);
    for (const auto& user : users){
        QListWidgetItem *item = new QListWidgetItem(user.second, usersList);
        item->setData(Qt::UserRole, user.first);
    }
    usersList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QPushButton* addButton = new QPushButton("Добавить");
    connect(addButton, &QPushButton::clicked, [this, usersList, dialogBox](){
        QList<QListWidgetItem*> selectedItems = usersList->selectedItems();
        QVector<int> SelectedUsersIds;
        for (const auto& item : selectedItems){
            SelectedUsersIds.append(item->data(Qt::UserRole).toInt());
        }

        dialogBox->accept();
        qDebug() << SelectedUsersIds;
    });

    layout->addWidget(usersList);
    layout->addWidget(addButton);
    dialogBox->setLayout(layout);

    dialogBox->exec();
}
