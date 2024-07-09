#include "DungeonCrawler.h"
#include "Character.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;
AbstractController *DungeonCrawler::getControllerFromString(const string &controllerType)
{
    if (controllerType == "StationaryController") {
        return new StationaryController();
    } else if (controllerType == "GuardController") {
        return new GuardController();
    } else if (controllerType == "AttackController") {
        return new AttackController(nullptr,nullptr,nullptr);
    } else {
        return ui;
    }
}

string DungeonCrawler::getControllerTypeName(AbstractController *controller)
{
    if (typeid(*controller) == typeid(StationaryController)) {
        return "StationaryController";
    } else if (typeid(*controller) == typeid(GuardController)) {
        return "GuardController";
    } else if (typeid(*controller) == typeid(AttackController)) {
        return "AttackController";
    }
    return "UnknownController";
}

void DungeonCrawler::loadFromFile(const std::string &filename)
{
    // getting position of current level
    int i = 0;
    for (auto l : levels) {
        if (l == level) {
            break;
        }
        i++;
    }

    AttackController* attacker = nullptr;
    Switch* switchObj = nullptr;
    std::string levelData = Level::getLevelString("level1.txt");
    Level* loadedLevel = new Level(levelData, 16, 13);
    bool doorOpened = false;

    // Map to convert strings back to enums
    std::map<std::string, CharacterTyp> stringToCharacterType = {
        {"mainPlayer", CharacterTyp::mainPlayer},
        {"Player", CharacterTyp::Player},
        {"NPC", CharacterTyp::NPC}
    };

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to load level");
    }

    std::string line, type, charTypeStr;
    int row = 0, col, stamina, strength, hitpoints, maxHp;
    while (std::getline(file, line)) {
        if (line == "LEVEL") {
            // Continue to read each line until "CHARACTER" is found
            while (std::getline(file, line) && line != "CHARACTER") {
                std::istringstream iss(line);
                col = 0;
                while (iss >> type) {
                    if (type == "/") {
                        doorOpened = true;
                    }
                    col++;
                }
                row++;
                if (row == 12){
                    break;
                }
            }
        } else if (line == "CHARACTER") {
            cout << " characters init "<<line << endl;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                iss >> type >> charTypeStr >> row >> col >> stamina >> strength >> hitpoints >> maxHp;
                cout << type << charTypeStr << row << col << stamina << strength << hitpoints << maxHp;

                CharacterTyp charType = stringToCharacterType[type];
                Character* character = new Character(charTypeStr, charType, stamina, strength);
                character->setHitpoints(hitpoints);

                std::string controllerType;
                iss >> controllerType;
                auto controller = getControllerFromString(controllerType);
                character->setTerminal(controller);
                if(character->getTerminal() == ui){
                    character->setCurrentLevel(level);
                }

                // Handle GuardController specific string
                if (controllerType == "GuardController") {
                    std::string guardString;
                    iss >> guardString;
                    auto controllerg = dynamic_cast<GuardController*>(controller);
                    controllerg->setGuardSring(guardString);
                }

                loadedLevel->placeCharacter(character, row, col);
                cout << endl;
            }
        }
    }

    switchObj = loadedLevel->getSwitc();
    if (doorOpened && switchObj) {
        switchObj->activate();
    }
    auto beforecharacters = loadedLevel->getCharactersSpecial();
    (*level) = (*loadedLevel);
    cout << "after asigment : " << level->getCharSize()<< endl;
    auto allcharacters = level->getCharactersSpecial();
    //level->switchDoorsetting();
    for (auto c : allcharacters) {
        auto contr = c->getTerminal();
        auto attackController = dynamic_cast<AttackController*>(contr);
        if (attackController != nullptr) {
            auto mainCharacter = level->getMainCharacter();
            attackController->setLevel(level);
            attackController->setZombie(c);
            attackController->setCharacter(mainCharacter);
            c->setTerminal(attackController);
            cout << "$$$$$$ do ur thing " << endl;
        }
    }
    levels[i] = level;
    //first levelchanger
    level->levelChangers[0]->attach(this);
    level->levelChangers[1]->attach(this);
    level->levelChangers[0]->setDestination(levels[(i-1)%4]->levelChangers[1]);
    levels[(i-1)%4]->levelChangers[1]->setDestination(level->levelChangers[0]);
    // second levelchanger
    level->levelChangers[1]->setDestination(levels[(i+1)%4]->levelChangers[0]);
    levels[(i+1)%4]->levelChangers[0]->setDestination(level->levelChangers[1]);

    std::cout << "Loaded level with " << loadedLevel->getCharacters().size() << " characters." << std::endl;
    delete loadedLevel;
    file.close();
}

