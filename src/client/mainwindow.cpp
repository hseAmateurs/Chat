#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoginSystem *LoginWindow = new LoginSystem(); // create a dynamic object of the login window
    QObject::connect(LoginWindow, &LoginSystem::OpenMainWindow, this, &MainWindow::Open);
    // 1 - an object, which sends the signal
    // 2 - a sending signal function
    // 3 - an object, which gets the signal and executes the slot function
    // 4 - the slot function
    LoginWindow->show(); // show the login window from the main window object
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Open()
{
    this->show();
}

