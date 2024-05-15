#include "core/mainWindow.h"

#include <QApplication>

#include "caching/cacher.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    MainWindow w;

//    auto *loginWindow = new LoginSystem();
//    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
//    loginWindow->show();
    w.show();

    return a.exec();
}
