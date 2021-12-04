#include "heroplane.h"
#include "config.h"
heroPlane::heroPlane()
{
   //初始化加载飞机的资源
    m_heroPlane.load(heroPlanPath);
   //初始化飞机坐标
    m_Plane_X=(screeWidth-m_heroPlane.width())/2;
    m_Plane_Y=(screehight-m_heroPlane.height());
  //初始化检测边框
    m_heroPlaneRect.setWidth(m_heroPlane.width());
    m_heroPlaneRect.setHeight(m_heroPlane.height());
    m_heroPlaneRect.moveTo(m_Plane_X,m_Plane_Y);

}

void heroPlane::weaponSystem_shoot()
{
    //左侧武器发射子弹
    weaponLeft.getWeapon(m_Plane_X,m_Plane_Y);
    weaponLeft.weaponShoot(15,50);
    calBulletPos(&weaponLeft);

    //右侧武器发射子弹
    weaponRight.getWeapon(m_Plane_X,m_Plane_Y);
    weaponRight.weaponShoot(80,50);
    calBulletPos(&weaponRight);

}



void heroPlane::followMouse(int x,int y)
{
     m_Plane_X=x;
     m_Plane_Y=y;
     m_heroPlaneRect.moveTo(m_Plane_X,m_Plane_Y);


}

void heroPlane::calBulletPos(Weapon * weapSub)
{
    for(int i=0;i<bulletNum;i++){
        if(weapSub->bullets[i].bullet_state==false){
            weapSub->bullets[i].updatePosition();

        }
    }
}
