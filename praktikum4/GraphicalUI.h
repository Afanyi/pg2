#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H
//#include <QMainWindow>
#include <QDialog>
#include <QPixmap>
#include <QGridLayout>
#include <QLabel>
#include <StartScreem.h>
#include <QApplication>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "AbstractUI.h"
#include <QFrame>
#include <QEvent>
#include "MyButton.h"
#include "mainwindow.h"

class DungeonCrawler;
class GraphicalUI : public MainWindow, public AbstractView, public AbstractController {
    Q_OBJECT

public:
    bool moveSlotIsCalled = false;
    GraphicalUI();
    void draw(Level* level) override;
    void redraw(Level* level);
    Input move() override;
    void resizeEvent(QResizeEvent* event) override;
    void moveSlot(int x, int y);
    void keyPressEvent(QKeyEvent* event) override;
    Level* level;
    DungeonCrawler* m_d;
private:
    //QGridLayout* gridLayout;
    QGridLayout* tilesgridLayout;
    QGridLayout* buttonGridLayout;

    QLabel* gameFieldTiles[10][10];
    QPushButton* control[3][3];
    //QLabel* mainBack;

    //QLabel *labels[rows][cols];
    QWidget* centralWidget;
    QWidget* gameFieldWidget;
    QWidget* controlWidget;

    // tiles
    QPixmap character;
    QPixmap charLeft;
    QPixmap charRight;
    QPixmap charBack;

    //QPixmap mainBackground;
    QPixmap floor;
    QPixmap floor1;
    QPixmap floor2;
    QPixmap floor3;
    QPixmap floor4;
    QPixmap wall;
    QPixmap portal;
    QPixmap portal1;
    QPixmap pit;
    QPixmap Ramp;
    QPixmap doorOpen;
    QPixmap doorclose;
    QPixmap switc;

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

private slots:
    void switchWindow();

private:
    QLabel* c = nullptr;
    StartCreem* startScreen;
    MainWindow* mainWindow;
    Input lastInput;
    void loadTextures();
};

#endif // GRAPHICALUI_H
