#include "core/mainWindow.h"

#include <QApplication>

#include "utils/cacher.h"
#include "core/loginSystem.h"
#include "core/chatWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

//    ChatWindow chat;
//    chat.show();

    MainWindow w;

    w.open();

//    auto *loginWindow = new LoginSystem();
//    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
//    loginWindow->show();

    return a.exec();
}
