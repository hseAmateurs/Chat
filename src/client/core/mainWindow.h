#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void update();

private:
    Ui::MainWindow *ui;
    ChatWindow *chatWindow;

    bool isChatMode;

    QVector<int> currentFolder;

    // Возвращает уровень текущего слоя в StackLayout
    int getPos() { return currentFolder.last(); }

    void openChat(int chatId, const QString &folderName);

    int rootId;

signals:
    void sayHello();

public slots:

    void open();

private slots:

    void on_backButton_clicked();

    void on_onlineButton_clicked();

    void on_addFolderButton_clicked();

    void renderStackLayout(int curDirId, QWidget *parentPage = nullptr);
};

#endif // MAINWINDOW_H
