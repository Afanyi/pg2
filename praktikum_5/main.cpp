#include "mainwindow.h"
#include "DungeonCrawler.h"
//#include "GraphicalUI.h"
#include <iostream>
#include "List_impl.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphicalUI* ui = new GraphicalUI;
    DungeonCrawler* d = new DungeonCrawler(ui);
    //ui->mainWindow->level = d->levels[1];

    ui->mainWindow->d = d;
    return a.exec();
}

// int main(){

//     std::cout << Level::getLevelString("level1.txt") << std::endl;
//     return 0;
// }
