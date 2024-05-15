#include<QDialog>
#include "mainWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    chat = new ChatWindow();
    chat->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    QObject::connect(chat, &ChatWindow::openMainWindow, this, &MainWindow::open);
}

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

    QDialog dialogBox;
    getFolders(user_id, current_folder_id, users);

//    for (const std::string& user : users) {
//      msgBox.addItem(user.c_str());
//    }

    dialogBox.exec();
}


