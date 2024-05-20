#include "loginSystem.h"
#include "ui_loginsystem.h"

#include <QMessageBox>

#include "../utils/cacher.h"

LoginSystem::LoginSystem(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::LoginSystem) {
    ui->setupUi(this);
    QObject::connect(this, &LoginSystem::openMainWindow, this, &LoginSystem::close);
}

LoginSystem::~LoginSystem() {
    delete ui;
}

void LoginSystem::on_pushButton_clicked() {
    login = ui->login->text();
    pass = ui->pass->text();
    auth();
}

bool LoginSystem::isCorrectPass() const {
    int countCapital = 0, countLowercase = 0, countDigit = 0;
    if (pass.length() >= 5) {
        for (int i = 0; i < pass.length(); ++i) {
            if (pass[i] >= 65 && pass[i] <= 90)
                countCapital += 1;

            else if (pass[i] >= 97 && pass[i] <= 122)
                countLowercase += 1;

            else if (pass[i] >= 48 && pass[i] <= 57)
                countDigit += 1;

            if (countCapital >= 1 && countLowercase >= 1 && countDigit >= 1)
                return true;

        }
        return false;
    }
    return false;
}

bool LoginSystem::isValidData() const {
    return true;
}

void LoginSystem::auth() {
    auto *ms = new QMessageBox();
    ms->setStyleSheet("QMessageBox{background-color: white;}"
                      "QPushButton{background-color: #E5E5E5; color: black;}");

    ms->setWindowTitle("Создание аккаунта");
    ms->setIcon(QMessageBox::Question);
    ms->setText("Вы уверены, что хотите создать новый аккаунт?");

    ms->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    ms->setDefaultButton(QMessageBox::No);

    auto *message = new QMessageBox();
    message->setStyleSheet("QMessageBox{background-color: white;}"
                           "QPushButton{background-color: #E5E5E5; color: black;}");
    message->setWindowTitle("Ошибка входа");
    message->setIcon(QMessageBox::Warning);

    if (login.isEmpty() || pass.isEmpty()) {
        message->setText("Необходимо заполнить все поля");
        message->exec();
        return;
    }

    if (!isCorrectPass()) {
        message->setText("Пароль должен быть не менее\n"
                         "5 символов, содержать заглавные,\n"
                         "строчные латинские буквы и цифры");
        message->exec();
        return;
    }

    switch (Cacher::instance().isUserValid(login, pass)) {
        case cfg::OK:
            Cacher::instance().setOnlineStatus(true);
            emit openMainWindow();
            break;
        case cfg::BAD_PASS:
            message->setText("Неверный пароль");
            message->exec();
            break;
        case cfg::NOT_FOUND:
            if(ms->exec() == QMessageBox::Yes) {
                if(Cacher::instance().registerUser(login, pass)) emit openMainWindow();
                else {
                    message->setText("Регистрация временно недоступна");
                    message->exec();
                }
            }
            break;
        case cfg::UNKNOWN:
            message->setText("Неизвестная ошибка");
            message->exec();
            break;
    }

    delete ms;
    delete message;
}
