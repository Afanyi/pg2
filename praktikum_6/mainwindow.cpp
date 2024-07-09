#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DungeonCrawler.h"
#include <iostream>
#include <QMessageBox>

void MainWindow::loadGame()
{
    clearLevelData();
    d->loadFromFile("state1.txt");
    level = d->getLevel();
    std::cout << "size of level " <<level->getCharSize() << std::endl;;
    //level = characterc->getCurrentLevel();
    draw(level);
}

void MainWindow::checkingEnd() {
    if (characterc && characterc->getHitpoints() <= 0) {
        QMessageBox::critical(this, "Game Over", "The main character's health has reached 0. Game Over!");
        QApplication::quit(); // This will close the application
    }
    if (d && d->isLootchestFound) {
        QMessageBox::information(this, "You Win", "You found the treasure. Game Over!");
        QApplication::quit(); // This will close the application
    }
}

void MainWindow::addingnpcs()
{
    attacker = new Character("d", CharacterTyp::NPC,10,10);
    zombieCharacter1 = new Character("c", CharacterTyp::NPC);
    zombieCharacter = new Character("b", CharacterTyp::NPC);
    zombieController = new GuardController();
    zombieController1 = new GuardController();

    zombieCharacter->setTerminal(zombieController);
    zombieController1->setGuardSring("22888822");
    zombieCharacter1->setTerminal(zombieController1);
    characterc = level->getMainCharacter();
    attackerCharacter = new AttackController(level, characterc, attacker);
    attacker->setTerminal(attackerCharacter);

    allCharacters = {characterc, zombieCharacter, zombieCharacter1,attacker};

    level->placeCharacter(zombieCharacter, 2, 2);
    level->placeCharacter(zombieCharacter1, 4, 4);
    level->placeCharacter(attacker, 9, 12);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , d(nullptr)
    , characterc(nullptr)
    , characterAny(nullptr)
    , c(nullptr)
    , gridLayout(nullptr)
    , tilesgridLayout(nullptr)
    , buttonGridLayout(nullptr)
    , gameFieldWidget(nullptr)
    , controlWidget(nullptr)
{
    setMinimumSize(1000, 800);
    //level = new Level();

    ui->setupUi(this);
    loadTextures();
    setWindowTitle("Dungeon Crawler");

    mainBack = new QLabel(this);
    mainBackground = QPixmap("./files/textures/bloody_frame.png");
    mainBackground.setDevicePixelRatio(1);
    mainBack->setPixmap(mainBackground);
    mainBack->setMinimumSize(this->width(), this->height() - 80);
    mainBack->setScaledContents(true);
    setCentralWidget(mainBack);

    gridLayout = new QGridLayout(mainBack);
    gameFieldWidget = new QWidget(mainBack);
    tilesgridLayout = new QGridLayout(gameFieldWidget);
    controlWidget = new QWidget(mainBack);
    buttonGridLayout = new QGridLayout(controlWidget);

    statusbar = new QStatusBar(mainBack);
    statusbar->addWidget(new QLabel("Character HP: "));
    mainCharacterHp = new QProgressBar(mainBack);
    statusbar->addWidget(mainCharacterHp);
    mainCharacterHp->setValue(100);
    mainCharacterHp->setStyleSheet(
        "QProgressBar::chunk {"
        "background-color: #00FF00;" /* Green color */
        "width: 20px;"
        "}"
        );
    statusbar->setFixedSize(1000, 40);
    statusbar->show();
    setStatusBar(statusbar);
    // d->saveToFile("state1.txt");
    // d->loadFromFile("state1.txt");

    QAction* saveAction = new QAction("Save Game", this);
    //connect(saveAction, &QAction::triggered, this, [this]() { saveGameState("savegame.txt"); });
    connect(saveAction, &QAction::triggered, this, [this]() { d->saveToFile("state1.txt"); });

    QAction* loadAction = new QAction("Load Game", this);
    //connect(loadAction, &QAction::triggered, this, [this]() { loadGameState("savegame.txt"); });
    connect(loadAction, &QAction::triggered, this, [this]() { loadGame(); });

    QMenu* fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(saveAction);
    fileMenu->addAction(loadAction);

    saveAction->setShortcut(QKeySequence("Ctrl+S"));
    loadAction->setShortcut(QKeySequence("Ctrl+L"));
}

MainWindow::~MainWindow() {
    qDeleteAll(allCharacters);
    qDeleteAll(characterLabels);
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

void MainWindow::draw(Level *level) {
    int portalCount = 0;
    srand(time(0));
    for (int row = 0; row < level->getHeight(); ++row) {
        for (int col = 0; col < level->getWidth(); ++col) {
            QLabel* label = new QLabel("label");
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (texture == "$") {
                label->setPixmap(lootchest);
            } else if (texture == ".") {
                int rad = rand() % 5;
                label->setPixmap(rad == 0 ? floor : rad == 1 ? floor1 : rad == 2 ? floor2 : rad == 3 ? floor3 : floor4);
            } else if (texture == "#") {
                label->setPixmap(wall);
            } else if (texture == "_") {
                label->setPixmap(pit);
            } else if (texture == "o") {
                label->setPixmap(portalCount < 2 ? portal : portalCount < 4 ? portal2 : portal1);
                portalCount++;
            } else if (texture == "<") {
                label->setPixmap(Ramp);
            } else if (texture == "X") {
                label->setPixmap(doorclose);
            } else if (texture == "/") {
                label->setPixmap(doorOpen);
            } else if (texture == "?") {
                label->setPixmap(switc);
            } else {
                label->setPixmap(levelChanger);
            }

            label->setFixedSize(42, 42);
            label->setScaledContents(true);
            tilesgridLayout->addWidget(label, row, col, Qt::AlignCenter);

            if (level->getTile(row, col)->hasCharacter()) {
                characterAny = level->getTile(row, col)->getCharacter();
                if (characterAny->getCharTyp() == CharacterTyp::NPC) {
                    if (std::find(allCharacters.begin(), allCharacters.end(), characterAny) == allCharacters.end()) {
                        allCharacters.push_back(characterAny);
                    }
                    QLabel *zombieLabel = new QLabel("");
                    zombieLabel->setPixmap(zombie);
                    zombieLabel->setFixedSize(33, 33);
                    zombieLabel->setScaledContents(true);
                    tilesgridLayout->addWidget(zombieLabel, row, col, Qt::AlignCenter);
                    characterLabels.push_back(zombieLabel);
                } else {
                    if (c != nullptr) {
                        //delete c;
                    }
                    c = new QLabel("");
                    characterc = characterAny;
                    allCharacters[0] = characterc;
                    QPixmap pixmap = characterc->getDirection() == Direction::front ? character :
                                         characterc->getDirection() == Direction::left ? charLeft :
                                         characterc->getDirection() == Direction::right ? charRight : charBack;
                    c->setPixmap(pixmap);
                    c->setFixedSize(33, 33);
                    c->setScaledContents(true);
                    tilesgridLayout->addWidget(c, row, col, Qt::AlignCenter);

                    if (texture == "_") {
                        c->lower(); // Lower the character label if the tile is a pit
                    }
                    if (texture == "<") {
                        c->raise();
                    }
                }
            }
        }
    }

    tilesgridLayout->setSpacing(0);
    tilesgridLayout->setContentsMargins(0, 0, 0, 0);
    gameFieldWidget->setMinimumSize(42 * level->getWidth(), 42 * level->getHeight());
    gridLayout->addWidget(gameFieldWidget, 0, 0, Qt::AlignCenter);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            MyButton* button = new MyButton(row, col);
            QPixmap icon = row == 0 && col == 0 ? upleft : row == 0 && col == 1 ? up : row == 0 && col == 2 ? upright :
                                                           row == 1 && col == 0 ? left : row == 1 && col == 1 ? center : row == 1 && col == 2 ? right :
                                                           row == 2 && col == 0 ? downleft : row == 2 && col == 1 ? down : downrigt;
            button->setIcon(QIcon(icon));
            button->setIconSize(QSize(42, 42));
            button->setFixedSize(42, 42);
            connect(button, &MyButton::clicked, button, &MyButton::buttonclicked);
            connect(button, &MyButton::slotbutton, this, &MainWindow::moveSlot);
            buttonGridLayout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }

    buttonGridLayout->setSpacing(0);
    buttonGridLayout->setContentsMargins(0, 0, 0, 0);

    controlWidget->setMinimumSize(139, 139);
    controlWidget->setBackgroundRole(QPalette::Dark);
    controlWidget->setLayout(buttonGridLayout);
    gridLayout->addWidget(controlWidget, 0, 1, Qt::AlignCenter);
}

void MainWindow::moveSlot(int x, int y) {
    static const Input inputs[3][3] = {
        {Input::upleft, Input::up, Input::upright},
        {Input::left, Input::center, Input::right},
        {Input::downleft, Input::down, Input::downright}
    };

    std::cout << "Move to (" << x << ", " << y << ")\n";
    lastInput = inputs[x][y];

    if (characterc) {
        characterc->setCurrentLevel(level);
    }

    d->turn();
    if (characterc) {
        mainCharacterHp->setValue(100 * characterc->getHitpoints() / characterc->getMaxHP());
    }
    checkingEnd();
    redraw(level);
    level->removeDeadFigurs();

    if (characterc && level != characterc->getCurrentLevel()) {
        // d->saveToFile("state1.txt");
        // d->loadFromFile("state1.txt");
        clearLevelData();
        level = characterc->getCurrentLevel();
        draw(level);
    }
}

void MainWindow::redraw(Level *level) {
    int lNummer = 0;
    for (int row = 0; row < level->getHeight(); ++row) {
        for (int col = 0; col < level->getWidth(); ++col) {
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (level->getTile(row, col)->hasCharacter()) {
                characterAny = level->getTile(row, col)->getCharacter();
                if (characterAny->getCharTyp() == CharacterTyp::NPC) {
                    if (characterLabels[lNummer] != nullptr) {
                        delete characterLabels[lNummer];
                    }
                    QLabel* zombieLabel = new QLabel("");
                    if (lNummer == 0) {
                        for (auto characterLabel : characterLabels) {
                            characterLabel->setPixmap(dead);
                        }
                    }
                    zombieLabel->setPixmap(characterAny->getHitpoints() <= 0 ? dead : zombie);
                    zombieLabel->setFixedSize(33, 33);
                    zombieLabel->setScaledContents(true);
                    tilesgridLayout->addWidget(zombieLabel, row, col, Qt::AlignCenter);
                    characterLabels[lNummer] = zombieLabel;
                    lNummer++;
                } else {
                    if (c != nullptr) {
                        delete c;
                    }
                    c = new QLabel("");
                    characterc = characterAny;
                    QPixmap pixmap = characterc->getDirection() == Direction::front ? character :
                                         characterc->getDirection() == Direction::left ? charLeft :
                                         characterc->getDirection() == Direction::right ? charRight : charBack;
                    c->setPixmap(pixmap);
                    c->setFixedSize(33, 33);
                    c->setScaledContents(true);
                    tilesgridLayout->addWidget(c, row, col, Qt::AlignCenter);

                    if (texture == "_") {
                        c->lower(); // Lower the character label if the tile is a pit
                    }
                    if (texture == "<") {
                        c->raise();
                    }
                }
                if (texture == "?") {
                    for (auto d : level->doors) {
                        QString doorTexture = QString::fromStdString(d->getTexture());
                        QLabel* label = static_cast<QLabel*>(tilesgridLayout->itemAtPosition(d->getRow(), d->getColumn())->widget());
                        if (label) {
                            tilesgridLayout->removeWidget(label);
                            delete label;
                        }
                        label = new QLabel("label");
                        label->setPixmap(doorTexture == "X" ? doorclose : doorOpen);
                        label->setFixedSize(42, 42);
                        label->setScaledContents(true);
                        tilesgridLayout->addWidget(label, d->getRow(), d->getColumn(), Qt::AlignCenter);
                    }
                }
            }
        }
    }

}

Input MainWindow::getLastInput() const {
    return lastInput;
}

void MainWindow::setLastInput(Input newLastInput) {
    lastInput = newLastInput;
}

void MainWindow::clearLayout(QLayout *layout) {
    if (layout) {
        while (layout->count() > 0) {
            QLayoutItem* item = layout->takeAt(0);
            if (item) {
                if (QWidget* widget = item->widget()) {
                    layout->removeWidget(widget);
                    delete widget;
                }
                delete item;
            }
        }
    }
}

void MainWindow::loadTextures() {
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

void MainWindow::clearLevelData() {
    qDeleteAll(characterLabels);
    characterLabels.clear();
    clearLayout(tilesgridLayout);
    clearLayout(buttonGridLayout);
    delete tilesgridLayout;
    delete buttonGridLayout;
    delete gameFieldWidget;
    delete controlWidget;
    delete gridLayout;
    gridLayout = new QGridLayout(mainBack);
    gameFieldWidget = new QWidget(mainBack);
    tilesgridLayout = new QGridLayout(gameFieldWidget);
    controlWidget = new QWidget(mainBack);
    buttonGridLayout = new QGridLayout(controlWidget);
}
