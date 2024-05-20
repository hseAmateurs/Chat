#include "core/mainWindow.h"

#include <QApplication>

#include "utils/cacher.h"
#include "core/loginSystem.h"
#include "core/chatWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Загрузка БД SQLite
    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    // Инициализация основго окна
    MainWindow w;

    // Запуск окна авторизации
    auto *loginWindow = new LoginSystem();
    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
    loginWindow->show();

    return a.exec();
}

/* TODO:
 * Создать класс network, который будет:
 * 1) Обновлять локальную БД
 * 2) Отправлять запросы на сервер от Cacher
 * 3) Устанавливать статус offline/online
 * 4) Обмениваться в online режиме сообщениями
 */
