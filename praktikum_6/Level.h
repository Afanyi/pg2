#ifndef LEVEL_H
#define LEVEL_H
//#include "Character.h"
#include <vector>
#include "Portal.h"
#include "Floor.h"
#include "Wall.h"
#include "Door.h"
#include "Switch.h"
#include "Pit.h"
#include "Ramp.h"
#include "Lootchest.h"
#include "Levelchanger.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

class AbstractController;
// Define a position structure
struct Position {
    int x, y;
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

// Hash function for Position to use in unordered_map
struct PositionHash {
    std::size_t operator()(const Position& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

// Node structure for Dijkstra's algorithm
struct Node {
    Position pos;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};
using std::vector;

class Character;


class Level{
    std::vector<Position> reconstructPath(std::unordered_map<Position, Position, PositionHash>& cameFrom, Position current);
    std::unordered_map<Position, std::vector<Position>, PositionHash> adjacencyList;
    vector<vector<Tile*>> tiles;
    int width;
    int height;
    Door* door;
    Switch* switc;
    Door* getDoorpos();
    Switch* getSwitcpos();
    Character* a;
public:
    string l = getLevelString("level1.txt");

    string l1 = {
        "################"
        "#!.............#"
        "#..............#"
        "#..............#"
        "#..............#"
        "#......###/#####"
        "#O.....#.......#"
        "######.#..._<..#"
        "#.........___..#"
        "#..............#"
        "#.............!#"
        "#O.....?.......#"
        "################"

    };

    std::vector<Position> getPath(Position from, Position to);
    void addEdge(Position from, Position to);
    void connectingEdges();
    bool isPortal(Position from, Position to);
    static string getLevelString(const std::string& file_path);
    void getDoors();
    vector<Door*> doors;
    void removeDeadFigurs();
    int getCharSize();
    Character* getMainCharacter();
    void switchDoorsetting();
    Level();
    Level(string levelString, int width, int height);
    Level(const Level& l);
    Level& operator=(const Level& l);
    // bool operator==(const Level& rhs) const;
    ~Level();
    Tile *getTile(int row, int col);
    vector<Portal* > portals;
    vector<Levelchanger* > levelChangers;
    //const Tile *getTile(int row, int col);
    void placeCharacter(Character *c, int row, int col);
    void printLevel();
    vector<vector<Tile *> > getTiles() const;
    void setPortalSettings();
    void generateTile();
    Door *getDoor() const;
    Switch *getSwitc() const;
    int getWidth() const;
    int getHeight() const;
    vector<Character *> getCharacters() const;
    vector<Character *> getCharactersSpecial();
    void getLevelChangers();
    vector<Character*> characters;
    vector<Character*> charactersSpecia;
};

#endif // LEVEL_H
