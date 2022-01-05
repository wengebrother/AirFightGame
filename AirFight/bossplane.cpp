#include "bossplane.h"
#include "enemyplane.h"
#include "config.h"
BossPlane::BossPlane()
{
    enemyBoss_pic.load(enemBossPath);

    enemyPlane_rect.setWidth(enemyBoss_pic.width());
    enemyPlane_rect.setHeight(enemyBoss_pic.height());
    enemyPlane_rect.moveTo(enemyPlane_x,enemyPlane_y);
    rateOfBlood=1;
    bloodOfLife=100;
    nowHp=100;


    enemyPlane_speed=1;
    directionNow=Down;
     //qDebug("nowHP:%d",nowHp);

}

BossPlane::~BossPlane()
{

}

void BossPlane::updateBossPos()
{
    //判断敌机是否空闲
      if(enemy_state){

          return;

      }

      if(enemyPlane_y==500&&directionNow==Down){
          directionNow=Up;

      }else if(enemyPlane_y==300&&directionNow==Down){
          directionNow=Right;

      }else if(enemyPlane_x==400&&directionNow==Right){
          directionNow=Left;
          //qDebug("向左%d",enemyPlane_x);

      }else if(enemyPlane_x==10&&directionNow==Left){
          directionNow=Down;
      }else if(enemyPlane_y==10&&directionNow==Up){

            directionNow=Down;
      }

      switch(directionNow){
           case Down :
             enemyPlane_y+=enemyPlane_speed;
            break;

           case Up :
              enemyPlane_y-=enemyPlane_speed;
            break;

           case Right :
                enemyPlane_x+=enemyPlane_speed;
                //qDebug("%d",enemyPlane_x);
           break;

           case Left :
                enemyPlane_x-=enemyPlane_speed;
           break;

      }


      enemyPlane_rect.moveTo(enemyPlane_x,enemyPlane_y);
      //qDebug("nowHP:%d",enemyPlane_y);
      //如果超出屏幕则重置为空闲状态
     /* if(enemyPlane_y>=screehight+enemyPlane_rect.height()){
          enemy_state=true;

      }*/

}
