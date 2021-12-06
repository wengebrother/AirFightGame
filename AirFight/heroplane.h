#ifndef HEROPLANE_H
#define HEROPLANE_H
#include <QPixmap>
#include <QRect>
//#include "bullet.h"
#include "weapon.h"
#include "config.h"
class heroPlane
{
public:
    heroPlane();

    //开火
    void weaponSystem_shoot();

    //飞机控制器：跟随鼠标位置
    void followMouse(int x,int y);

    //计算射出去的子弹坐标
    void calBulletPos(Weapon * weapSub);

public:
    //主角飞机图片
    QPixmap m_heroPlane;
    //边框检测
    QRect m_heroPlaneRect;
    //飞机坐标
    int m_Plane_X;
    int m_Plane_Y;

    //武器系统参数
    Weapon weaponRight;
    Weapon weaponLeft;
    bool trigger; //扳机
    bool trigger_limit;//鼠标必须在场景中才可以击发

};

#endif // HEROPLANE_H
