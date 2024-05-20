#include "core/mainWindow.h"

#include <QApplication>

#include "utils/cacher.h"
#include "core/loginSystem.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // �������� �� SQLite
    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    // ������������� ������� ����
    MainWindow w;
    QObject::connect(&w, &MainWindow::sayHello, []() {
        qDebug() << "Say Hello!";
    });

    //w.update();

    // ������ ���� �����������
    auto *loginWindow = new LoginSystem();
    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
    loginWindow->show();

    return a.exec();
}
