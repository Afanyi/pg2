#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "TerminalUI.h"
#include "GraphicalUI.h"


//using namespace std;

class DungeonCrawler{
    TerminalUI* terminal;
    GraphicalUI* ui;
    Level* level;
public:
    DungeonCrawler(GraphicalUI* ui);
    DungeonCrawler(TerminalUI* ui); // test
    DungeonCrawler(const DungeonCrawler& dungeonCrawler);
    DungeonCrawler& operator=(const DungeonCrawler& d);
    ~DungeonCrawler();
    bool turn();
    void move(Tile* t, Character* a, int crow, int ccol);
    GraphicalUI *getUi() const;
    Level *getLevel() const;
};
#endif // DUNGEONCRAWLER_H
