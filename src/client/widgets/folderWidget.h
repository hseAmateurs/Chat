//
// Created by Shon on 16.05.2024.
//

#ifndef CHAT_FOLDERWIDGET_H
#define CHAT_FOLDERWIDGET_H

#include "widget.h"

class FolderWidget : public Widget {
Q_OBJECT
public:
    explicit FolderWidget(const QPair<int, QString> &info, QWidget *parent = nullptr)
            : Widget(info, ":/images/folder.ico", parent) { };

};

#endif //CHAT_FOLDERWIDGET_H
