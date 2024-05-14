#include "mainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    LoginSystem *loginWindow = new LoginSystem(); // create a dynamic object of the login window
    QObject::connect(loginWindow, &LoginSystem::openMainWindow, this, &MainWindow::open);
    // 1 - an object, which sends the signal
    // 2 - a sending signal function
    // 3 - an object, which gets the signal and executes the slot function
    // 4 - the slot function
    loginWindow->show(); // show the login window from the main window object
    chat = new ChatWindow();
    chat->setWindowFlags(
            Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint); // flags for delition buttons in the heading
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
