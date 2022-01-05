#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include <QPixmap>
#include <QRect>

class EnemyPlane
{
public:
    EnemyPlane();
    virtual ~ EnemyPlane();

    //更新坐标
    void updatePos();
public:

    //敌机对象资源
    QPixmap enemyPlane_pic;


    //敌机位置
    int enemyPlane_x;
    int enemyPlane_y;



    //边框检测
    QRect enemyPlane_rect;

    //速度
    int enemyPlane_speed;

    //敌机状态，是否空闲
    bool enemy_state;
};

#endif // ENEMYPLANE_H
