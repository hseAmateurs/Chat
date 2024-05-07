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
};

#endif // CHATWINDOW_H
