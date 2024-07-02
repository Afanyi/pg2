#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H
#include "Passive.h"
#include "TerminalUI.h"
#include "GraphicalUI.h"
#include <vector>
#include "GuardController.h"
#include "List_impl.h"


//using namespace std;

class DungeonCrawler : public Passive{
    //TerminalUI* terminal;
    Character* a;
    Character* b;
    Character* c;
    GraphicalUI* ui;
    Level* level;
    Level* level1;
    Level* level2;
    Level* level3;
public:
    bool isLootchestFound = false;
    List<Character*> currentLevelChars;
    List<List<Character*>> everyCharacters;
    List<Character*> charactersl0;
    List<Character*> charactersl1;
    List<Character*> charactersl2;
    List<Character*> charactersl3;

    GuardController* controller = new GuardController;

    void moveExecute(Character* );
    List<Active*> actives;
    void levelChangerSetting();
    bool isLevelPresent(Level* l);
    List<Level*> levels;
    DungeonCrawler(GraphicalUI* ui);
    DungeonCrawler(TerminalUI* ui); // test
    DungeonCrawler(const DungeonCrawler& dungeonCrawler);
    DungeonCrawler& operator=(const DungeonCrawler& d);
    ~DungeonCrawler();
    bool turn();
    void move(Tile* t, Character* , int crow, int ccol);
    GraphicalUI *getUi() const;
    Level *getLevel() const;
    void generatingLevels();
    void notify(Active* active) override;
};
#endif // DUNGEONCRAWLER_H
