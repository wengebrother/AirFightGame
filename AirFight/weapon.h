#ifndef WEAPON_H
#define WEAPON_H
#include "bullet.h"
#include "config.h"
class Weapon
{
public:
    Weapon();
    //武器发射系统
    void weaponShoot(int x,int y);

    //获取武器的安装位置
    void getWeapon(int x,int y);
public:
    //射速
    int bullets_recoder;

    //弹容量
    Bullet bullets[bulletNum];

    //武器的安装位置
   int  weapon_X;
   int  weapon_Y;

};

#endif // WEAPON_H
