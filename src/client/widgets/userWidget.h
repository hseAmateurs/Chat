//
// Created by Shon on 16.05.2024.
//

#ifndef CHAT_USERWIDGET_H
#define CHAT_USERWIDGET_H


#include "widget.h"

class UserWidget : public Widget {
Q_OBJECT
public:
    explicit UserWidget(const QPair<int, QString> &info, QWidget *parent = nullptr)
            : Widget(info, ":/images/user.ico", parent) { };

};


#endif //CHAT_USERWIDGET_H
