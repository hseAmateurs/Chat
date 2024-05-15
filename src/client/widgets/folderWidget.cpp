//
// Created by Shon on 15.05.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Folder.h" resolved

#include <QVBoxLayout>
#include <QLabel>
#include "folderWidget.h"

FolderWidget::FolderWidget(const QPair<int, QString> &folder, QWidget *parent)
        : QWidget(parent), m_folderName(folder.second), m_selected(false), m_folderId(folder.first) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Иконка папки
    QLabel *iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(":/images/folder.ico")); // Установите путь к иконке папки
    layout->addWidget(iconLabel, 0, Qt::AlignHCenter);

    // Текст с именем папки
    QLabel *textLabel = new QLabel(m_folderName, this);
    textLabel->setAlignment(Qt::AlignHCenter);
    layout->addWidget(textLabel, 0, Qt::AlignHCenter);

    // Устанавливаем минимальный размер для элемента-папки
    setMinimumSize(120, 120);

    // Соединяем сигналы и слоты для обработки щелчков мыши
    connect(this, &FolderWidget::clicked, this, &FolderWidget::handleClick);
}

void FolderWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        handleClick();
        emit clicked();
    }
    QWidget::mouseDoubleClickEvent(event);
}

void FolderWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        handleClick();
    QWidget::mousePressEvent(event);
}

void FolderWidget::handleClick() {
    setBackgroundColor(m_selected ? QColor("#f0f0f0") : Qt::blue);
    m_selected = !m_selected;
}

void FolderWidget::setBackgroundColor(const QColor &color) {
    QPalette pal = palette();
    pal.setColor(QPalette::Background, color);
    setAutoFillBackground(true);
    setPalette(pal);
}

void FolderWidget::deselect() {
    if (m_selected) handleClick();
}
