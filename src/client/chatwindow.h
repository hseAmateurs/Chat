#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private:
    Ui::ChatWindow *ui;
signals:
    void openMainWindow(); // create a signal, which opens the main window

private slots:
    void on_pushButton_2_clicked(); // event, which does pushing the button
};

#endif // CHATWINDOW_H
