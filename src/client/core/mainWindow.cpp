#include "mainWindow.h"
#include "ui_mainwindow.h"
#include "../settings/config.h"
#include "../widgets/folderWidget.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    stackedWidget = findChild<QStackedWidget *>("stackedWidget");
    if (!stackedWidget) qDebug() << "Can't find stackedWidget";

    QWidget *rootPage = new QWidget();
    auto *gridLayoutRoot = new QGridLayout(rootPage);
    gridLayoutRoot->setSpacing(cfg::foldersView::space);

    for (int row = 0; row < cfg::foldersView::rowCount; ++row) {
        for (int col = 0; col < cfg::foldersView::columnCount; ++col) {
            QString folderName = QString("Папка %1").arg(row * cfg::foldersView::columnCount + col + 1);
            auto *folderWidget = new FolderWidget(folderName);
            gridLayoutRoot->addWidget(folderWidget, row, col);
            // Подключаем обработчик сигнала clicked для перехода при двойном клике
            QObject::connect(folderWidget, &FolderWidget::clicked, [this, folderWidget]() {
                // Двойной щелчок: переходим к следующему layout
                qDebug() << "Next folder" << folderWidget->folderName();
                QWidget *nextWidget = new QWidget();
                QVBoxLayout *nextLayout = new QVBoxLayout(nextWidget);

                QLabel *label = new QLabel("Содержимое папки " + folderWidget->folderName(), nextWidget);

                QPushButton *backButton = new QPushButton("Назад", nextWidget);
                QObject::connect(backButton, &QPushButton::clicked, [this]() { stackedWidget->setCurrentIndex(0);    });

                nextLayout->addWidget(label);
                nextLayout->addWidget(backButton);
                stackedWidget->addWidget(nextWidget);
                stackedWidget->setCurrentWidget(nextWidget);
            });
        }
    }

    stackedWidget->addWidget(rootPage);
    stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    delete ui;
    delete stackedWidget;
}
