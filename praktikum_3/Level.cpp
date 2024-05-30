#include "Level.h"
#include "Character.h"
#include <iostream>
using namespace std;

vector<vector<Tile *> > Level::getTiles() const
{
    return tiles;
}

void Level::setPortalSettings()
{
    /*
    Portal* p1 = new Portal("o",1,1);
    Portal* p2 = new Portal("o",7,1);
    tiles[1][1] = p1;
    tiles[7][1] = p1;*/

    // obtaning and storing the position of the portals
    Portal* p1 = static_cast<Portal*>(tiles[1][1]);
    Portal* p2 = static_cast<Portal*>(tiles[7][1]);

    //setting portal destinations
    p1->setDestination(p2);
    p2->setDestination(p1);
    portals.push_back(p1);
    portals.push_back(p2);
}

void Level::generateTile()
{   int row = -1;
    int column = 0;
    for(int i=0;i<l.size();i++){
        if (i % 10 == 0){
            row++;
        }
        column = (i%10);

        Tile * a = new Floor(".",1,1);
        if(l[i] == '.'){
            a = new Floor(".",row,column);
        }
        else if(l[i] == 'X'){
            a = new Door("X",row,column);
        }
        else if(l[i] == '<'){
            a = new Ramp("<",row,column);
        }
        else if(l[i] == '?'){
            a = new Switch("?",row,column);
        }
        else if(l[i] == '_'){
            a = new Pit("_",row,column);
        }
        else if(l[i] == 'O'){
            a = new Portal("o",row,column);
        }
        else if(l[i] == '#'){
            a = new Wall("#",row,column);
        }
        tiles.at(row).at(column) = a;
    }
}

Door *Level::getDoor() const
{
    return door;
}

Switch *Level::getSwitc() const
{
    return switc;
}

Door *Level::getDoorpos()
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(dynamic_cast<Door*>(tiles[i][j]) != nullptr){
                door = dynamic_cast<Door*>(tiles[i][j]);
                return door;
            }
        }
    }
    return nullptr;
}

Switch *Level::getSwitcpos()
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(dynamic_cast<Switch*>(tiles[i][j]) != nullptr){
                switc = dynamic_cast<Switch*>(tiles[i][j]);
                return switc;
            }
        }
    }
    return nullptr;
}

Level::Level() : width(10),height(10),tiles(),characters()
{
    int row = -1;
    int column = 0;
    //initialising tiles with nullptr
    for(int i=0;i<width;i++){
        vector<Tile*> v;
        for(int j=0;j<height;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // creating tiles
    generateTile();
    // printing level
    printLevel();
    door = getDoorpos();
    switc = getSwitcpos();
    cout << endl;

}

Level::Level(const Level &l): width(l.width),height(l.height)
{
    for(int i=0;i<width;i++){
        vector<Tile*> v;
        for(int j=0;j<height;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // copying tiles
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            Tile* otherTile = l.getTiles()[i][j];
            if(typeid(*otherTile) == typeid(Floor)){
                tiles[i][j] = new Floor(*dynamic_cast<Floor*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Wall)){
                tiles[i][j] = new Wall(*dynamic_cast<Wall*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Portal)){
                tiles[i][j] = new Portal(*dynamic_cast<Portal*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Pit)){
                tiles[i][j] = new Pit(*dynamic_cast<Pit*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Ramp)){
                tiles[i][j] = new Ramp(*dynamic_cast<Ramp*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Switch)){
                tiles[i][j] = new Switch(*dynamic_cast<Switch*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Door)){
                tiles[i][j] = new Door(*dynamic_cast<Door*>(otherTile));
            }
            else{
                tiles[i][j] = nullptr;
            }
        }
    }
    // copy character
    if(!l.characters.empty()){
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(l.tiles[i][j]->hasCharacter()){
                    Character *c = new Character((l.tiles[i][j]->getCharacter())->getTyp());
                    tiles[i][j]->setCharacter(c);
                }
            }
        }
    }
    // general settings
    setPortalSettings();
    door = getDoorpos();
    switc = getSwitcpos();
}

Level &Level::operator=(const Level &l)
{
    // destruction
    for (auto  v : tiles){
        for(auto t : v){
            delete t;
        }
    }
    portals.clear();
    if(!portals.empty()){
        portals.pop_back();
        portals.pop_back();
    }
    characters.clear();
    if(!characters.empty()){
        for(auto c : characters){
            delete c;
        }
    }
    // initialising level with nullptr
    //characters = l.characters;
    for(int i=0;i<width;i++){
        vector<Tile*> v;
        for(int j=0;j<height;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // copying tiles
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            Tile* otherTile = l.getTiles()[i][j];
            if(typeid(*otherTile) == typeid(Floor)){
                tiles[i][j] = new Floor(*dynamic_cast<Floor*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Wall)){
                tiles[i][j] = new Wall(*dynamic_cast<Wall*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Portal)){
                tiles[i][j] = new Portal(*dynamic_cast<Portal*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Pit)){
                tiles[i][j] = new Pit(*dynamic_cast<Pit*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Ramp)){
                tiles[i][j] = new Ramp(*dynamic_cast<Ramp*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Switch)){
                tiles[i][j] = new Switch(*dynamic_cast<Switch*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Door)){
                tiles[i][j] = new Door(*dynamic_cast<Door*>(otherTile));
            }
            else{
                tiles[i][j] = nullptr;
            }
        }
    }
    // copy Character
    if(!l.characters.empty()){
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(l.tiles[i][j]->hasCharacter()){
                    Character *c = new Character((l.tiles[i][j]->getCharacter())->getTyp());
                    tiles[i][j]->setCharacter(c);
                }
            }
        }
    }
    // switch and door getting
    setPortalSettings();
    door = getDoorpos();
    switc = getSwitcpos();
    return *this;
}


Level::~Level()
{
    // deletin tiles from heap
    for (auto  v : tiles){
        for(auto t : v){
            delete t;
        }
    }
    if(!characters.empty()){
        for(auto c : characters){
            delete c;
        }
    }

}

Tile *Level::getTile(int row, int col)
{
    for(int i=0;i<width;i++){
        for(int j=0;j<height;j++){
            if(i==row && j == col){
                return tiles[i][j];
            }
        }
    }
    return nullptr;
}

void Level::placeCharacter(Character *c, int row, int col)
{
    characters.push_back(c);
    Tile* theTile = getTile(row,col);
    c->setTile(theTile);
    theTile->setCharacter(c);
}

void Level::printLevel()
{
    for (int i=0;i<width;i++){
        for(int j=0; j<height; j++){
            cout << tiles[i][j]->getTexture();
        }
        cout << endl;
    }
    cout << endl;
}
