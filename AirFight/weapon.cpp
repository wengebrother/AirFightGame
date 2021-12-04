#include "weapon.h"

Weapon::Weapon()
{
    bullets_recoder=0;

}

void Weapon::weaponShoot(int x, int y)
{
    //控制子弹射速
    bullets_recoder++;
    if(bullets_recoder<bulletInterval){
       //发射时间未到不发射
        return;
    }

    bullets_recoder=0;
    //遍历弹匣，找出弹匣中第一个未发射的子弹，将其发射
    for(int i=0;i<bulletNum;i++){
       if(bullets[i].bullet_state){
          bullets[i].bullet_state=false;
           //子弹的发射位置
          bullets[i].bullet_x=weapon_X+x;
          bullets[i].bullet_y=weapon_Y+y;
          break;//一个发射周期只发射一个
       }

    }
}

void Weapon::getWeapon(int x, int y)
{
    weapon_X=x;
    weapon_Y=y;
}
