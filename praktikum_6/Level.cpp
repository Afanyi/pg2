#include "Level.h"
#include "Character.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <limits>
#include <typeinfo>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <functional>
// #include <StationaryController.h>
// #include <GuardController.h>
// #include <AttackController.h>


using namespace std;


// Assuming necessary includes and class/struct definitions for Position, Node, Tile, Portal, and PositionHash are available

void Level::addEdge(Position from, Position to) {
    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from); // Assuming undirected graph, add the reverse edge as well
}

std::vector<Position> Level::getPath(Position from, Position to) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;
    frontier.push({from, 0}); // Initialize the priority queue with the start node

    std::unordered_map<Position, int, PositionHash> costSoFar;
    costSoFar[from] = 0; // Cost to reach the start node is 0

    std::unordered_map<Position, Position, PositionHash> cameFrom;
    cameFrom[from] = from; // Start node came from itself

    while (!frontier.empty()) {
        Node current = frontier.top();
        frontier.pop();

        if (current.pos == to) {
            return reconstructPath(cameFrom, current.pos); // Return the path if the goal is reached
        }

        for (Position next : adjacencyList[current.pos]) {
            int newCost = costSoFar[current.pos] + (isPortal(current.pos, next) ? 0 : 1); // Zero cost if portal

            if (costSoFar.find(next) == costSoFar.end() || newCost < costSoFar[next]) {
                costSoFar[next] = newCost; // Update cost
                frontier.push({next, newCost}); // Add to the priority queue
                cameFrom[next] = current.pos; // Record the path
            }
        }
    }

    return {}; // Return empty path if no path found
}

// Helper function to reconstruct the path from the 'cameFrom' map
std::vector<Position> Level::reconstructPath(std::unordered_map<Position, Position, PositionHash>& cameFrom, Position current) {
    std::vector<Position> path;
    while (!(cameFrom[current].x == current.x && cameFrom[current].y == current.y)) {
        path.push_back(current); // Add the current position to the path
        current = cameFrom[current]; // Move to the previous position
    }
    path.push_back(current); // Add the start node
    std::reverse(path.begin(), path.end()); // Reverse the path to get the correct order
    return path;
}

// Method to connect edges in a grid, considering all directions including diagonals
void Level::connectingEdges() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Position current = {i, j};
            if (!(tiles[i][j]->getTexture() == "#" || tiles[i][j]->getTexture() == "X" || tiles[i][j]->getTexture() == "o")) {
                std::vector<Position> neighbors = {
                    {i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1},
                    {i + 1, j + 1}, {i - 1, j - 1}, {i + 1, j - 1}, {i - 1, j + 1}
                };

                for (Position neighbor : neighbors) {
                    if (neighbor.x >= 0 && neighbor.x < height && neighbor.y >= 0 && neighbor.y < width) {
                        if (tiles[neighbor.x][neighbor.y]->getTexture() == "." || tiles[neighbor.x][neighbor.y]->getTexture() == "<"|| tiles[neighbor.x][neighbor.y]->getTexture() == "o") {
                            addEdge(current, neighbor);
                        }
                    }
                }
            }
        }
    }

    // Connect portals
    std::cout << "The size of the portal list at this time is " << portals.size() << std::endl;
    for (auto p : portals) {
        Position pos = {p->getRow(), p->getColumn()};
        Portal* dest = p->getDestination();
        if (dest) {
            Position destpos = {dest->getRow(), dest->getColumn()};
            addEdge(pos, destpos);
            addEdge(destpos, pos);
        }
    }
}

bool Level::isPortal(Position from, Position to) {
    Tile* fromTile = getTile(from.x, from.y);
    Tile* toTile = getTile(to.x, to.y);
    return (typeid(*fromTile) == typeid(Portal) && typeid(*toTile) == typeid(Portal));
}



vector<vector<Tile*>> Level::getTiles() const {
    return tiles;
}

void Level::setPortalSettings() {
    int id = 0;
    for (auto vt : tiles) {
        for (auto t : vt) {
            auto it = find(portals.begin(),portals.end(),t);
            if (typeid(*t) == typeid(Portal) && it==portals.end()) {
                cout << "portal found at " << t->getRow() <<" " << t->getColumn()<< endl;
                portals.push_back(dynamic_cast<Portal*>(t));
            }
        }
    }
    for (unsigned int i = 0; i < portals.size(); i += 2) {
        portals[i]->setDestination(portals[i + 1]);
        portals[i + 1]->setDestination(portals[i]);
        portals[i]->setId(id);
        portals[i + 1]->setId(id);
        id++;
    }
}

