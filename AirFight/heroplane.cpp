#include "heroplane.h"
#include "config.h"

heroPlane::heroPlane()
{
   //初始化加载飞机的资源
    m_heroPlane.load(heroPlanPath);

   //初始化飞机坐标
    m_Plane_X=(screeWidth-m_heroPlane.width())/2+240;
    m_Plane_Y=(screehight-m_heroPlane.height())/2+300;

  //初始化检测边框
    m_heroPlaneRect.setWidth(m_heroPlane.width());
    m_heroPlaneRect.setHeight(m_heroPlane.height());
    m_heroPlaneRect.moveTo(m_Plane_X,m_Plane_Y);

    //初始化存活状态
    stateOfLife=true;

    //初始化出场状态
    stateOfReady=false;
    //武器发射标志
    trigger=false;
    //初始化玩家得分
    scoersOfPlayer=0;

}

void heroPlane::weaponSystem_shoot()
{
    //扳机触发
    if((trigger==true)&&(trigger_limit)){
        //左侧武器发射子弹
        weaponLeft.getWeapon(m_Plane_X,m_Plane_Y);
        weaponLeft.weaponShoot(15,50);
        //右侧武器发射子弹
        weaponRight.getWeapon(m_Plane_X,m_Plane_Y);
        weaponRight.weaponShoot(80,50);
    }

    //计算发射出去的子弹位置
    calBulletPos(&weaponLeft);
    calBulletPos(&weaponRight);

}


//跟随控制指令
void heroPlane::followControl(int x,int y)
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

void heroPlane::gotoFight()
{
  stateOfReady=true;
  //qDebug("出击");
}
