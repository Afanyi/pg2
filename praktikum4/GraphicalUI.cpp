#include "GraphicalUI.h"
#include <iostream>
#include <QDebug>
#include "Character.h"
#include "DungeonCrawler.h"
#include "time.h"
GraphicalUI::GraphicalUI() : startScreen(new StartCreem), mainWindow(new MainWindow()){
    connect(startScreen->newGameButton, &QPushButton::clicked, this, &GraphicalUI::switchWindow);

    m_d = nullptr;

    loadTextures();
    gameFieldWidget = new QWidget(mainWindow->mainBack);
    tilesgridLayout = new QGridLayout(gameFieldWidget);

    controlWidget = new QWidget(mainWindow->mainBack);
    buttonGridLayout = new QGridLayout(controlWidget);
    level = new Level();
    draw(level);

    mainWindow->hide();
    startScreen->show();
}

void GraphicalUI::switchWindow() {
    startScreen->hide();
    mainWindow->show();
}

void GraphicalUI::loadTextures() {
    // Load textures using QPixmap
    floor = QPixmap("./files/textures/floor/floor1.png");
    floor1 = QPixmap("./files/textures/floor/floor2.png");
    floor2 = QPixmap("./files/textures/floor/floor3.png");
    floor3 = QPixmap("./files/textures/floor/floor4.png");
    floor4 = QPixmap("./files/textures/floor/floor5.png");
    wall = QPixmap("./files/textures/wall/wall1.png");
    portal = QPixmap("./files/textures/portal/portal1.png");
    portal1 = QPixmap("./files/textures/portal/portal2.png");
    pit = QPixmap("./files/textures/pit.png");
    Ramp = QPixmap("./files/textures/ramp.png");
    doorOpen = QPixmap("./files/textures/doors/door1.png");
    doorclose = QPixmap("./files/textures/doors/door2.png");
    switc = QPixmap("./files/textures/switch.png");

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
    charBack = QPixmap("./files/textures/char/back/char_back_1.png");
    charLeft = QPixmap("./files/textures/char/left/char_left_1.png");
    charRight = QPixmap("./files/textures/char/right/char_right_1.png");
}
void GraphicalUI::draw(Level* level) {

    int rad;    //random föoor
    int portalCount = 0;    // portal color
    srand(time(0));
    for (int row = 0; row < level->getHeight(); ++row) {
        for (int col = 0; col < level->getWidth(); ++col) {
            QLabel* label = new QLabel("label");
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (texture == ".") {
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

            label->setFixedSize(42, 42);
            label->setScaledContents(true);
            tilesgridLayout->addWidget(label, row, col, Qt::AlignCenter);

            if (level->getTile(row, col)->hasCharacter()) {
                if (c != nullptr) {
                    delete c;
                }

                c = new QLabel("");
                Character* characterc = level->getTile(row, col)->getCharacter();

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

    // Set spacing and margins for the game field layout
    tilesgridLayout->setSpacing(0);
    tilesgridLayout->setContentsMargins(0, 0, 0, 0);
    gameFieldWidget->setMinimumSize(500, 336);
    mainWindow->gridLayout->addWidget(gameFieldWidget, 0, 0, Qt::AlignCenter);

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
            connect(button, &MyButton::slotbutton, this, &GraphicalUI::moveSlot);
            buttonGridLayout->addWidget(button, row, col, Qt::AlignCenter);
        }
    }

    // Remove spacing and margins between buttons
    buttonGridLayout->setSpacing(0);
    buttonGridLayout->setContentsMargins(0, 0, 0, 0);

    controlWidget->setMinimumSize(139, 139);
    controlWidget->setBackgroundRole(QPalette::Dark);
    controlWidget->setLayout(buttonGridLayout);
    mainWindow->gridLayout->addWidget(controlWidget, 0, 1, Qt::AlignCenter);
}

void GraphicalUI::redraw(Level* level)
{

    for (int row = 0; row < level->getHeight(); ++row)
    {
        for (int col = 0; col < level->getWidth(); ++col)
        {
            QString texture = QString::fromStdString(level->getTile(row, col)->getTexture());
            if (level->getTile(row, col)->hasCharacter()) {
                if (c != nullptr) {
                    delete c;
                }
                c = new QLabel("");
                Character* characterc = level->getTile(row, col)->getCharacter();
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
                if(texture == "?"){
                    Door* d = level->getDoor();
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



void GraphicalUI::resizeEvent(QResizeEvent* event) {
    MainWindow::resizeEvent(event);
    mainBack->setFixedSize(event->size());
    mainBack->setPixmap(mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    mainBackground = mainBackground.scaled(event->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    mainWindow->resize(event->size());
    //draw(level);
    mainWindow->update();
}

void GraphicalUI::moveSlot(int x, int y) {
    //mainWindow->hide();
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
    moveSlotIsCalled = true;
    //draw(level);
    m_d->turn();
    redraw(level);
}

void GraphicalUI::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_7:
        lastInput = Input::upleft;
        std::cout << "left ";
        break;
    case Qt::Key_8:
        lastInput = Input::up;
        break;
    case Qt::Key_9:
        lastInput = Input::upright;
        break;
    case Qt::Key_4:
        lastInput = Input::left;
        break;
    case Qt::Key_5:
        lastInput = Input::center;
        break;
    case Qt::Key_6:
        lastInput = Input::right;
        break;
    case Qt::Key_1:
        lastInput = Input::downleft;
        break;
    case Qt::Key_2:
        lastInput = Input::down;
        break;
    case Qt::Key_3:
        lastInput = Input::downright;
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }
    m_d->turn();
    draw(level);

}

Input GraphicalUI::move() {
    return lastInput;
}
