#ifndef MAINSENS_H
#define MAINSENS_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include "enemyplane.h"
#include "bomb.h"
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

    //敌机出场
    void enemPlaneComeOn();


    //碰撞检测
    void colliDetec();

    //测试代码 爆炸效果调试
    void bombTest();
public:
    QTimer m_Timer;
    Map m_map;
    heroPlane m_plane_hero;

    EnemyPlane enemPlaneS[enemNum];
    int enemPlaneOut_count;
    Bomb bombs[bombNum];

    //测试代码

};
#endif // MAINSENS_H
