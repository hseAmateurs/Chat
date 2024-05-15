#include "core/mainWindow.h"

#include <QApplication>

#include "caching/cacher.h"
#include "core/loginSystem.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    MainWindow w;

    w.show();

//    auto *loginWindow = new LoginSystem();
//    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
//    loginWindow->show();

    return a.exec();
}
