//
// Created by Shon on 15.05.2024.
//

#ifndef CHAT_WIDGET_H
#define CHAT_WIDGET_H

#include <QtWidgets>

class Widget : public QWidget {
Q_OBJECT
public:
    explicit Widget(const QPair<int, QString> &info, const QString &icon, QWidget *parent = nullptr);

    QString name() const { return m_name; }

    int id() const { return m_id; }

    bool isSelected() const { return m_selected; }

public slots:

    void deselect();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

signals:

    void clicked();

private:
    QString m_name;
    bool m_selected;
    int m_id;

private:
    void setBackgroundColor(const QColor &color);

    void handleClick();
};


#endif //CHAT_WIDGET_H
