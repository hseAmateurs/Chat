#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginSystem.h"
#include "chatWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool getFolders(int userId, int rootId, QVector<QPair<int, QString>> &subFolders) { return true; };
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ChatWindow *chat;

    int user_id = 0;
    int current_folder_id = 0;

public slots:

    void open() { show(); };

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
};

#endif // MAINWINDOW_H
