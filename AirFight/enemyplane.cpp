#include "enemyplane.h"
#include "config.h"
EnemyPlane::EnemyPlane()
{
    //加载敌机图片
    enemyPlane_pic.load(enemPlanePath);

    //敌机位置
    enemyPlane_x=0;
    enemyPlane_y=0;
    //敌机边框
    enemyPlane_rect.setWidth(enemyPlane_pic.width());
    enemyPlane_rect.setHeight(enemyPlane_pic.height());
    enemyPlane_rect.moveTo(enemyPlane_x,enemyPlane_y);
    //敌机速度
    enemyPlane_speed=speed;
    //敌机状态
     enemy_state=true;
}

void EnemyPlane::updatePos()
{
  //判断敌机是否空闲
    if(enemy_state){

        return;

    }

   //否则计算坐标
    enemyPlane_y+=enemyPlane_speed;
    enemyPlane_rect.moveTo(enemyPlane_x,enemyPlane_y);

    //如果超出屏幕则重置为空闲状态
    if(enemyPlane_y>=screehight+enemyPlane_rect.height()){
        enemy_state=true;

    }
}
