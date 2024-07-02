#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DungeonCrawler.h"
#include <iostream>
#include <QMessageBox>


void MainWindow::checkingEnd() // ende, tod finden loots
{
    if(characterc){
        if(characterc->getHitpoints() <= 0){ // tod des spieler
            QMessageBox::critical(this, "Game Over", "The main character's health has reached 0. Game Over!");

            // Perform necessary cleanup and exit the game
            QApplication::quit(); // This will close the application
        }
    }
    if(d){
        if(d->isLootchestFound){ // spilende
            QMessageBox::critical(this, " you win ", "you found the treasure. Game Over!");

            // Perform necessary cleanup and exit the game
            QApplication::quit(); // This will close the application
        }
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),d(nullptr),allCharacters(),characterLabels()

{
    setMinimumSize(1000,800);
    level = new Level();
    zombieCharacter3 = new Character("d",CharacterTyp::NPC);
    zombieCharacter1 = new Character("c",CharacterTyp::NPC);
    zombieCharacter = new Character("b",CharacterTyp::NPC);
    zombieController = new GuardController();
    zombieController1 = new GuardController();
    stationarycontroller =new StationaryController();

    zombieCharacter->setTerminal(zombieController);
    zombieController1->setGuardSring("22888822");
    zombieCharacter1->setTerminal(zombieController1);
    zombieCharacter3->setTerminal(stationarycontroller);


    allCharacters.push_back(characterc);
    allCharacters.push_back(zombieCharacter);
    allCharacters.push_back(zombieCharacter1);
    allCharacters.push_back(zombieCharacter3);

    level->placeCharacter(zombieCharacter,2,2);
    level->placeCharacter(zombieCharacter1,4,4);
    level->placeCharacter(zombieCharacter3,9,12);
    ui->setupUi(this);
    loadTextures();
    setWindowTitle("Dungeon Crawler");
    mainBack = new QLabel(this);

    mainBackground = QPixmap("./files/textures/bloody_frame.png");
    mainBackground.setDevicePixelRatio(1);
    mainBack->setPixmap(mainBackground);
    mainBack->setMinimumSize(this->width(),this->height()-40);
    mainBack->setScaledContents(true);
    setCentralWidget(mainBack);

    gridLayout = new QGridLayout(mainBack);
    gameFieldWidget = new QWidget(mainBack);
    tilesgridLayout = new QGridLayout(gameFieldWidget);

    controlWidget = new QWidget(mainBack);
    buttonGridLayout = new QGridLayout(controlWidget);

    // implementation StatusBar. Update after redraw
    statusbar = new QStatusBar(mainBack);
    statusbar->addWidget(new QLabel("character hp: "));
    mainCharacterHp = new QProgressBar(mainBack);
    statusbar->addWidget(mainCharacterHp);
    //statusbar->findChild<QProgressBar*>()->setValue(100);
    mainCharacterHp->setValue(100);
    mainCharacterHp->setStyleSheet(
            "QProgressBar::chunk {"
                                 "background-color: #00FF00;" /* Green color */
                                 "width: 20px;"
                             "}"
        );
    statusbar->setFixedSize(1000,40);
    statusbar->show();

    setStatusBar(statusbar);

    mainBack->raise();

}

MainWindow::~MainWindow()
{
    for(auto character : allCharacters){
        delete character;
    }
    for(auto label : characterLabels){
        delete label;
    }
    delete stationarycontroller;
    delete zombieCharacter3;
    delete zombieCharacter1;
    clearLayout(tilesgridLayout);
    clearLayout(buttonGridLayout);
    delete characterc;
    delete mainCharacterHp;
    delete characterAny;
    delete zombieCharacter;
    delete zombieController;
    delete zombieController1;
    delete level;
    delete gameFieldWidget;
    delete tilesgridLayout;
    delete buttonGridLayout;
    delete controlWidget;
    delete statusbar;
    delete mainBack;
    delete ui;
}

void MainWindow::draw(Level *level)
{
    std::cout << std::endl;
    std::cout << std::endl;

    int rad;    //random föoor
    int portalCount = 0;    // portal color
    //srand(time(0));
    for (int row = 0; row < level->getHeight(); ++row) {
        for (int col = 0; col < level->getWidth(); ++col) {
            QLabel* label = new QLabel("label");
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (texture == "$"){
                label->setPixmap(lootchest);
            }
            else if (texture == ".") {
                rad = rand()%5;
                if(rad == 0){
                    label->setPixmap(floor);
                }
                else if(rad == 1){
                    label->setPixmap(floor1);
                }
                else if(rad == 2){
                    label->setPixmap(floor2);
                }
                else if(rad == 3){
                    label->setPixmap(floor3);
                }
                else{
                    label->setPixmap(floor3);
                }
            } else if (texture == "#") {
                label->setPixmap(wall);
            } else if (texture == "_") {
                label->setPixmap(pit);
            } else if (texture == "o") {
                if(portalCount < 2){
                    label->setPixmap(portal);
                    portalCount++;
                }
                else if(portalCount >= 2 && portalCount < 4){
                    label->setPixmap(portal2);
                    portalCount++;
                }
                else{
                    label->setPixmap(portal1);
                    portalCount++;
                }
            } else if (texture == "<") {
                label->setPixmap(Ramp);
            } else if (texture == "X") {
                label->setPixmap(doorclose);
            } else if (texture == "/") {
                label->setPixmap(doorOpen);
            } else if (texture == "?") {
                label->setPixmap(switc);
            }
            else{
                label->setPixmap(levelChanger);
            }

            label->setFixedSize(42, 42);
            label->setScaledContents(true);
            tilesgridLayout->addWidget(label, row, col, Qt::AlignCenter);

            if (level->getTile(row, col)->hasCharacter()) {
                characterAny = level->getTile(row, col)->getCharacter();
                if(characterAny->getCharTyp() == CharacterTyp::NPC){

                    auto it = std::find(allCharacters.begin(),allCharacters.end(),characterAny);
                    if(it == allCharacters.end()){
                        allCharacters.push_back(characterAny);
                    }
                    QLabel *zombieLabel = new QLabel("");
                    //std::cout << " zombie found currentsize " <<characterLabels.size() << std::endl;
                    zombieLabel->setPixmap(zombie);
                    zombieLabel->setFixedSize(33, 33);
                    zombieLabel->setScaledContents(true);
                    tilesgridLayout->addWidget(zombieLabel, row, col, Qt::AlignCenter);
                    characterLabels.push_back(zombieLabel);
                    //std::cout << " zombie found  at " << zombieLabel<<  " size " <<characterLabels.size() << std::endl;
                }
                else{
                    if (c != nullptr) {
                        //delete c;
                    }
                    characterAny = level->getTile(row, col)->getCharacter();
                    //std::cout << " main character found " << std::endl;
                    c = new QLabel("");
                    characterc = characterAny;
                    allCharacters.at(0) = characterc;
                    if (characterc->getDirection() == Direction::front) {
                        c->setPixmap(character);
                    } else if (characterc->getDirection() == Direction::left) {
                        c->setPixmap(charLeft);
                    } else if (characterc->getDirection() == Direction::right) {
                        c->setPixmap(charRight);
                    } else if (characterc->getDirection() == Direction::back) {
                        c->setPixmap(charBack);
                    }
                    c->setFixedSize(33, 33);
                    c->setScaledContents(true);
                    tilesgridLayout->addWidget(c, row, col, Qt::AlignCenter);

                    if (texture == "_") {
                        c->lower(); // Lower the character label if the tile is a pit
                    }
                    if(texture == "<"){
                        c->raise();
                    }
                }
            }
        }
    }

    // Set spacing and margins for the game field layout
    tilesgridLayout->setSpacing(0);
    tilesgridLayout->setContentsMargins(0, 0, 0, 0);
    //gameFieldWidget->setMinimumSize(500, 336);
    gameFieldWidget->setMinimumSize(42*level->getWidth(), 42*level->getHeight());
    gridLayout->addWidget(gameFieldWidget, 0, 0, Qt::AlignCenter);

    // Create control buttons
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            MyButton* button = new MyButton(row, col);

            if (row == 0 && col == 0) {
                button->setIcon(QIcon(upleft));
            } else if (row == 0 && col == 1) {
                button->setIcon(QIcon(up));
            } else if (row == 0 && col == 2) {
                button->setIcon(QIcon(upright));
            } else if (row == 1 && col == 0) {
                button->setIcon(QIcon(left));
            } else if (row == 1 && col == 1) {
                button->setIcon(QIcon(center));
            } else if (row == 1 && col == 2) {
                button->setIcon(QIcon(right));
            } else if (row == 2 && col == 0) {
                button->setIcon(QIcon(downleft));
            } else if (row == 2 && col == 1) {
                button->setIcon(QIcon(down));
            } else if (row == 2 && col == 2) {
                button->setIcon(QIcon(downrigt));
            }

            button->setIconSize(QSize(42, 42));
            button->setFixedSize(42, 42);
            connect(button, &MyButton::clicked, button, &MyButton::buttonclicked);
            connect(button, &MyButton::slotbutton, this, &MainWindow::moveSlot);
            buttonGridLayout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }

    // Remove spacing and margins between buttons
    buttonGridLayout->setSpacing(0);
    buttonGridLayout->setContentsMargins(0, 0, 0, 0);

    controlWidget->setMinimumSize(139, 139);
    controlWidget->setBackgroundRole(QPalette::Dark);
    controlWidget->setLayout(buttonGridLayout);
    gridLayout->addWidget(controlWidget, 0, 1, Qt::AlignCenter);

    // std::cout << " in draw size of charactters in level " << level->getCharacters().size() << std::endl;
    // std::cout << " in draw size of charactersLabel in level " << characterLabels.size() << std::endl;
}

