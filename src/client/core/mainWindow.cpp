#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    LoginSystem *loginWindow = new LoginSystem();
    QObject::connect(loginWindow, &LoginSystem::openMainWindow, this, &MainWindow::open);
    loginWindow->show();
    chat = new ChatWindow();
    chat->setWindowFlags(
            Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    QObject::connect(chat, &ChatWindow::openMainWindow, this, &MainWindow::open);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::open() {
    this->show();
}


void MainWindow::on_pushButton_clicked() {
    this->close();
    chat->show();
}
