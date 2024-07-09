#include "mainwindow.h"
#include "DungeonCrawler.h"
//#include "GraphicalUI.h"
#include <iostream>
#include "List_impl.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // GraphicalUI* ui = new GraphicalUI();
    // DungeonCrawler* d = new DungeonCrawler(ui);
    //ui->mainWindow->d = d;
    DungeonCrawler* d = new DungeonCrawler();
    GraphicalUI* ui = new GraphicalUI(d);
    d->setUi(ui);
    return a.exec();
}

// int main(){
//     Level l =  Level();
//     Level l2 =  Level();

//     l = l2;
//     std::cout << " woriking " << std::endl;

//     // l.printLevel();

//     //std::cout << Level::getLevelString("level1.txt") << std::endl;

//     return 0;
// }