void MainWindow::moveSlot(int x, int y)
{
    std::cout << "Move to (" << x << ", " << y << ")\n";

    if (x == 0 && y == 0) {
        lastInput = Input::upleft;
    } else if (x == 0 && y == 1) {
        lastInput = Input::up;
    } else if (x == 0 && y == 2) {
        lastInput = Input::upright;
    } else if (x == 1 && y == 0) {
        lastInput = Input::left;
    } else if (x == 1 && y == 1) {
        lastInput = Input::center;
    } else if (x == 1 && y == 2) {
        lastInput = Input::right;
    } else if (x == 2 && y == 0) {
        lastInput = Input::downleft;
    } else if (x == 2 && y == 1) {
        lastInput = Input::down;
    } else if (x == 2 && y == 2) {
        lastInput = Input::downright;
    }
    //std::cout << " speciality size of character level : " <<level->getCharSize() << std::endl;
    //std::cout << "alpha $$$$ speciality size of character level : " <<level->getCharSize() << std::endl;
    if(characterc){
        characterc->setCurrentLevel(level);
    }
    std::cout << "alpha before turn $$$$ speciality size of character level : " <<level->getCharSize() << std::endl;
    d->turn();
    std::cout << "alpha $$$$ speciality size of character level : " <<level->getCharSize() << std::endl;
    checkingEnd();
    redraw(level);
    level->removeDeadFigurs();
    //std::cout << " working untill here " << std::endl;
    //std::cout << " size of character level : " <<level->getCharacters().size() << std::endl;
    if(characterc){
        if(level != characterc->getCurrentLevel()){
            //std::cout << "hii from character size : " << allCharacters.size()<< std::endl;
            if(allCharacters.size()>1){
                for(int i = allCharacters.size()-1;i>=0;i--){
                    if(allCharacters[i]->getCharTyp() == CharacterTyp::NPC){
                        //delete allCharacters[i];
                        //allCharacters.erase(allCharacters.begin() + i);
                        allCharacters.pop_back();
                        //std::cout << "hii from character "<< i << std::endl;

                    }
                }
            }
            //std::cout << "hii from character size : " << allCharacters.size()<< std::endl;
            //allCharacters.clear();
            //std::cout << " delete working "<< characterLabels.size() << std::endl;
            if(characterLabels.size()>0){
                for(int i= characterLabels.size()-1;i<0;i--){
                    delete characterLabels[i];
                    characterLabels.erase(characterLabels.begin()+i);
                }
            }
            characterLabels.clear();
            //std::cout << " delete working " << std::endl;
            //std::cout << "$$$$ speciality size of character level : " <<level->getCharSize() << std::endl;

            clearLayout(tilesgridLayout);
            clearLayout(buttonGridLayout);

            delete tilesgridLayout;
            delete buttonGridLayout;
            delete gameFieldWidget;
            delete controlWidget;

            delete gridLayout;

            gridLayout = nullptr;
            gameFieldWidget = nullptr;
            tilesgridLayout = nullptr;
            controlWidget = nullptr;
            buttonGridLayout = nullptr;

            // Create new layouts and widgets
            gridLayout = new QGridLayout(mainBack);

            gameFieldWidget = new QWidget(mainBack);
            tilesgridLayout = new QGridLayout(gameFieldWidget);

            controlWidget = new QWidget(mainBack);
            buttonGridLayout = new QGridLayout(controlWidget);

            // gridLayout->addWidget(gameFieldWidget, 0, 0, Qt::AlignCenter);
            // gridLayout->addWidget(controlWidget, 0, 1, Qt::AlignCenter);
            //std::cout << " working untill here  draw again" << std::endl;
            //std::cout << "$$$$ size of char end moveslot "<< allCharacters.size() << " label  " <<characterLabels.size()<< std::endl;
            // std::cout << "$$$$ speciality size of character level : " <<level->getCharSize() << std::endl;
            level = characterc->getCurrentLevel();
            //std::cout << " size of char end moveslot "<< allCharacters.size() << " label  " <<characterLabels.size()<< std::endl;
            //std::cout << " size of character level : " <<level->getCharSize() << std::endl;

            draw(level);

        }
    }

}

