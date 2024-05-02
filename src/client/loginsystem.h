#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QDialog>
#include "Authorisation.h"

namespace Ui {
class LoginSystem;
}

class LoginSystem : public QDialog
{
    Q_OBJECT

public:
    explicit LoginSystem(QWidget *parent = nullptr);
    ~LoginSystem();

private:
    Ui::LoginSystem *ui;
signals:
    void OpenMainWindow(); // create a signal, which opens the main window

private slots:
    void on_pushButton_clicked(); // event, which does pushing the button
};

#endif // LOGINSYSTEM_H
