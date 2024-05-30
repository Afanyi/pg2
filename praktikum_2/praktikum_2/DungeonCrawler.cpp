#include "DungeonCrawler.h"
#include "Character.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;
DungeonCrawler::DungeonCrawler(): level(new Level()), terminal(new TerminalUI())
{

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
            std::cout << p->getRow() << "  " << p->getColumn() << std::endl;
            p = level->portals[1];
            auto pair = p->onEnter(a);
            destPortal = pair.second;
            t->moveTo(level->getTile(destPortal->getRow()-crow,destPortal->getColumn()-ccol),a);
        }
        newTile = nullptr;
    }
    else if(newTile->getTexture() == "#"){
        std::cout << "you can move on a wall choose another ziel" << std::endl;
    }
    else{
        bool x = t->moveTo(level->getTile((t->getRow())+crow,t->getColumn()+ccol),a);
        std::cout << x << std::endl;
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
    Character* b = new Character("b");
    Character* c = new Character("c");

    // setting character terminal attribute
    a->setTerminal(terminal);
    b->setTerminal(terminal);
    c->setTerminal(terminal);

    // placing character
    level->placeCharacter(a,8,3);
    level->placeCharacter(b,3,3);
    level->placeCharacter(c,4,2);

    // obtaining actual character location
    Tile* t = level->getTile(8,3);
    Tile* tb = level->getTile(3,3);
    Tile* tc = level->getTile(4,2);

    // initialising new location
    Tile* newTile;
    Tile* newTileb;
    Tile* newTilec;

    // drawing terminal
    terminal->draw(level);
    level->setPortalSettings();
    std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
    while(gaming){
        // player movement
        srand(time(0));
        Input m = terminal->move();
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
            break;
        }
        // pvp player movement
        randomMoveB = (int)(rand() % 3)+1;
        randomMoveC = (int)(rand() % 3)+1;
        inputB = terminal->ConvertNumberToInput(randomMoveB);
        inputc = terminal->ConvertNumberToInput(randomMoveC);

        // pvp b
        if(inputB==Input::up){
            move(tb,b,-1,0);
        }
        else if(inputB==Input::down){
            move(tb,b,1,0);
        }
        else if(inputB== Input::left){
            move(tb,b,0,-1);
        }
        else if(inputB== Input::right){
            move(tb,b,0,1);
        }

        // pvp c movement
        if(inputc==Input::up){
            move(tc,c,-1,0);
        }
        else if(inputc==Input::down){
            move(tc,c,1,0);
        }
        else if(inputc== Input::left){
            move(tc,c,0,-1);
        }
        else if(inputc== Input::right){
            move(tc,c,0,1);
        }

        // obtaning new locations after movement
        t = a->getTile();
        tb = b->getTile();
        tc = c->getTile();
        std::cout << t->getRow() << "  " << t->getColumn() << std::endl;
        terminal->draw(level);
    }
    return false;
}


