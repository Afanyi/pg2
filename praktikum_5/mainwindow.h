#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "DungeonCrawler.h"
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>
#include <qpushbutton.h>
#include "Level.h"
#include <QStatusBar>
#include <QProgressBar>
#include "Character.h"
#include "GuardController.h"
#include "StationaryController.h"
#include <vector>

using std::vector;
class DungeonCrawler;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class DungeonCrawler;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void checkingEnd();

    Level* level;
    DungeonCrawler* d;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void draw(Level* level);
    void moveSlot(int x, int y);

    void redraw(Level* level);
    //void resizeEvent(QResizeEvent* event) override;

    QGridLayout* gridLayout;
    QLabel* mainBack;
    QLabel* copyMainBack;
    QPixmap mainBackground;

    Input getLastInput() const;

    void setLastInput(Input newLastInput);
    void clearLayout(QLayout* layout);
    void specialRedraw(Level* level);

private:
    Character* characterAny;

    // zombie save in vectors
    vector<Character*> allCharacters;
    vector<QLabel*> characterLabels;

    Character* zombieCharacter;
    Character* zombieCharacter1;
    Character* zombieCharacter3;
    GuardController* zombieController;
    GuardController* zombieController1;
    StationaryController* stationarycontroller;

    // end zoombie settings

    Character* characterc = nullptr;
    QStatusBar* statusbar; // StatusLeiste
    QProgressBar* mainCharacterHp; // to display blood
    Ui::MainWindow *ui;

    QGridLayout* tilesgridLayout;
    QGridLayout* buttonGridLayout;

    QWidget* centralWidget;
    QWidget* gameFieldWidget;
    QWidget* controlWidget;

    QLabel* gameFieldTiles[10][10];
    QPushButton* control[3][3];

    QPixmap character;
    QPixmap charLeft;
    QPixmap charRight;
    QPixmap charBack;
    QPixmap zombie;
    QPixmap zombieRight;
    QPixmap dead;

    //QPixmap mainBackground;
    QPixmap lootchest;
    QPixmap floor;
    QPixmap floor1;
    QPixmap floor2;
    QPixmap floor3;
    QPixmap floor4;
    QPixmap wall;
    QPixmap portal;
    QPixmap portal1;
    QPixmap portal2;
    QPixmap pit;
    QPixmap Ramp;
    QPixmap doorOpen;
    QPixmap doorclose;
    QPixmap switc;
    QPixmap levelChanger;

    // control
    QPixmap up;
    QPixmap upleft;
    QPixmap upright;
    QPixmap down;
    QPixmap downleft;
    QPixmap downrigt;
    QPixmap left;
    QPixmap right;
    QPixmap center;
    QLabel* c = nullptr;
    QLabel* cZombie = nullptr;
    Input lastInput;

    void loadTextures();


};
#endif // MAINWINDOW_H