void MainWindow::redraw(Level *level)
{
    int lNummer=0;
    for (int row = 0; row < level->getHeight(); ++row)
    {
        for (int col = 0; col < level->getWidth(); ++col)
        {
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (level->getTile(row, col)->hasCharacter()) {
                characterAny = level->getTile(row, col)->getCharacter();
                std::cout <<" size of label : " << characterLabels.size() << std::endl;
                if(characterAny->getCharTyp() == CharacterTyp::NPC){
                    if(characterLabels[lNummer] != nullptr){
                        //QLabel* lb = characterLabels[lNummer];
                        std::cout <<" hp : " <<characterAny->getHitpoints() << std::endl;
                        std::cout << "$$$ remeoval " << std::endl;
                        delete characterLabels[lNummer];
                    }
                    characterLabels[lNummer] = new QLabel("");
                    if(lNummer == 0){
                        for(auto characterLabel : characterLabels){
                            characterLabel->setPixmap(dead);
                        }
                    }
                    if(characterAny->getHitpoints() <= 0){
                        characterLabels[lNummer]->setPixmap(dead);
                    }
                    else{
                        characterLabels[lNummer]->setPixmap(zombie);
                    }
                    characterLabels[lNummer]->setFixedSize(33, 33);
                    characterLabels[lNummer]->setScaledContents(true);
                    tilesgridLayout->addWidget(characterLabels[lNummer], row, col, Qt::AlignCenter);
                    lNummer++;
                }
                else{
                    if (c != nullptr) {
                        delete c;
                    }
                    c = new QLabel("");
                    characterc = characterAny;
                    if (characterc->getDirection() == Direction::front) {
                        c->setPixmap(character);
                    } else if (characterc->getDirection() == Direction::left) {
                        c->setPixmap(charLeft);
                    } else if (characterc->getDirection() == Direction::right) {
                        c->setPixmap(charRight);
                    } else if (characterc->getDirection() == Direction::back) {
                        c->setPixmap(charBack);
                    }
                    c->setFixedSize(33, 33);
                    c->setScaledContents(true);
                    tilesgridLayout->addWidget(c, row, col, Qt::AlignCenter);

                    if (texture == "_") {
                        c->lower(); // Lower the character label if the tile is a pit
                    }
                    if(texture == "<"){
                        c->raise();
                    }
                }
                if(texture == "?"){
                    //Door* d = level->getDoor();
                    vector<Door*> doors = level->doors;
                    for(auto d : doors){
                        QString texture = QString::fromStdString(d->getTexture());
                        //QLabel* label = new QLabel("label");
                        QLabel* label = static_cast<QLabel*>(tilesgridLayout->itemAtPosition(d->getRow(),d->getColumn())->widget());
                        if(label){
                            tilesgridLayout->removeWidget(label);
                            delete label;
                        }
                        label = new QLabel("label");
                        if (texture == "X") {
                            label->setPixmap(doorclose);
                        } else if (texture == "/") {
                            label->setPixmap(doorOpen);
                        }
                        label->setFixedSize(42, 42);
                        label->setScaledContents(true);
                        tilesgridLayout->addWidget(label, d->getRow(), d->getColumn(), Qt::AlignCenter);
                    }
                }
            }
        }
    }
    // Update Hp for StatusBar

    if(characterc){
        mainCharacterHp->setValue(100*characterc->getHitpoints()/(characterc->getMaxHP()));
    }
    std::cout << std::endl;
    // std::cout << " in draw size of charactters in level " << level->getCharacters().size() << std::endl;
    // std::cout << " in draw size of charactersLabel in level " << characterLabels.size() << std::endl;
    std::cout << std::endl;
}