void DungeonCrawler::saveToFile(const string &filename)
{

    // Map to convert enums to strings
    std::map<CharacterTyp, std::string> characterTypeToString = {
        {CharacterTyp::mainPlayer, "mainPlayer"},
        {CharacterTyp::Player, "Player"},
        {CharacterTyp::NPC, "NPC"}
    };

    // Map to convert strings back to enums
    std::map<std::string, CharacterTyp> stringToCharacterType = {
        {"mainPlayer",CharacterTyp::mainPlayer},
        {"Player",CharacterTyp::Player},
        {"NPC",CharacterTyp::NPC}
    };
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file to save level");
    }

    file << "LEVEL\n";  // Schreibe eine Kopfzeile, um den Anfang der Leveldaten zu kennzeichnen

    // Speichern der Tiles
    for (const auto& row : level->getTiles()) {
        for (const auto& tile : row) {
            if (tile->hasCharacter()) {
                Character* c = tile->getCharacter();
                if (c->getCharTyp() == CharacterTyp::NPC) {
                    file << "n" << " ";  // n für NPC
                } else {
                    file << "p" << " ";  // p für Player, angenommen
                }
            } else {
                file << tile->getTexture() << " ";
            }
        }
        file << "\n";  // Neues Zeile für jede Zeile der Karte
    }

    file << "CHARACTER\n";
    auto characters = level->getCharactersSpecial();
    for(auto& character : characters){
        std::string controllerType = getControllerTypeName(character->getTerminal());
        file << (std::string)characterTypeToString[character->getCharTyp()] << " "
             << character->getTyp() << " "
             << character->getTile()->getRow() << " "
             << character->getTile()->getColumn() << " "
             << character->getStamina() << " "
             << character->getStrength() << " "
             << character->getHitpoints() << " "
             << character->getMaxHP() << " "
             << controllerType << " ";
        // Special handling for GuardController
        if (controllerType == "GuardController") {
            GuardController* guard = dynamic_cast<GuardController*>(character->getTerminal());
            if (guard) { // Ensure dynamic_cast was successful
                file << guard->getGuardSring(); // Assuming getGuardString() returns the guard-specific string
            }
        }

        // Newline for the next character or end of this character's data
        file << "\n";
    }
    file.close();
}
GraphicalUI* DungeonCrawler::getUi() const {
    return ui;
}

Level* DungeonCrawler::getLevel() const {
    return level;
}

void DungeonCrawler::generatingLevels() {
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
}

void DungeonCrawler::notify(Active* active) {
    level = a->getCurrentLevel();
    int i = 0;
    for (auto l : levels) {
        if (l == level) {
            break;
        }
        i++;
    }
    i = i % 4;
    Levelchanger* lc = dynamic_cast<Levelchanger*>(active);
    if (lc) {
        level->characters.pop_back(); // Removing character from old level
        if (lc->getLevelchangerId() == level->levelChangers[0]->getLevelchangerId()) {
            //level = levels[(i - 1 + 4) % 4];
            level = levels[(i - 1) % 4];
        } else if (lc->getLevelchangerId() == level->levelChangers[1]->getLevelchangerId()) {
            level = levels[(i + 1) % 4];
        }

        if (a) {
            a->setCurrentLevel(level);
            if (find(level->characters.begin(), level->characters.end(), a) == level->characters.end()) {
                level->characters.push_back(a);
            }
        }
    }
}

