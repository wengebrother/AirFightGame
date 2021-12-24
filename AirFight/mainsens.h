#ifndef MAINSENS_H
#define MAINSENS_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include "enemyplane.h"
#include "bomb.h"
#include "uigame.h"
#include <QLabel>
class Mainsens : public QWidget
{
    Q_OBJECT

public:
    Mainsens(QWidget *parent = nullptr);
    ~Mainsens();



    //初始化场景
    void initSence();

    //更新游戏元素的坐标

    void updatePosition();
    //启动游戏
    void playGame();

    //绘制屏幕 系统函数，名称不能改，此处为函数重载
    void paintEvent(QPaintEvent*);

    //重写鼠标移动事件，名称不能改，此处为函数重载
    void mouseMoveEvent(QMouseEvent * event);

    //鼠标点击事件
    void mousePressEvent(QMouseEvent * event);

    //鼠标松开事件
    void mouseReleaseEvent(QMouseEvent *event);

    //重载按键按下事件
    void keyPressEvent(QKeyEvent *event);

    //按键松开
    void keyReleaseEvent(QKeyEvent *event);

    //飞机移动控制
    void moveControl();

    //敌机出场
    void enemPlaneComeOn();

    //碰撞检测
    void colliDetec();

    //
    //void getUI(UIgame* UI);
    //测试代码
public slots:
    void functionSlot();
    void getSubWidgetSignal();
    void back2UI();

public:
    //定时器
    QTimer m_Timer;

    //地图
    Map m_map;

    //英雄飞机
    heroPlane m_plane_hero;

    //敌机
    EnemyPlane enemPlaneS[enemNum];

    //敌机出场间隔记时参数
    int enemPlaneOut_count;

    //敌机爆炸场景
    Bomb bombs[bombNum];


    //玩家爆炸场景
    Bomb bombPlayer;

    //键盘移动控制标志
    bool moveFlag[4];

private:
    //记分
    QLabel* score;
    QString strOfscore;

    //测试代码


};
#endif // MAINSENS_H
