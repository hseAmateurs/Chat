#include<QDialog>
#include<QListWidget>
#include<QVBoxLayout>
#include<QtDebug>
#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "../widgets/folderWidget.h"
#include "../widgets/userWidget.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QObject::connect(ui->chatButton, &QPushButton::clicked, [this]() {
        if (getPos() == rootId) {
            QMessageBox::warning(nullptr, "Предупреждение!",
                                 "Вы не можете написать в корень чата. Перейдите в любую папку");
        }
    });

    QObject::connect(&server, &Server::messageReceived, this, &MainWindow::update);
    QObject::connect(this, &MainWindow::sayHello, &server, &Server::sendMessage);
    server.connectToServer("127.0.0.1", 1234);
}

void MainWindow::openChat(int chatId, const QString &folderName) {
    chatWindow = new ChatWindow(chatId, folderName, this);
    QObject::connect(chatWindow, &ChatWindow::sentMsg, this, &MainWindow::sayHello);
    QObject::connect(chatWindow, &ChatWindow::finished, this, [this]() { isChatMode = false; });
    chatWindow->setModal(true);
    chatWindow->open();
    isChatMode = true;
}

void MainWindow::renderStackLayout(int curDirId, QWidget *parentPage) {
    qDebug() << currentFolder;
    if (currentFolder.isEmpty() || curDirId != getPos())
        currentFolder.append(curDirId);

    QVector<QPair<int, QString>> folders;
    if (curDirId != rootId && !Cacher::instance().isChainExist(curDirId)) {
        QMessageBox::warning(nullptr, "Внимание!",
                             "Вы не имеета доступа к данной папке. Опускаю вас в корень");
        currentFolder.clear();
        renderStackLayout(rootId);
    }
    bool res = Cacher::instance().getSubFolders(curDirId, folders);
    qDebug() << res;

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
            folderWidget->deselect();

            qDebug() << "Delete " << folderWidget->id();
            Cacher::instance().deleteFolder(folderWidget->id());
            renderStackLayout(getPos());
            emit sayHello();
        });
        QObject::connect(ui->chatButton, &QPushButton::clicked, folderWidget, [this, folderWidget]() {
            if (getPos() == folderWidget->id() && !isChatMode)
                openChat(folderWidget->id(), folderWidget->name());
        });

        column++;
    }

    QVector<QPair<int, QString>> users;
    Cacher::instance().getUserOwners(curDirId, users);
    for (const auto &user: users) {
        column %= cfg::foldersView::columnCount;
        if (!column) row++;

        auto *userWidget = new UserWidget(user);
        gridLayoutRoot->addWidget(userWidget, row, column);
        QObject::connect(userWidget, &FolderWidget::clicked,
                         [this, userWidget]() { openChat(userWidget->id(), userWidget->name()); });
        QObject::connect(ui->backButton, &QPushButton::clicked, userWidget, &FolderWidget::deselect);
        QObject::connect(ui->deleteButton, &QPushButton::clicked, userWidget, [this, userWidget]() {
            if (!userWidget->isSelected()) return;
            userWidget->deselect();

            Cacher::instance().deleteUser(userWidget->id(), getPos());
            renderStackLayout(getPos());
            emit sayHello();
        });

        column++;
    }

    ui->stackedWidget->addWidget(page);
    ui->stackedWidget->setCurrentWidget(page);
}

MainWindow::~MainWindow() {
    Cacher::instance().setOnlineStatus(false);
    delete ui;
}

void MainWindow::on_backButton_clicked() {
    if (getPos() == rootId) return;
    QWidget *currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget) {
        ui->stackedWidget->removeWidget(currentWidget);
        delete currentWidget;
    }
    currentFolder.pop_back();
    update();
}

void MainWindow::on_onlineButton_clicked() {
    if (currentFolder.size() <= 2) {
        QMessageBox::warning(nullptr, "Предупреждение!",
                             "Вы не можете добавить пользователей в первый слой или корень. Создайте подпапку");
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

    if (!selectedUsersIds.isEmpty()) {
        Cacher::instance().addUsersToFolder(selectedUsersIds, getPos());
        renderStackLayout(getPos());
        emit sayHello();
    }
}

void MainWindow::on_addFolderButton_clicked() {
    bool ok;
    QString folderName = QInputDialog::getText(this, "Подтверждение действия", "Введите название папки",
                                               QLineEdit::Normal, "root", &ok);
    if (ok && !folderName.isEmpty()) {
        if (Cacher::instance().createFolder(getPos(), folderName)) {
            renderStackLayout(getPos());
            emit sayHello();
        }
        else
            QMessageBox::critical(nullptr, "Ошибка!", "Невозможно создать папку");
    }
}

void MainWindow::open() {
    rootId = cfg::ROOT_OFFSET + Cacher::instance().getUserId();

    renderStackLayout(rootId);
    ui->nameLabel->setText("Имя: " + Cacher::instance().getUserName());
    QFont font;
    font.setPointSize(12);
    ui->nameLabel->setFont(font);

    show();
    emit sayHello();
}

void MainWindow::update() {
    if(!isVisible()) {
        qDebug() << "Not visible";
        return;
    }
    renderStackLayout(getPos());
    if (isChatMode)
        chatWindow->updateChat(true);
}
