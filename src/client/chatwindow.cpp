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

void ChatWindow::sendMessage(int from, double time, std::string text)
{
    if (from == 1) // a message is from server for example
    {
        if (!text.empty())
        {
            QString message = QString::fromUtf8(text.c_str());
            QLabel *answer = new QLabel(message);
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
    else // a message is from client
    {
        if (!text.empty())
        {
            QString message = QString::fromUtf8(text.c_str());
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
        }

    }
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
    std::string text = message.toUtf8().constData(); // here you can send this message on server or on data base
    sendMessage(0, 1.45, text); // server sends a message
}

//void ChatWindow::onEnterPressed()
//{
//    //QString message = ui->message->toPlainText();
//    //std::string text = message.toUtf8().constData(); // here you can send this message on server or on data base
//    //sendMessage(0, 1.45, text); // server sends a message
//    on_pushButton_clicked();
//}

//void ChatWindow::keyPressEvent(QKeyEvent *event)
//{
//    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
//    {
//        QString message = ui->message->toPlainText();
//        std::string text = message.toUtf8().constData(); // here you can send this message on server or on data base
//        sendMessage(0, 1.45, text); // server sends a message
//    }
//    else
//    {
//        QWidget::keyPressEvent(event);
//    }
//}

