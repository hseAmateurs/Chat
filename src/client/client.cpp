#include "mainwindow.h"

#include <QApplication>

#include "database/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Database db(QCoreApplication::applicationDirPath());
    db.connect();

    return a.exec();
}
