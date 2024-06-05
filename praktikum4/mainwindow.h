#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "DungeonCrawler.h"
#include <QMainWindow>
#include <QLabel>
#include <QGridLayout>
#include <QResizeEvent>

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
    DungeonCrawler* d;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void resizeEvent(QResizeEvent* event) override;

    QGridLayout* gridLayout;
    QLabel* mainBack;
    QPixmap mainBackground;

private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
