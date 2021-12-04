#include "bullet.h"
#include "config.h"
Bullet::Bullet()
{
    //加载子弹资源
    Bullet_pic.load(bulletPath);
    //子弹坐标
    bullet_x=(screeWidth-Bullet_pic.width())/2;
    bullet_y=screehight;

    //子弹的状态
    bullet_state=true;
    //子弹的速度
    bullet_speed=bulletSpeed;

    //子弹边框 碰撞检测
    bullet_rect.setWidth(Bullet_pic.width());
    bullet_rect.setHeight(Bullet_pic.height());
    bullet_rect.moveTo(bullet_x,bullet_y);
}

void Bullet::updatePosition()
{
    //判断子弹的状态
    if(bullet_state){

        return;
    }

    //更新子弹位置
    bullet_y-=bullet_speed;
    bullet_rect.moveTo(bullet_x,bullet_y);

    //更新子弹状态
    if(bullet_y<=-bullet_rect.height()){
        bullet_state=true;
    }

}
