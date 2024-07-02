#include "DungeonCrawler.h"
#include "Character.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;
GraphicalUI *DungeonCrawler::getUi() const
{
    return ui;
}

Level *DungeonCrawler::getLevel() const
{
    return level;
}

void DungeonCrawler::generatingLevels()
{

    string l11 = Level::getLevelString("level2.txt");

    string l22 = Level::getLevelString("level3.txt");

    string l33 = Level::getLevelString("level4.txt");

    controller = new GuardController();
    //level = new Level();
    level1 = new Level(l11,16,13);
    charactersl0.push_back(nullptr);
    charactersl0.push_back(nullptr);
    charactersl0[1] = new Character("bbbb",CharacterTyp::NPC);
    charactersl0[0] = new Character("cccc",CharacterTyp::NPC);

    level2 = new Level(l22,16,13);
    charactersl1.push_back(nullptr);
    charactersl1.push_back(nullptr);
    charactersl1[1] = new Character("bbbb",CharacterTyp::NPC);
    charactersl1[0] = new Character("cccc",CharacterTyp::NPC);

    level3 = new Level(l33,16,13);
    charactersl2.push_back(nullptr);
    charactersl2.push_back(nullptr);
    charactersl2[1] = new Character("bbbb",CharacterTyp::NPC);
    charactersl2[0] = new Character("cccc",CharacterTyp::NPC);

    charactersl0[0]->setTerminal(controller);
    charactersl1[0]->setTerminal(controller);
    charactersl2[0]->setTerminal(controller);

    controller->setGuardSring("22888822");
    charactersl0[1]->setTerminal(controller);
    charactersl1[1]->setTerminal(controller);
    charactersl2[1]->setTerminal(controller);

    level1->placeCharacter(charactersl0[0],2,2);
    level1->placeCharacter(charactersl0[1],4,4);

    level2->placeCharacter(charactersl1[0],2,2);
    level2->placeCharacter(charactersl1[1],4,4);

    level3->placeCharacter(charactersl2[0],2,2);
    level3->placeCharacter(charactersl2[1],4,4);

    everyCharacters.push_back(charactersl0);
    everyCharacters.push_back(charactersl1);
    everyCharacters.push_back(charactersl2);

    //levels.push_back(level);
    levels.push_back(level1);
    levels.push_back(level2);
    levels.push_back(level3);

}

void DungeonCrawler::notify(Active* active)
{

    level = a->getCurrentLevel();
    //cout << " in dugeoncrawler " << level->getCharacters().size() << endl;
    int i = 0;
    for(auto l : levels){
        if(l == level){
            break;
        }
        i++;
    }

    i = i%4;


    Levelchanger* lc = dynamic_cast<Levelchanger*>(active);
    if(lc){
        if(lc->getLevelchangerId() == level->levelChangers[0]->getLevelchangerId()){
            level->characters.pop_back(); // removing character form old level
            level = levels[(i-1)%4];
            i = (i-1)%4;  // 0nly to debug
            if(a){
                a->setCurrentLevel(level);
                auto it = find(level->characters.begin(),level->characters.end(),a);
                if(it == level->characters.end()){
                    level->characters.push_back(a);
                }
            }
        }
        else if(lc->getLevelchangerId() == level->levelChangers[1]->getLevelchangerId()){
            //cout << " second : " << lc  <<endl;
            level->characters.pop_back();
            level = levels[(i+1)%4];
            i = (i+1)%4;    // 0nly to debug
            if(a){
                a->setCurrentLevel(level);
                auto it = find(level->characters.begin(),level->characters.end(),a);
                if(it == level->characters.end()){
                    level->characters.push_back(a);
                }
            }
        }
    }
    //cout << "$$$ in dugeoncrawler ende " << level->getCharSize() << endl;

}



