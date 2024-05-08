#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>

namespace Ui {
class chatwindow;
}

class chatwindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatwindow(QWidget *parent = nullptr);
    ~chatwindow();

private:
    Ui::chatwindow *ui;
signals:
    void OpenMainWindow(); // create a signal, which opens the main window

private slots:
    void on_pushButton_2_clicked(); // event, which does pushing the button
};

#endif // CHATWINDOW_H
