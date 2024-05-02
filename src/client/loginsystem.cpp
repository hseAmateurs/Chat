#include "loginsystem.h"
#include "ui_loginsystem.h"

LoginSystem::LoginSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginSystem)
{
    ui->setupUi(this);
    setStyleSheet("background-color: #7DD4F0");
}

LoginSystem::~LoginSystem()
{
    delete ui;
}

void LoginSystem::on_pushButton_clicked()
{
    this->close(); // close the login window
    emit OpenMainWindow(); // send a signal from the login window to the main window
}

