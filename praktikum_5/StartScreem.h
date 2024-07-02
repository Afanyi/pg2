#ifndef STARTSCREEM_H
#define STARTSCREEM_H
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>

class StartCreem: public QDialog{


public:
    StartCreem();
    QLabel* background;
    QPushButton* newGameButton;
    QVBoxLayout* startLayout;

};
#endif // STARTSCREEM_H
