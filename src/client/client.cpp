#include "core/mainWindow.h"

#include <QApplication>

#include "utils/cacher.h"
#include "core/loginSystem.h"

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
