#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(int x,int y);

public slots:
    void buttonclicked();

signals:
    void slotbutton(int,int);

private:
    int x;
    int y;
};

#endif // MYBUTTON_H
