#include "Level.h"
#include "Character.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<Tile *> > Level::getTiles() const
{
    return tiles;
}

void Level::setPortalSettings()
{
    int id = 0;
    for(auto vt : tiles){
        for (auto t : vt){
            //if(dynamic_cast<Portal*>(t) != nullptr){
            if(typeid(*t)==typeid(Portal)){
                portals.push_back(dynamic_cast<Portal*>(t));
            }
        }
    }
    cout << portals[0]->getRow() << "  " << portals[0]->getColumn() << endl;
    cout << portals.size() << endl;
    for(unsigned int i=0;i<portals.size();i+=2){
        portals[i]->setDestination(portals[i+1]);
        portals[i+1]->setDestination(portals[i]);
        portals[i]->setId(id);
        portals[i+1]->setId(id);
        id++;
    }
}

void Level::generateTile()
{   int row = -1;
    int column = 0;
    for(unsigned int i=0;i<l.size();i++){
        if (i % width == 0){
            row++;
        }
        column = (i%width);

        Tile * a = new Floor("$",1,1);
        if(l[i] == '$'){
            a = new Lootchest(".",row,column);
        }
        else if(l[i] == '.'){
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
        else if(l[i] == '!'){
            a = new Levelchanger("!",row,column);
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

vector<Character *> Level::getCharactersSpecial()
{
    while (!charactersSpecia.empty()) {
        charactersSpecia.pop_back();
    }
    Character* chara;
    for(auto vt : tiles){
        for(auto t : vt){
            if(t->hasCharacter()){
                chara = t->getCharacter();
                charactersSpecia.push_back(chara);
            }
        }
    }

    return charactersSpecia;
}

void Level::getLevelChangers()
{
    for(auto vt : tiles){
        for(auto t : vt){
            if(typeid(*t) == typeid(Levelchanger)){
                Levelchanger* lc = dynamic_cast<Levelchanger*>(t);
                cout << " levelchangers " << lc->getRow()<< " " <<lc->getColumn() << endl;
                levelChangers.push_back(lc);
            }
        }
    }
    cout << "size of lc " << levelChangers.size() << endl;
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

string Level::getLevelString(const std::string& file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "Error: Could not open the file.";
    }

    string line;
    string content;
    while (std::getline(file, line)) {
        if(line.empty()){
            continue;
        }
        content += line;
    }
    return content;
}

void Level::getDoors()
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(dynamic_cast<Door*>(tiles[i][j]) != nullptr){
                door = dynamic_cast<Door*>(tiles[i][j]);
                doors.push_back(door);
            }
        }
    }
}

void Level::removeDeadFigurs()
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(tiles[i][j]->hasCharacter()){
                Character* chara = tiles[i][j]->getCharacter();
                if(chara->getHitpoints() <= 0){
                    auto it = find(characters.begin(),characters.end(),chara);
                    if(it != characters.end()){
                        characters.erase(it);
                    }
                    //auto it1 = find()
                    tiles[i][j]->setCharacter(nullptr);
                    delete chara;

                }
            }
        }
    }
}

int Level::getCharSize()
{
    int size = 0;
    for(auto vt : tiles){
        for(auto t : vt){
            if(t->hasCharacter()){
                size++;
            }
        }
    }
    return size;
}

Character *Level::getMainCharacter()
{
    Character* main16;
    for(auto vt : tiles){
        for(auto t : vt){
            if(t->hasCharacter()){
                main16 = t->getCharacter();
                if(main16->getCharTyp() == CharacterTyp::mainPlayer){
                    return main16;
                }
            }
        }
    }
    return nullptr;
}

void Level::switchPortalsetting()
{
    switc->attach(door);
    for(auto d : doors){
        switc->attach(d);
    }
}

Level::Level() : width(16),height(13),tiles(),characters()
{
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
    a = new Character("a",CharacterTyp::mainPlayer,20,20);
    a->setCurrentLevel(this);
    placeCharacter(a,1,2);
    printLevel();

    door = getDoorpos();
    switc = getSwitcpos();
    getDoors();
    switchPortalsetting();
    setPortalSettings();
    getLevelChangers();

    cout << endl;

}

Level::Level(string levelString, int width, int height):width(width),height(height)
{
    l = levelString;
    for(int i=0;i<height;i++){
        vector<Tile*> v;
        for(int j=0;j<width;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    generateTile();
    printLevel();
    door = getDoorpos();
    switc = getSwitcpos();
    getDoors();
    switchPortalsetting();
    setPortalSettings();
    getLevelChangers();
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
                    Character *c = new Character((l.tiles[i][j]->getCharacter())->getTyp(),(l.tiles[i][j]->getCharacter())->getCharTyp());
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
                    Character *c = new Character((l.tiles[i][j]->getCharacter())->getTyp(),(l.tiles[i][j]->getCharacter())->getCharTyp());
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
    delete switc;
    delete door;
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