void DungeonCrawler::levelChangerSetting()
{
    // Ensure we have at least one character
    if (level->getCharacters().empty()) {
        cerr << "Error: No characters in current level." << endl;
        return;
    }

    a = level->getCharacters()[0];

    // Check if the level is already present
    if (!isLevelPresent(level)) {
        levels.push_back(level);
        cout << "Added new level. Current number of levels: " << levels.size() << endl;

        // Set up level changers
        int changerId = 0;
        for (unsigned int i = 0; i < levels.size(); i++) {
            unsigned int j = (i + 1) % levels.size(); // Adjust to the actual number of levels
            if (levels[i]->levelChangers.size() > 1 && levels[j]->levelChangers.size() > 1) {
                levels[i]->levelChangers[1]->setDestination(levels[j]->levelChangers[0]);
                levels[j]->levelChangers[0]->setDestination(levels[i]->levelChangers[1]);

                levels[i]->levelChangers[0]->setLevelchangerId(changerId);
                levels[i]->levelChangers[1]->setLevelchangerId((changerId+1));

                //cout << " first active at initialisation  : " << levels[i]->levelChangers[0]->getLevelchangerId() << endl;
                //cout << " second active at initialisation : " << levels[i]->levelChangers[1]->getLevelchangerId() << endl;

                levels[i]->levelChangers[0]->attach(this);  //attaching passive element dungeoncrawler
                levels[i]->levelChangers[1]->attach(this);

                actives.push_back(levels[i]->levelChangers[0]);
                actives.push_back(levels[i]->levelChangers[1]);
                changerId += 2;

                //cout << "Set level changer from level " << i << " to level " << j << endl;
            } else {
                cerr << "Error: Level changers not properly initialized for levels " << i << " or " << j << endl;
            }
        }
    } else {
        cout << "Level already present. No changes made." << endl;
    }
}

bool DungeonCrawler::isLevelPresent(Level* l)
{
    for(auto levelMacht : levels){
        if(levelMacht == l ){
            return true;
        }
    }
    //return std::find(levels.begin(), levels.end(), l) != levels.end();
    return false;
}

DungeonCrawler::DungeonCrawler(GraphicalUI* ui): ui(ui),level(ui->level),currentLevelChars()
{
    generatingLevels();
    levelChangerSetting();
}

DungeonCrawler::DungeonCrawler(TerminalUI *ui)
{
    auto* tmp = new Level();
    level = new Level(*tmp); // currentLevel is attribute of DungeonCrawler
    delete tmp;
    ui->draw(level);
    // Test assignment
    tmp = new Level();
    *level = *tmp;
    ui->draw(level);
    delete tmp;
}

DungeonCrawler::DungeonCrawler(const DungeonCrawler &dungeonCrawler): level(dungeonCrawler.level),
    ui(dungeonCrawler.ui)
{


}

DungeonCrawler &DungeonCrawler::operator=(const DungeonCrawler &d)
{
    delete level;
    delete ui;
    this->ui = d.ui;
    this->level = d.level;
    return *this;
}

DungeonCrawler::~DungeonCrawler()
{
    for(auto cl : everyCharacters){
        for(auto c : cl){
            delete c;
        }
    }
    for(auto l : levels){
        delete l;
    }
    delete level;
    //delete terminal;
    delete ui;
}
// could have simplified the move function but teleportation is not working as expected


void DungeonCrawler::move(Tile *t, Character *anyA, int crow, int ccol)
{

    Tile* newTile;
    newTile = level->getTile(t->getRow()+crow,t->getColumn()+ccol);
    //cout << " hi " << endl;
    cout << "main character move called "<< endl;
    //if(anyA->getIsDead());
    if(!(t->onLeave(newTile,anyA))){
        //std::cout << "you can move on this tile choose another ziel" << std::endl;
    }
    else if(anyA->getCharTyp() == CharacterTyp::NPC && newTile->getTexture() == "!"){
        //std::cout << "npc can change level" << std::endl;
    }
    else{
        cout << "main character move called "<< endl;
        if(newTile->getTexture() == "!"){
            level = anyA->getCurrentLevel();
        }
        if(anyA->getCharTyp() != CharacterTyp::NPC){
            if(anyA->getIsLootchestFound()){
                isLootchestFound = true;
            }
        }

        t->moveTo(newTile,anyA);
    }

}

