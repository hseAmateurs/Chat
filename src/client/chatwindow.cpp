#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

ChatWindow::ChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
    lay = new QVBoxLayout();
    lay->setAlignment(Qt::AlignTop);
    ui->frame->setLayout(lay);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

void ChatWindow::on_pushButton_2_clicked()
{
    this->close(); // close the chatting window
    emit openMainWindow(); // send a signal from the chatting window to the main window
}


void ChatWindow::on_pushButton_clicked()
{
    QString message = ui->message->toPlainText();
    QLabel *label = new QLabel(message);
    label->setContentsMargins(5, 5, 5, 5);
    QFont font = label->font();
    font.setPointSize(11);
    label->setFont(font);
    label->setMaximumWidth(150);
    label->setMinimumWidth(100);
    label->setMinimumHeight(30);
    label->adjustSize();
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignRight);
    label->setAlignment(Qt::AlignLeft);
    label->setStyleSheet("QLabel {background-color: #A9F3E6}");
    lay->setContentsMargins(0, 0, 30, 0);
    lay->addWidget(label);
    lay->addSpacing(12);
    ui->message->clear();
}

