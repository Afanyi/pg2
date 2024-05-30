#include "DungeonCrawler.h"
#include "Character.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
DungeonCrawler::DungeonCrawler(): level(new Level()), terminal(new TerminalUI())
{

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
}
// could have simplified the move function but teleportation is not working as expected
pair<Tile*,Character*> DungeonCrawler::Teleportation(Tile *t,Tile *newTile, Character *a, int crow, int ccol)
{
    Portal* p;
    Tile* destPortal;
    pair<Tile*,Character*> result;
    if(newTile->getRow()==1 && newTile->getColumn()==1){
        p = level->portals[0];
    }
    else{
        p = level->portals[1];
    }
    auto pair = p->onEnter(a);
    destPortal = pair.second;
    t->moveTo(level->getTile(destPortal->getRow()+crow,destPortal->getColumn()+ccol),a);
    result.first = t;
    result.second = a;
    return result;
}

void DungeonCrawler::move(Tile *t, Character *a, int crow, int ccol)
{
    // obtaining new character location
    Tile* newTile;
    newTile = level->getTile(t->getRow()+crow,t->getColumn()+ccol);
    if(newTile->getTexture() == "o"){
        // teleportaion
        std::cout << newTile->getRow() << " new " << newTile->getColumn() << std::endl;
        std::cout << "is portal " << std::endl;
        std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
        Portal* p;
        Tile* destPortal;
        if((newTile->getRow()==1 && newTile->getColumn()==1)){
            std::cout << "hi" << std::endl;
            p = level->portals[0];
            auto pair = p->onEnter(a);
            destPortal = pair.second;
            t->moveTo(level->getTile(destPortal->getRow()-crow,destPortal->getColumn()-ccol),a);
        }
        else{
            std::cout << "hello" << std::endl;
            p = level->portals[1];
            auto pair = p->onEnter(a);
            destPortal = pair.second;
            t->moveTo(level->getTile(destPortal->getRow()-crow,destPortal->getColumn()-ccol),a);
        }
        newTile = nullptr;
    }
    else{
        if(!(t->onLeave(newTile,a) && t->onEnter(a).first)){
            std::cout << "you can move on this tile choose another ziel" << std::endl;
        }
        else{
            t->moveTo(level->getTile((t->getRow())+crow,t->getColumn()+ccol),a);
            Switch* s = level->getSwitc();
            if(newTile->getRow()==s->getRow() && newTile->getColumn()==s->getColumn()){
                Door* d = level->getDoor();
                s->attach(d);
                s->activate();
                s->detach(d);
            }
        }
    }
}

bool DungeonCrawler::turn()
{
    Input inputB;
    Input inputc;

    int randomMoveB;
    int randomMoveC;
    bool gaming = true;
    // creating characters
    Character* a = new Character("a");

    // setting character terminal attribute
    a->setTerminal(terminal);

    // placing character
    level->placeCharacter(a,8,3);

    // obtaining actual character location
    Tile* t = level->getTile(8,3);
    // initialising new location
    Tile* newTile;

    // drawing terminal
    terminal->draw(level);
    //a->getTerminal()
    level->setPortalSettings();
    std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
    while(gaming){
        // player movement
        srand(time(0));
        //Input m = terminal->move();
        Input m = a->move();
        if(m==Input::up){
            move(t,a,-1,0);
        }
        else if(m==Input::down){
            move(t,a,1,0);
        }
        else if(m== Input::left){
            move(t,a,0,-1);
        }
        else if(m== Input::right){
            move(t,a,0,1);
        }
        else{
            std::cout << " game over " << std::endl;
            //gaming = false;
            break;
        }
        t = a->getTile();
        std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
        terminal->draw(level);
    }
    return false;
}
