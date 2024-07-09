#include "MyButton.h"

MyButton::MyButton(int x,int y) : x(x),y(y)
{
    // setText(QString("Spalte ") +
    //         QString::fromStdString(std::to_string(x + 1)));
}

void MyButton::buttonclicked()
{
    emit slotbutton(x,y);
}
