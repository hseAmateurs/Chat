#include "core/mainWindow.h"

#include <QApplication>

#include "utils/cacher.h"
#include "core/loginSystem.h"
#include "core/chatWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // �������� �� SQLite
    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    // ������������� ������� ����
    MainWindow w;

    // ������ ���� �����������
    auto *loginWindow = new LoginSystem();
    QObject::connect(loginWindow, &LoginSystem::openMainWindow, &w, &MainWindow::open);
    loginWindow->show();

    return a.exec();
}

/* TODO:
 * ������� ����� network, ������� �����:
 * 1) ��������� ��������� ��
 * 2) ���������� ������� �� ������ �� Cacher
 * 3) ������������� ������ offline/online
 * 4) ������������ � online ������ �����������
 */
