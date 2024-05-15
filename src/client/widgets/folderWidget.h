//
// Created by Shon on 15.05.2024.
//

#ifndef CHAT_FOLDERWIDGET_H
#define CHAT_FOLDERWIDGET_H

#include <QtWidgets>

class FolderWidget : public QWidget {
Q_OBJECT
public:
    explicit FolderWidget(const QPair<int, QString> &folder, QWidget *parent = nullptr);

    QString name() const { return m_folderName; }

    int id() const { return m_folderId; }

public slots:

    void deselect();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

signals:

    void clicked();

private:
    QString m_folderName;
    bool m_selected;
    int m_folderId;

private:
    void setBackgroundColor(const QColor &color);

    void handleClick();
};


#endif //CHAT_FOLDERWIDGET_H