bool DungeonCrawler::turn()
{
    for(auto le : levels){
        cout << le->getCharactersSpecial().size() << endl;
    }
    a = level->getMainCharacter();
    if(a){
        level = a->getCurrentLevel();
    }
    // creating characters
    cout << "$$$ in dugeoncrawler turn_init " << level->getCharacters().size() << endl;
    cout << "$$$ in dugeoncrawler new speciality turn_init " << level->getCharactersSpecial().size() << endl;
    cout << "$$$ in dugeoncrawler special method turn_init ende " << level->getCharSize() << endl;


    // setting character terminal attribute
    a->setTerminal(ui);

    cout << "$$$ move main character walking "<< endl;

    moveExecute(a);
    cout << "$$$ move main character walking "<< endl;
    level = a->getCurrentLevel();
    int count = 0;
    auto charactersSpecial = level->getCharactersSpecial();
    if(a->getTile()->getTexture() != "!"){
        for(auto anyChar : charactersSpecial){
            if(anyChar->getCharTyp() == CharacterTyp::mainPlayer){
                a = anyChar;
                cout << "the texture is main char " << anyChar->getTyp() << endl;

            }
            else if(count == 0){
                cout << "the texture of b is " << anyChar->getTyp() << endl;
                b = anyChar;
                currentLevelChars.push_back(anyChar);
                count++;
            }
            else{
                cout << "the texture of b is " << anyChar->getTyp() << endl;
                c = anyChar;
                currentLevelChars.push_back(anyChar);

            }
        }
        if(charactersSpecial.size()>1){
            for(auto currentLevelChar : currentLevelChars){
                if(currentLevelChar){
                    moveExecute(currentLevelChar);
                }
            }
            cout << "$$$ in dugeoncrawler turn_init $$ middle  then new " << level->getCharSize() << endl;
            cout << "$$$ in dugeoncrawler new speciality  $$ middle" << level->getCharactersSpecial().size() << endl;
        }
        count = 0;
        for(auto anyChar : level->getCharactersSpecial()){
            if(anyChar->getCharTyp() == CharacterTyp::mainPlayer){
                cout << "the texture is main char " << anyChar->getTyp() << endl;
            }
            else if(count == 0){
                cout << "the texture of b is " << anyChar->getTyp() << endl;
                count++;
            }
            else{
                cout << "the texture of b is " << anyChar->getTyp() << endl;
                //c = anyChar;
            }
        }

    }

    cout << " in dugeoncrawler end turn  " << level->getCharSize() << endl;
    srand(time(0));
    a->setCurrentLevel(level);

    while(!currentLevelChars.empty()){
        currentLevelChars.pop_back();
    }

    return true;
}

void DungeonCrawler::moveExecute(Character* anyA)
{

    Tile* t = anyA->getTile();
    //std::cout << t->getRow() << " zombie " << t->getColumn() << std::endl;
    Input m = anyA->move();
    if(m==Input::up){
        move(t,anyA,-1,0);
        anyA->setDirection(Direction::back);
    }
    else if(m==Input::upleft){
        move(t,anyA,-1,-1);
        anyA->setDirection(Direction::left);
    }
    else if(m==Input::upright){
        move(t,anyA,-1,1);
        anyA->setDirection(Direction::right);
    }
    else if(m==Input::down){
        move(t,anyA,1,0);
        anyA->setDirection(Direction::front);
    }
    else if(m==Input::downleft){
        move(t,anyA,1,-1);
        anyA->setDirection(Direction::left);
    }
    else if(m==Input::downright){
        move(t,anyA,1,1);
        anyA->setDirection(Direction::right);
    }
    else if(m== Input::left){
        move(t,anyA,0,-1);
        anyA->setDirection(Direction::left);
    }
    else if(m== Input::right){
        move(t,anyA,0,1);
        anyA->setDirection(Direction::right);
    }
    else if(m==Input::center){
        if(anyA->getDirection() == Direction::front){
            anyA->setDirection(Direction::back);
        }
        else if(anyA->getDirection() == Direction::back){
            anyA->setDirection(Direction::front);
        }
        else if(anyA->getDirection() == Direction::left){
            anyA->setDirection(Direction::right);
        }
        else if(anyA->getDirection() == Direction::right){
            anyA->setDirection(Direction::left);
        }
    }
    else if(m==Input::exxit){
        //return false;
    }
    //std::cout << a->getTile()->getRow() << "  " << a->getTile()->getColumn() << std::endl;
}
