#include "chatwindow.h"
#include "ui_chatwindow.h"

chatwindow::chatwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
}

chatwindow::~chatwindow()
{
    delete ui;
}

void chatwindow::on_pushButton_2_clicked()
{
    this->close(); // close the chatting window
    emit OpenMainWindow(); // send a signal from the chatting window to the main window
}

