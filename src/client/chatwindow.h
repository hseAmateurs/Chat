#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

namespace Ui {
class chatwindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::chatwindow *ui;
    QVBoxLayout *lay;
    QScrollArea *scroll;

signals:
    void openMainWindow(); // create a signal, which opens the main window

private slots:
    void on_pushButton_2_clicked(); // event, which does pushing the button
    void on_pushButton_clicked();
};

#endif // CHATWINDOW_H
