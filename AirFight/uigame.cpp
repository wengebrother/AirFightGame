#include "uigame.h"
#include <QDebug>
UIgame::UIgame(QWidget *parent) : QWidget(parent)
{
    //this->setParent(parent);
    this->setWindowTitle("UI界面");
    this->resize(QSize(800, 800));
    start_btn=new QPushButton(this);
    start_btn->setText("进入游戏");
    start_btn->move(300,500);
    connect(this->start_btn,SIGNAL(clicked()),this,SLOT(sendSignal()));


}

void UIgame::sendSignal()
{
    qDebug("发射信号");
    //this->hide();
    emit startGameSignal();

}