void DungeonCrawler::levelChangerSetting() {
    if (level->getCharacters().empty()) {
        cerr << "Error: No characters in current level." << endl;
        return;
    }

    a = level->getCharacters()[0];

    if (!isLevelPresent(level)) {
        levels.push_back(level);
        cout << "Added new level. Current number of levels: " << levels.size() << endl;
    }
    int changerId = 0;
    for (unsigned int i = 0; i < levels.size(); i++) {
        unsigned int j = (i + 1) % levels.size();
        if (levels[i]->levelChangers.size() > 1 && levels[j]->levelChangers.size() > 1) {
            levels[i]->levelChangers[1]->setDestination(levels[j]->levelChangers[0]);
            levels[j]->levelChangers[0]->setDestination(levels[i]->levelChangers[1]);

            levels[i]->levelChangers[0]->setLevelchangerId(changerId);
            levels[i]->levelChangers[1]->setLevelchangerId(changerId + 1);

            levels[i]->levelChangers[0]->attach(this);
            levels[i]->levelChangers[1]->attach(this);

            actives.push_back(levels[i]->levelChangers[0]);
            actives.push_back(levels[i]->levelChangers[1]);
            changerId += 2;
        } else {
            cerr << "Error: Level changers not properly initialized for levels " << i << " or " << j << endl;
        }
    }

}

bool DungeonCrawler::isLevelPresent(Level* l)
{
    for(auto levelMacht : levels)
    {
        if(levelMacht == l )
        {
            return true;
        }
    }
    //return std::find(levels.begin(), levels.end(), l) != levels.end();
    return false;
}

DungeonCrawler::DungeonCrawler(GraphicalUI* ui) : ui(ui), level(ui->level) {
    generatingLevels();
    levelChangerSetting();
}

DungeonCrawler::DungeonCrawler():level(new Level()), ui(nullptr)
{
    generatingLevels();
    levelChangerSetting();
}

DungeonCrawler::DungeonCrawler(TerminalUI *ui) {
    auto* tmp = new Level();
    level = new Level(*tmp);
    delete tmp;
    ui->draw(level);

    tmp = new Level();
    *level = *tmp;
    ui->draw(level);
    delete tmp;
}

DungeonCrawler::DungeonCrawler(const DungeonCrawler &dungeonCrawler) : level(dungeonCrawler.level), ui(dungeonCrawler.ui) {}


DungeonCrawler& DungeonCrawler::operator=(const DungeonCrawler &d) {
    if (this != &d) {
        delete level;
        delete ui;
        ui = d.ui;
        level = d.level;
    }
    return *this;
}

DungeonCrawler::~DungeonCrawler() {
    for (auto cl : everyCharacters) {
        for (auto c : cl) {
            delete c;
        }
    }
    for (auto l : levels) {
        delete l;
    }
    delete level;
    delete ui;
}

void DungeonCrawler::move(Tile* t, Character* anyA, int crow, int ccol) {
    cout << "Main character move called" << endl;
    Tile* newTile = level->getTile(t->getRow() + crow, t->getColumn() + ccol);
    if (!(t->onLeave(newTile, anyA))) {
        // std::cout << "You can't move to this tile, choose another destination" << std::endl;
    } else if (anyA->getCharTyp() == CharacterTyp::NPC && newTile->getTexture() == "!") {
        // std::cout << "NPC can change level" << std::endl;
    } else {
        if (newTile->getTexture() == "!") {
            level = anyA->getCurrentLevel();
        }
        if (anyA->getCharTyp() != CharacterTyp::NPC) {
            if (anyA->getIsLootchestFound()) {
                isLootchestFound = true;
            }
        }
        t->moveTo(newTile, anyA);
    }
}

