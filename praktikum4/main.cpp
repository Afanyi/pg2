#include "mainwindow.h"
#include "DungeonCrawler.h"
//#include "GraphicalUI.h"
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicalUI* ui = new GraphicalUI;
    DungeonCrawler* d = new DungeonCrawler(ui);
    ui->m_d = d;
    return a.exec();
}
