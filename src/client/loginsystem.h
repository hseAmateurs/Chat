#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QDialog>

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
};

#endif // LOGINSYSTEM_H
