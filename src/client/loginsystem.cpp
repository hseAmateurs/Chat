#include "loginsystem.h"
#include "ui_loginsystem.h"
#include <QMessageBox>

LoginSystem::LoginSystem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginSystem)
{
    ui->setupUi(this);
}

LoginSystem::~LoginSystem()
{
    delete ui;
}

void LoginSystem::on_pushButton_clicked()
{
    QString log = ui->login->text();
    std::string login = log.toUtf8().constData();
    QString pas = ui->pass->text();
    std::string pass = pas.toUtf8().constData();
    Authorisation data(login, pass);
    if (!data.IsEmptyLogin() && !data.IsEmptyPass())
    {
        if (data.IsCorrectData(login, pass))
        {
            this->close(); // close the login window
            emit OpenMainWindow(); // send a signal from the login window to the main window
        }
        else
        {
            QMessageBox *message = new QMessageBox();
            message->setStyleSheet("QMessageBox{background-color: white;}"
                               "QPushButton{background-color: #E5E5E5; color: black;}");
            message->setWindowTitle("Ошибка входа");
            message->setText("Неверный логин или пароль");
            message->setIcon(QMessageBox::Warning);
            message->exec();
        }
    }
    else if (data.IsEmptyLogin() || data.IsEmptyPass())
    {
        QMessageBox *message = new QMessageBox();
        message->setStyleSheet("QMessageBox{background-color: white;}"
                           "QPushButton{background-color: #E5E5E5; color: black;}");
        message->setWindowTitle("Ошибка входа");
        message->setText("Необходимо заполнить все поля");
        message->setIcon(QMessageBox::Warning);
        message->exec();
    }
}