Input MainWindow::getLastInput() const
{
    return lastInput;
}

void MainWindow::setLastInput(Input newLastInput)
{
    lastInput = newLastInput;
}


void MainWindow::clearLayout(QLayout *layout)
{
    if (layout != nullptr) {
        // Loop through all items in the layout
        while (layout->count() > 0) {
            QLayoutItem* item = layout->takeAt(0);
            if (item) {
                QWidget* widget = item->widget();
                if (widget) {
                    layout->removeWidget(widget);
                    delete widget; // Delete the widget
                }
                delete item; // Delete the layout item
            }
        }
    }
}

void MainWindow::loadTextures()
{
    lootchest = QPixmap("./files/textures/chest.png");
    floor = QPixmap("./files/textures/floor/floor1.png");
    floor1 = QPixmap("./files/textures/floor/floor2.png");
    floor2 = QPixmap("./files/textures/floor/floor3.png");
    floor3 = QPixmap("./files/textures/floor/floor4.png");
    floor4 = QPixmap("./files/textures/floor/floor5.png");
    wall = QPixmap("./files/textures/wall/wall1.png");
    portal = QPixmap("./files/textures/portal/portal1.png");
    portal1 = QPixmap("./files/textures/portal/portal2.png");
    portal2 = QPixmap("./files/textures/portal/portal3.png");
    pit = QPixmap("./files/textures/pit.png");
    Ramp = QPixmap("./files/textures/ramp.png");
    doorOpen = QPixmap("./files/textures/doors/door1.png");
    doorclose = QPixmap("./files/textures/doors/door2.png");
    switc = QPixmap("./files/textures/switch.png");
    levelChanger = QPixmap("./files/textures/levelchanger.png");

    up = QPixmap("./files/textures/arrows/arrow_up.png");
    upleft = QPixmap("./files/textures/arrows/arrow_up_left.png");
    upright = QPixmap("./files/textures/arrows/arrow_up_right.png");
    down = QPixmap("./files/textures/arrows/arrow_down.png");
    downleft = QPixmap("./files/textures/arrows/arrow_down_left.png");
    downrigt = QPixmap("./files/textures/arrows/arrow_down_right.png");
    left = QPixmap("./files/textures/arrows/arrow_left.png");
    right = QPixmap("./files/textures/arrows/arrow_right.png");
    center = QPixmap("./files/textures/arrows/arrow_skip.png");

    character = QPixmap("./files/textures/char/front/char_front_1.png");
    zombie = QPixmap("./files/textures/zombie/zombie_left.png");
    zombieRight = QPixmap("./files/textures/zombie/zombie_right.png");
    charBack = QPixmap("./files/textures/char/back/char_back_1.png");
    charLeft = QPixmap("./files/textures/char/left/char_left_1.png");
    charRight = QPixmap("./files/textures/char/right/char_right_1.png");
}

// void MainWindow::resizeEvent(QResizeEvent *event)
// {
//     QMainWindow::resizeEvent(event);
//     mainBack->setFixedSize(event->size());
//     mainBack->setPixmap(mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
//     mainBackground = mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     this->resize(event->size());

// }
