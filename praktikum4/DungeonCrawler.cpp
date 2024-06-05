#include "DungeonCrawler.h"
#include "Character.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
GraphicalUI *DungeonCrawler::getUi() const
{
    return ui;
}

Level *DungeonCrawler::getLevel() const
{
    return level;
}

DungeonCrawler::DungeonCrawler(GraphicalUI* ui): ui(ui),level(ui->level)
{

}

DungeonCrawler::DungeonCrawler(TerminalUI *ui)
{
    auto* tmp = new Level();
    level = new Level(*tmp); // currentLevel is attribute of DungeonCrawler
    delete tmp;
    ui->draw(level);
    // Test assignment
    tmp = new Level();
    *level = *tmp;
    ui->draw(level);
    delete tmp;
}

DungeonCrawler::DungeonCrawler(const DungeonCrawler &dungeonCrawler): level(dungeonCrawler.level),
    terminal(dungeonCrawler.terminal)
{

}

DungeonCrawler &DungeonCrawler::operator=(const DungeonCrawler &d)
{
    delete level;
    delete terminal;
    this->terminal = d.terminal;
    this->level = d.level;
    return *this;
}

DungeonCrawler::~DungeonCrawler()
{
    delete level;
    delete terminal;
    delete ui;
}
// could have simplified the move function but teleportation is not working as expected


void DungeonCrawler::move(Tile *t, Character *a, int crow, int ccol)
{
    // obtaining new character location
    //level->setPortalSettings();
    vector<Portal*> portals = level->portals;
    Tile* newTile;
    newTile = level->getTile(t->getRow()+crow,t->getColumn()+ccol);
    cout << " hi " << endl;

    if(!(t->onLeave(newTile,a))){
        std::cout << "you can move on this tile choose another ziel" << std::endl;
    }
    else{
        t->moveTo(newTile,a);
    }
}

bool DungeonCrawler::turn()
{

    // creating characters
    Character* a = level->getCharacters()[0];
    cout << a->getTyp() << endl;

    // setting character terminal attribute
    a->setTerminal(ui);

    // obtaining actual character location
    Tile* t = a->getTile();
    // initialising new location

    level->setPortalSettings();
    std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
    level->switchPortalsetting();

    // player movement
    srand(time(0));
    //Input m = terminal->move();
    Input m = a->move();
    if(m==Input::up){
        move(t,a,-1,0);
        a->setDirection(Direction::back);
    }
    else if(m==Input::upleft){
        move(t,a,-1,-1);
        a->setDirection(Direction::left);
    }
    else if(m==Input::upright){
        move(t,a,-1,1);
        a->setDirection(Direction::right);
    }
    else if(m==Input::down){
        move(t,a,1,0);
        a->setDirection(Direction::front);
    }
    else if(m==Input::downleft){
        move(t,a,1,-1);
        a->setDirection(Direction::left);
    }
    else if(m==Input::downright){
        move(t,a,1,1);
        a->setDirection(Direction::right);
    }
    else if(m== Input::left){
        move(t,a,0,-1);
        a->setDirection(Direction::left);
    }
    else if(m== Input::right){
        move(t,a,0,1);
        a->setDirection(Direction::right);
    }
    else if(m==Input::exxit){
        return false;
    }
    std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
    return true;
}
