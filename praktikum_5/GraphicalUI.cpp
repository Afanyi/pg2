#include "GraphicalUI.h"
#include <iostream>
#include <QDebug>
#include "Character.h"
#include "DungeonCrawler.h"
#include "time.h"
GraphicalUI::GraphicalUI() : startScreen(new StartCreem()), mainWindow(new MainWindow()){
    connect(startScreen->newGameButton, &QPushButton::clicked, this, &GraphicalUI::switchWindow);
    level = mainWindow->level;
    draw(level);
    std::cout << mainWindow->width() << " size " << mainWindow->height() << std::endl;

    mainWindow->hide();
    startScreen->show();
}

void GraphicalUI::switchWindow() {
    startScreen->hide();
    mainWindow->show();
}

void GraphicalUI::draw(Level* level) {
    mainWindow->draw(level);
}

void GraphicalUI::redraw(Level* level)
{
    mainWindow->redraw(level);
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
    lastInput = mainWindow->getLastInput();
    return lastInput;
}
