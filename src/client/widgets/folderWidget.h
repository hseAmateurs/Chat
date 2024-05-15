//
// Created by Shon on 15.05.2024.
//

#ifndef CHAT_FOLDERWIDGET_H
#define CHAT_FOLDERWIDGET_H

#include <QtWidgets>

class FolderWidget : public QWidget {
Q_OBJECT
public:
    explicit FolderWidget(const QString &folderName, QWidget *parent = nullptr);

    QString folderName() const { return m_folderName; }


protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

signals:

    void clicked();

private:
    QString m_folderName;
    bool m_selected;

private:
    void setBackgroundColor(const QColor &color);

    void handleClick();
};


#endif //CHAT_FOLDERWIDGET_H
