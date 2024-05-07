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
    //std::cout<<login<<" "<<pass;
    // This message box is used when the person has entered a new login and password
    QMessageBox *ms = new QMessageBox();
    ms->setStyleSheet("QMessageBox{background-color: white;}"
                       "QPushButton{background-color: #E5E5E5; color: black;}");
    ms->setWindowTitle("Создание аккаунта");
    ms->setIcon(QMessageBox::Question);
    ms->setText("Вы уверены, что хотите создать новый аккаунт?");
    QAbstractButton* no_button = ms->addButton(tr("Нет"), QMessageBox::NoRole);
    QAbstractButton* yes_button = ms->addButton(tr("Да"), QMessageBox::YesRole);

    QMessageBox *message = new QMessageBox();
    message->setStyleSheet("QMessageBox{background-color: white;}"
                       "QPushButton{background-color: #E5E5E5; color: black;}");
    message->setWindowTitle("Ошибка входа");
    message->setIcon(QMessageBox::Warning);

    if (!data.IsEmptyLogin() && !data.IsEmptyPass())
    {
        if (data.IsCorrectPass())
        {
            if (data.IsCorrectData(login, pass))
            {
                // if an user is new
                /*
                ms->exec();
                if (ms->clickedButton() == yes_button)
                {
                    this->close(); // close the login window
                    emit OpenMainWindow(); // send a signal from the login window to the main window
                }
                */
                // if the user is not new

                this->close(); // close the login window
                emit OpenMainWindow(); // send a signal from the login window to the main window


            }
            else
            {
                message->setText("Неверный логин или пароль");
                message->exec();
            }
        }
        else
        {
            message->setText("Пароль должен быть не менее\n"
                             "5 символов, содержать заглавные,\n"
                             "строчные латинские буквы и цифры");
            message->exec();
        }
    }
    else if (data.IsEmptyLogin() || data.IsEmptyPass())
    {
        message->setText("Необходимо заполнить все поля");
        message->exec();
    }
}

