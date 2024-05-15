#include<QDialog>
#include<QListWidget>
#include<QVBoxLayout>
#include<QtDebug>
#include "mainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    chat = new ChatWindow();
    chat->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    QObject::connect(chat, &ChatWindow::openMainWindow, this, &MainWindow::open);
}

bool MainWindow::getUsers(int userId, int rootId, QVector<QPair<int, QString>> &subFolders) {
    subFolders.append(QPair(67, QString("Malcolm")));
    subFolders.append(QPair(4, QString("Widen")));
    subFolders.append(QPair(138, QString("Ched")));
    return true; }

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    this->close();
    chat->show();
}




void MainWindow::on_pushButton_3_clicked()
{
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


