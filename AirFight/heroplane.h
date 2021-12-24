#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
//#include "bullet.h"
#include "weapon.h"
#include "config.h"
#include <QDebug>
class heroPlane
{
public:
    heroPlane();

    //开火
    void weaponSystem_shoot();

    //飞机控制器：跟随鼠标位置
    void followControl(int x,int y);

    //计算射出去的子弹坐标
    void calBulletPos(Weapon * weapSub);

    //出场
    void gotoFight();

public:
    //主角飞机图片
    QPixmap m_heroPlane;
    //边框检测
    QRect m_heroPlaneRect;
    //飞机坐标
    int m_Plane_X;
    int m_Plane_Y;

    //玩家得分
    int scoersOfPlayer;
    //玩家存活标志
    bool stateOfLife;

    //出场标志
    bool stateOfReady;

    //玩家出场无敌时间
    int noOneTime;

    //玩家无敌状态标志
    bool noOneState;

    //武器系统参数
    Weapon weaponRight;
    Weapon weaponLeft;
    bool trigger; //扳机
    bool trigger_limit;//鼠标必须在场景中才可以击发

};

#endif // HEROPLANE_H
