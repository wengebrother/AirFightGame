#ifndef NEWPUSHBUTTON_H
#define NEWPUSHBUTTON_H
#include <QPushButton>

class newPushbutton :public QPushButton
{
    Q_OBJECT

public:
    newPushbutton();
    //~newPushbutton();
    void setPixmap(QPixmap* pNormal,QPixmap* pHover,QPixmap* pLighted);
    void setLighted(bool value);
};

#endif // NEWPUSHBUTTON_H
