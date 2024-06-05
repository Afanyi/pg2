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
    for(auto vt : tiles){
        for (auto t : vt){
            if(dynamic_cast<Portal*>(t) != nullptr){
                portals.push_back(dynamic_cast<Portal*>(t));
            }
        }
    }
    cout << portals[0]->getRow() << "  " << portals[0]->getColumn() << endl;
    cout << portals.size() << endl;
    for(int i=0;i<portals.size();i+=2){
        portals[i]->setDestination(portals[i+1]);
        portals[i+1]->setDestination(portals[i]);
    }

    // obtaning and storing the position of the portals
    // Portal* p1 = static_cast<Portal*>(tiles[1][1]);
    // Portal* p2 = static_cast<Portal*>(tiles[7][1]);

    // //setting portal destinations
    // p1->setDestination(p2);
    // p2->setDestination(p1);
    // portals.push_back(p1);
    // portals.push_back(p2);
}

void Level::generateTile()
{   int row = -1;
    int column = 0;
    for(int i=0;i<l.size();i++){
        if (i % width == 0){
            row++;
        }
        column = (i%width);

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

int Level::getWidth() const
{
    return width;
}

int Level::getHeight() const
{
    return height;
}

vector<Character *> Level::getCharacters() const
{
    return characters;
}

Door *Level::getDoorpos()
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
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
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(dynamic_cast<Switch*>(tiles[i][j]) != nullptr){
                switc = dynamic_cast<Switch*>(tiles[i][j]);
                return switc;
            }
        }
    }
    return nullptr;
}

void Level::switchPortalsetting()
{
    switc->attach(door);
}

Level::Level() : width(16),height(8),tiles(),characters()
{
    int row = -1;
    int column = 0;
    //initialising tiles with nullptr
    for(int i=0;i<height;i++){
        vector<Tile*> v;
        for(int j=0;j<width;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // creating tiles
    generateTile();
    // printing level
    a = new Character("a");
    placeCharacter(a,1,2);
    printLevel();

    door = getDoorpos();
    switc = getSwitcpos();
    setPortalSettings();

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
    tiles.clear();
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
    //setPortalSettings();
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
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
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
    for (int i=0;i<height;i++){
        for(int j=0; j<width; j++){
            cout << tiles[i][j]->getTexture();
        }
        cout << endl;
    }
    cout << endl;
}