void Level::generateTile() {
    int row = -1;
    int column = 0;
    for (unsigned int i = 0; i < l.size(); i++) {
        if (i % width == 0) {
            row++;
        }
        column = (i % width);

        //Tile* a = new Floor("$", 1, 1);
        Tile* a;
        switch (l[i]) {
        case '$':
            a = new Lootchest("$", row, column);
            break;
        case '.':
            a = new Floor(".", row, column);
            break;
        case 'X':
            a = new Door("X", row, column);
            break;
        case '<':
            a = new Ramp("<", row, column);
            break;
        case '?':
            a = new Switch("?", row, column);
            break;
        case '_':
            a = new Pit("_", row, column);
            break;
        case 'O':
            a = new Portal("o", row, column);
            break;
        case '#':
            a = new Wall("#", row, column);
            break;
        case '!':
            a = new Levelchanger("!", row, column);
            break;
        default:
            a = new Floor(".", row, column);
            break;
        }

        tiles.at(row).at(column) = a;
    }
}

Door* Level::getDoor() const {
    return door;
}

Switch* Level::getSwitc() const {
    return switc;
}

int Level::getWidth() const {
    return width;
}

int Level::getHeight() const {
    return height;
}

vector<Character*> Level::getCharacters() const {
    return characters;
}

vector<Character*> Level::getCharactersSpecial() {
    while (!charactersSpecia.empty()) {
        charactersSpecia.pop_back();
    }
    for (auto vt : tiles) {
        for (auto t : vt) {
            if (t->hasCharacter()) {
                Character* chara = t->getCharacter();
                charactersSpecia.push_back(chara);
            }
        }
    }

    return charactersSpecia;
}

void Level::getLevelChangers() {
    for (auto vt : tiles) {
        for (auto t : vt) {
            if (typeid(*t) == typeid(Levelchanger)) {
                Levelchanger* lc = dynamic_cast<Levelchanger*>(t);
                levelChangers.push_back(lc);
            }
        }
    }
}

Door* Level::getDoorpos() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (dynamic_cast<Door*>(tiles[i][j]) != nullptr) {
                door = dynamic_cast<Door*>(tiles[i][j]);
                return door;
            }
        }
    }
    return nullptr;
}

Switch* Level::getSwitcpos() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (dynamic_cast<Switch*>(tiles[i][j]) != nullptr) {
                switc = dynamic_cast<Switch*>(tiles[i][j]);
                return switc;
            }
        }
    }
    return nullptr;
}


string Level::getLevelString(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "Error: Could not open the file.";
    }

    string line;
    string content;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        content += line;
    }
    return content;
}

void Level::getDoors() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (dynamic_cast<Door*>(tiles[i][j]) != nullptr) {
                door = dynamic_cast<Door*>(tiles[i][j]);
                doors.push_back(door);
            }
        }
    }
}

void Level::removeDeadFigurs() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (tiles[i][j]->hasCharacter()) {
                Character* chara = tiles[i][j]->getCharacter();
                if (chara->getHitpoints() <= 0) {
                    auto it = find(characters.begin(), characters.end(), chara);
                    if (it != characters.end()) {
                        characters.erase(it);
                    }
                    tiles[i][j]->setCharacter(nullptr);
                    delete chara;
                }
            }
        }
    }
}

int Level::getCharSize() {
    int size = 0;
    for (auto vt : tiles) {
        for (auto t : vt) {
            if (t->hasCharacter()) {
                size++;
            }
        }
    }
    return size;
}

Character* Level::getMainCharacter() {
    for (auto vt : tiles) {
        for (auto t : vt) {
            if (t->hasCharacter()) {
                Character* main16 = t->getCharacter();
                if (main16->getCharTyp() == CharacterTyp::mainPlayer) {
                    return main16;
                }
            }
        }
    }
    return nullptr;
}

void Level::switchDoorsetting() {
    getDoors();
    switc = getSwitcpos();
    //switc->attach(door);
    for (auto d : doors) {
        switc->attach(d);
    }
}

