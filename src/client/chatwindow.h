#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
//#include "textarea.h"

namespace Ui {
class chatwindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    void sendMessage(int from, double time, std::string text); // function, which sends a message on the screen
    ~ChatWindow();

private:
    Ui::chatwindow *ui;
    QVBoxLayout *lay;
    QHBoxLayout *hlay1;
    QHBoxLayout *hlay2;
    QScrollArea *scroll;
    //TextArea *textArea;

signals:
    void openMainWindow(); // create a signal, which opens the main window

private slots:
    void on_pushButton_2_clicked(); // event, which does pushing the button
    void on_pushButton_clicked();
    //void onEnterPressed();
//protected:
//    void keyPressEvent(QKeyEvent *event) override; // for sending messages by enter
};

#endif // CHATWINDOW_H