bool DungeonCrawler::turn() {
    // for (auto le : levels) {
    //     cout << le->getCharactersSpecial().size() << endl;
    // }
    a = level->getMainCharacter();
    // if (a) {
    //     level = a->getCurrentLevel();
    // }

    cout << "$$$ DungeonCrawler turn_init " << level->getCharacters().size() << endl;
    // cout << "$$$ DungeonCrawler new speciality turn_init " << level->getCharactersSpecial().size() << endl;
    // cout << "$$$ DungeonCrawler special method turn_init end " << level->getCharSize() << endl;

    a->setTerminal(ui);

    moveExecute(a);
    cout << "$$$ Move main character walking " << endl;

    level = a->getCurrentLevel();
    int count = 0;
    auto charactersSpecial = level->getCharactersSpecial();

    if (a->getTile()->getTexture() != "!") {
        for (auto anyChar : charactersSpecial) {
            if (anyChar->getCharTyp() == CharacterTyp::mainPlayer) {
                a = anyChar;
                //cout << "The texture is main char " << anyChar->getTyp() << endl;
            } else if (count == 0) {
                b = anyChar;
                currentLevelChars.push_back(anyChar);
                count++;
            } else {
                c = anyChar;
                currentLevelChars.push_back(anyChar);
            }
        }
        cout << "$$$ working untill heers " << endl;
        if (charactersSpecial.size() > 1) {
            for (auto currentLevelChar : currentLevelChars) {
                moveExecute(currentLevelChar);
            }
            // cout << "$$$ DungeonCrawler turn_init $$ middle  then new " << level->getCharSize() << endl;
            // cout << "$$$ DungeonCrawler new speciality  $$ middle" << level->getCharactersSpecial().size() << endl;
        }
        count = 0;
        for (auto anyChar : level->getCharactersSpecial()) {
            if (anyChar->getCharTyp() == CharacterTyp::mainPlayer) {
                //cout << "The texture is main char " << anyChar->getTyp() << endl;
            } else if (count == 0) {
                count++;
            }
        }
    }

    cout << "DungeonCrawler end turn " << level->getCharSize() << endl;
    srand(time(0));
    a->setCurrentLevel(level);

    currentLevelChars.clear();
    return true;
}

void DungeonCrawler::setUi(GraphicalUI *newUi)
{
    ui = newUi;
}

void DungeonCrawler::moveExecute(Character* anyA) {
    Tile* t = anyA->getTile();
    Input m = anyA->move();
    cout << " move exe getrow : " << endl;
    cout << " move exe getrow : " << t->getRow() << endl;
    if (m == Input::up) {
        move(t, anyA, -1, 0);
        anyA->setDirection(Direction::back);
    } else if (m == Input::upleft) {
        move(t, anyA, -1, -1);
        anyA->setDirection(Direction::left);
    } else if (m == Input::upright) {
        move(t, anyA, -1, 1);
        anyA->setDirection(Direction::right);
    } else if (m == Input::down) {
        move(t, anyA, 1, 0);
        anyA->setDirection(Direction::front);
    } else if (m == Input::downleft) {
        move(t, anyA, 1, -1);
        anyA->setDirection(Direction::left);
    } else if (m == Input::downright) {
        move(t, anyA, 1, 1);
        anyA->setDirection(Direction::right);
    } else if (m == Input::left) {
        move(t, anyA, 0, -1);
        anyA->setDirection(Direction::left);
    } else if (m == Input::right) {
        move(t, anyA, 0, 1);
        anyA->setDirection(Direction::right);
    } else if (m == Input::center) {
        switch (anyA->getDirection()) {
        case Direction::front:
            anyA->setDirection(Direction::back);
            break;
        case Direction::back:
            anyA->setDirection(Direction::front);
            break;
        case Direction::left:
            anyA->setDirection(Direction::right);
            break;
        case Direction::right:
            anyA->setDirection(Direction::left);
            break;
        }
    } else if (m == Input::exxit) {
        // Handle exit case if necessary
    }
}
