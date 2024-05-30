#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "TerminalUI.h"


//using namespace std;

class DungeonCrawler{
    TerminalUI* terminal;
    Level* level;
public:
    DungeonCrawler();
    DungeonCrawler(const DungeonCrawler& dungeonCrawler);
    DungeonCrawler& operator=(const DungeonCrawler& d);
    ~DungeonCrawler();
    bool turn();
    pair<Tile*,Character*> Teleportation(Tile* t,Tile *newTile, Character* a,int crow,int ccol);
    void move(Tile* t, Character* a, int crow, int ccol);
};
#endif // DUNGEONCRAWLER_H
