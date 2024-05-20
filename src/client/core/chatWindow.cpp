#include "chatWindow.h"
#include "ui_chatwindow.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QScrollBar>

ChatWindow::ChatWindow(int folderId, const QString &folderName, QWidget *parent) :
        QDialog(parent), folderId(folderId), lastMsgTime(""),
        ui(new Ui::ChatWindow) {
    ui->setupUi(this);
    ui->label->setText(folderName);

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

    updateChat(false);
}


void ChatWindow::sendMessage(int from, QString message) {
    if (from == 1) { // a message is from server for example
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
    else { // a message is from client
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

ChatWindow::~ChatWindow() {
    delete ui;
}

void ChatWindow::on_pushButton_2_clicked() {
    this->close();
}

void ChatWindow::on_pushButton_clicked() {
    QString message = ui->message->toPlainText();
    if (message.isEmpty()) return;

    Cacher::instance().sendMsg(folderId, message);
    sendMessage(0, message);
    emit sentMsg();
}

void ChatWindow::updateChat(bool onlyLast) {
    QVector<QPair<int, QString>> msgs;
    Cacher::instance().getLastMsgs(folderId, msgs, lastMsgTime);
    for (auto &msg: msgs) {
        if (onlyLast) {
            if (msg.first != Cacher::instance().getUserId())
                sendMessage(1, msg.second);
        }
        else
            sendMessage(msg.first != Cacher::instance().getUserId(), msg.second);
    }
}
