#ifndef LOGINSYSTEM_H
#define LOGINSYSTEM_H

#include <QDialog>

namespace Ui {
    class LoginSystem;
}

class LoginSystem : public QDialog {
Q_OBJECT

public:
    explicit LoginSystem(QWidget *parent = nullptr);

    ~LoginSystem();

private:
    Ui::LoginSystem *ui;
    QString login;
    QString pass;

private:
    void auth();

    bool isCorrectPass() const;

    bool isValidData() const;

signals:

    void openMainWindow();

private slots:

    void on_pushButton_clicked();
};

#endif // LOGINSYSTEM_H
