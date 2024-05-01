#include "mainwindow.h"
#include "loginsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginSystem window;
    window.show();
    //MainWindow w;
    //w.show();
    return a.exec();
}
