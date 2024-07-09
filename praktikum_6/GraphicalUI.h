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
    MainWindow* mainWindow;
    GraphicalUI();
    GraphicalUI(DungeonCrawler* dung);
    void draw(Level* level) override;
    void redraw(Level* level);
    Input move() override;
    void moveSlot(int x, int y);
    void keyPressEvent(QKeyEvent* event) override;
    Level* level;
    DungeonCrawler* m_d;
private:


private slots:
    void switchWindow();

private:
    QLabel* c = nullptr;
    StartCreem* startScreen;

    Input lastInput;
    void loadTextures();
};

#endif // GRAPHICALUI_H
