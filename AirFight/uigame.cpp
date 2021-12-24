#include "uigame.h"
#include <QDebug>
#include <QPainter>
UIgame::UIgame(QWidget *parent) : QWidget(parent)
{
     //隐藏边框
    //setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    this->setWindowTitle("文哥出品-雷霆空战");
    setFixedSize(800,400);
    //this->resize(QSize(800, 400));
    setWindowIcon(QIcon(gameIconPath));

    //加载图片
    UI_map.load(UImapPath);
    UI_button.load(UIbuttomPath);

    //按钮设置
    start_btn=new QPushButton(this);
    //start_btn->setText("进入游戏");
    start_btn->move(500,10);
    start_btn->setFixedSize(150,54);//设置按钮大小
    start_btn->setIconSize(QSize(150,54));//设置按钮图标大小
    start_btn->setIcon(QIcon(UIbuttomPath));


    //连接信号
    connect(this->start_btn,SIGNAL(clicked()),this,SLOT(sendSignal()));

   // QImage image(QString(":/image/sf.png"));
    //this->setPixmap(QPixmap::fromImage(image));


}

void UIgame::paintEvent(QPaintEvent *)
{
     QPainter painter(this);
     painter.drawPixmap(0,0,UI_map);
     //painter.drawPixmap(0,0,UI_map);


}

void UIgame::sendSignal()
{
    qDebug("发射信号");

    emit startGameSignal();

}