Level::Level() : width(16), height(13), tiles(), characters() {
    // Initializing tiles with nullptr
    for (int i = 0; i < height; i++) {
        vector<Tile*> v;
        for (int j = 0; j < width; j++) {
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // Creating tiles
    generateTile();
    // Printing level
    a = new Character("a", CharacterTyp::mainPlayer, 15, 15);
    a->setCurrentLevel(this);
    placeCharacter(a, 1, 2);
    printLevel();

    door = getDoorpos();
    switc = getSwitcpos();
    getDoors();
    switchDoorsetting();
    setPortalSettings();
    getLevelChangers();
    connectingEdges();
}

Level::Level(string levelString, int width, int height) : width(width), height(height) {
    l = levelString;
    for (int i = 0; i < height; i++) {
        vector<Tile*> v;
        for (int j = 0; j < width; j++) {
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    generateTile();
    printLevel();
    door = getDoorpos();
    switc = getSwitcpos();
    getDoors();
    switchDoorsetting();
    setPortalSettings();
    getLevelChangers();
    connectingEdges();
}

Level::Level(const Level& l) : width(l.width), height(l.height) {
    for (int i = 0; i < width; i++) {
        vector<Tile*> v;
        for (int j = 0; j < height; j++) {
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // Copying tiles
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Tile* otherTile = l.getTiles()[i][j];
            if (typeid(*otherTile) == typeid(Floor)) {
                tiles[i][j] = new Floor(*dynamic_cast<Floor*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Wall)) {
                tiles[i][j] = new Wall(*dynamic_cast<Wall*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Portal)) {
                tiles[i][j] = new Portal(*dynamic_cast<Portal*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Pit)) {
                tiles[i][j] = new Pit(*dynamic_cast<Pit*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Ramp)) {
                tiles[i][j] = new Ramp(*dynamic_cast<Ramp*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Switch)) {
                tiles[i][j] = new Switch(*dynamic_cast<Switch*>(otherTile));
            } else if (typeid(*otherTile) == typeid(Door)) {
                tiles[i][j] = new Door(*dynamic_cast<Door*>(otherTile));
            } else {
                tiles[i][j] = nullptr;
            }
        }
    }
    // Copy character
    if (!l.characters.empty()) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                if (l.tiles[i][j]->hasCharacter()) {
                    Character* c = new Character((l.tiles[i][j]->getCharacter())->getTyp(), (l.tiles[i][j]->getCharacter())->getCharTyp());
                    tiles[i][j]->setCharacter(c);
                }
            }
        }
    }
    // General settings
    setPortalSettings();
    door = getDoorpos();
    switc = getSwitcpos();
}

Level& Level::operator=(const Level& l) {
    // destruction
    levelChangers.clear();
    getDoors();
    doors.clear();
    switc = getSwitc();
    switc->passiveObjects.clear();
    for (auto  v : tiles){
        for(auto t : v){
            delete t;
        }
    }
    tiles.clear();
    portals.clear();

    while(!portals.empty()){
        portals.pop_back();
    }

    characters.clear();
    for(int i=0;i<height;i++){
        vector<Tile*> v;
        for(int j=0;j<width;j++){
            v.push_back(nullptr);
        }
        tiles.push_back(v);
    }
    // copying tiles
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
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
            else if(typeid(*otherTile) == typeid(Levelchanger)){
                tiles[i][j] = new Levelchanger(*dynamic_cast<Levelchanger*>(otherTile));
            }
            else if(typeid(*otherTile) == typeid(Lootchest)){
                tiles[i][j] = new Lootchest(*dynamic_cast<Lootchest*>(otherTile));
            }
            else{
                tiles[i][j] = nullptr;
            }
        }
    }
    // copy Character
    if(!l.characters.empty()){
        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                if(l.tiles[i][j]->hasCharacter()){
                    auto oldcharacter = l.tiles[i][j]->getCharacter();
                    Character *c = new Character((l.tiles[i][j]->getCharacter())->getTyp(),(l.tiles[i][j]->getCharacter())->getCharTyp());
                    c->setTerminal(oldcharacter->getTerminal());
                    c->setIsLootchestFound(oldcharacter->getIsLootchestFound());
                    tiles[i][j]->setCharacter(c);
                    placeCharacter(c,tiles[i][j]->getRow(),tiles[i][j]->getColumn());
                }
            }
        }
    }
    //cout << " /////////hi problem" << endl;
    printLevel();
    switchDoorsetting();
    setPortalSettings();
    getLevelChangers();
    connectingEdges();
     characters = getCharactersSpecial();
    //cout << "%%%% working  sucess"  << characters.size() << endl;

    return *this;
}

Level::~Level() {
    // delete switc;
    // delete door;
    // Deleting tiles from heap
    for (auto v : tiles) {
        for (auto t : v) {
            delete t;
        }
    }
    // if (!characters.empty()) {
    //     for (auto c : characters) {
    //         delete c;
    //     }
    // }
}

Tile* Level::getTile(int row, int col) {
    if (row >= 0 && row < height && col >= 0 && col < width) {
        return tiles[row][col];
    }
    return nullptr;
}

void Level::placeCharacter(Character* c, int row, int col) {
    characters.push_back(c);
    Tile* theTile = getTile(row, col);
    c->setTile(theTile);
    theTile->setCharacter(c);
}

void Level::printLevel() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << tiles[i][j]->getTexture();
        }
        cout << endl;
    }
    cout << endl;
}
