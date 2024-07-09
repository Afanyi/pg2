#include "StartScreem.h"

StartCreem::StartCreem()
{
    setWindowTitle("Start Screen");

    QLabel* background = new QLabel(this);
    background->setPixmap(QPixmap("./files/textures/startscreen.png"));
    background->setScaledContents(true);

    newGameButton = new QPushButton("", this);
    newGameButton->setStyleSheet(
        "QPushButton {"
        "border-image: url(./files/textures/new_game_button.png)"
        "}"
        "QPushButton:hover {"
        "border-image: url(./files/textures/new_game_button.png);"
        "}"
        "QPushButton:pressed {"
        "border-image: url(./files/textures/new_game_button.png);"
        "}"
        );
    newGameButton->setFixedSize(600, 200);
    //connect(newGameButton, &QPushButton::clicked, this, &GraphicalUI::switchWindow);

    startLayout = new QVBoxLayout();
    startLayout->addWidget(background, 0, Qt::AlignCenter);
    startLayout->addWidget(newGameButton, 0, Qt::AlignCenter);
    setLayout(startLayout);
}
