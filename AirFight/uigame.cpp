#include "uigame.h"
#include <QDebug>
#include <QPainter>
UIgame::UIgame(QWidget *parent) : QWidget(parent)
{


    //设置界面
    this->setWindowTitle("文哥出品-雷霆空战");
    setFixedSize(800,400);
    //隐藏边框
    //setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    //this->resize(QSize(800, 400));
    setWindowIcon(QIcon(UIitemPath));//设置图标

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

    QFont ft;
    ft.setPointSize(26);
    quit_btn=new QPushButton(this);
    quit_btn->setFont(ft);
    quit_btn->setText("关闭游戏");
    quit_btn->move(500,100);
    quit_btn->setFixedSize(150,54);//设置按钮大小
    quit_btn->setIconSize(QSize(150,54));//设置按钮图标大小
    //quit_btn->setIcon(QIcon(UIbuttomPath));


    bgm = new QSound(UIbgmPath, this);
    bgm->setLoops(-1);
    bgm->play();

    //连接信号
    connect(this->start_btn,SIGNAL(clicked()),this,SLOT(sendSignal()));
    connect(this->quit_btn,SIGNAL(clicked()),this,SIGNAL(quitAppSignal()));
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
    //qDebug("发射信号");
    bgm->stop();
    emit startGameSignal();

}

void UIgame::getFromMasensSlot()
{
    bgm->play();
    bgm->setLoops(-1);

}
