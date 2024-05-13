#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QScrollBar>

ChatWindow::ChatWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatwindow)
{
    ui->setupUi(this);
    lay = new QVBoxLayout();
    lay->setAlignment(Qt::AlignTop);
    ui->frame->setLayout(lay);
    scroll = new QScrollArea(this);
    scroll->setStyleSheet("QScrollArea {border: none}"
                          "QScrollBar:vertical {"
                          "background-color: #d0f3e6;"
                          "width: 14px;"
                          "}");
    scroll->setWidget(ui->frame);
    scroll->setGeometry(9, 79, 481, 401);
    scroll->setWidgetResizable(true);
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
    if (!message.isEmpty())
    {
        QLabel *label = new QLabel(message);
        label->setContentsMargins(5, 5, 5, 5);
        QFont font = label->font();
        font.setPointSize(11);
        label->setFont(font);
        label->setMaximumWidth(150);
        label->setMinimumWidth(150);
        label->setMinimumHeight(30);
        label->adjustSize();
        label->setWordWrap(true);
        hlay1 = new QHBoxLayout();
        //label->setAlignment(Qt::AlignRight);
        //label->setAlignment(Qt::AlignLeft);
        label->setStyleSheet("QLabel {background-color: #A9F3E6}");
        QSpacerItem *spacerLabel = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        hlay1->addWidget(label);
        hlay1->addItem(spacerLabel);
        hlay1->setAlignment(label, Qt::AlignRight);
        //lay->setContentsMargins(0, 0, 20, 0);
        //lay->addWidget(label);
        lay->addLayout(hlay1);
        lay->addSpacing(12);
        ui->message->clear();

        QLabel *answer = new QLabel("Как здорово!");
        answer->setContentsMargins(5, 5, 5, 5);
        QFont font1 = answer->font();
        font1.setPointSize(11);
        answer->setFont(font1);
        answer->setMaximumWidth(150);
        answer->setMinimumWidth(150);
        answer->setMinimumHeight(30);
        answer->adjustSize();
        answer->setWordWrap(true);
        hlay2 = new QHBoxLayout();
        //answer->setAlignment(Qt::AlignLeft);
        //answer->setAlignment(Qt::AlignLeft);
        answer->setStyleSheet("QLabel {background-color: #e5e5e5}");
        QSpacerItem *spacerAnswer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        hlay2->addItem(spacerAnswer);
        hlay2->addWidget(answer);
        hlay2->setAlignment(answer, Qt::AlignLeft);
        //lay->setContentsMargins(0, 0, 20, 0);
        //lay->addWidget(answer);
        lay->addLayout(hlay2);
        lay->addSpacing(12);
    }
}

