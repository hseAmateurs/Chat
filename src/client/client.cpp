#include "mainwindow.h"

#include <QApplication>

#include "caching/cacher.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Cacher::instance().loadConfig(QCoreApplication::applicationDirPath());

    qDebug() << Cacher::instance().isUserValid("admin", "pass1");
    qDebug() << Cacher::instance().isUserValid("admin", "pass");
    qDebug() << Cacher::instance().isUserValid("admin1", "pass1");

    return a.exec();
}
