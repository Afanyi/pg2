#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DungeonCrawler.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),d(nullptr)

{
    ui->setupUi(this);

    setWindowTitle("Dungeon Crawler");
    mainBack = new QLabel(this);

    mainBackground = QPixmap("./files/textures/bloody_frame.png");
    mainBackground.setDevicePixelRatio(1);
    mainBack->setPixmap(mainBackground);
    mainBack->setMinimumSize(this->size());
    mainBack->setScaledContents(true);
    setCentralWidget(mainBack);

    gridLayout = new QGridLayout(mainBack);
    mainBack->raise();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// void MainWindow::resizeEvent(QResizeEvent *event)
// {
//     QMainWindow::resizeEvent(event);
//     mainBack->setFixedSize(event->size());
//     mainBack->setPixmap(mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//     mainBackground = mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     this->resize(event->size());

// }
