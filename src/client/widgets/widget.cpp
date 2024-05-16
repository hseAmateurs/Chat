//
// Created by Shon on 15.05.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Folder.h" resolved

#include <QVBoxLayout>
#include <QLabel>
#include "widget.h"

Widget::Widget(const QPair<int, QString> &info, const QString &icon, QWidget *parent)
        : QWidget(parent), m_name(info.second), m_selected(false), m_id(info.first) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Иконка папки
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(icon)); // Установите путь к иконке папки
    layout->addWidget(iconLabel, 0, Qt::AlignHCenter);

    // Текст с именем папки
    QLabel *textLabel = new QLabel(m_name, this);
    textLabel->setAlignment(Qt::AlignHCenter);
    layout->addWidget(textLabel, 0, Qt::AlignHCenter);

    // Устанавливаем минимальный размер для элемента-папки
    setMinimumSize(120, 120);

    // Соединяем сигналы и слоты для обработки щелчков мыши
    QObject::connect(this, &Widget::clicked, this, &Widget::handleClick);
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        handleClick();
        emit clicked();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void Widget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        handleClick();
    QWidget::mousePressEvent(event);
}

void Widget::handleClick() {
    setBackgroundColor(m_selected ? QColor("#f0f0f0") : Qt::blue);
    m_selected = !m_selected;
}

void Widget::setBackgroundColor(const QColor &color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(pal);
}

void Widget::deselect() {
    if (m_selected) handleClick();
}
