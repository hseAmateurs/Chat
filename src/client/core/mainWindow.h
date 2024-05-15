#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    bool getUsers(int userId, int rootId, QVector<QPair<int, QString>> &subFolders);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int currentStackIndex;
    QVector<int> currentFolderId;

public slots:

    void open() { show(); };

signals:
    void deleteSelectedItem();

private slots:

    void on_backButton_clicked();

    void on_onlineButton_clicked();

    void on_addFolderButton_clicked();

    void on_deleteButton_clicked();

    void renderStackLayout(int curDirId);
};

#endif // MAINWINDOW_H
