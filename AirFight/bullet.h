#ifndef BULLET_H
#define BULLET_H
#include <QPixmap>
#include <QRect>
class Bullet
{
public:
    Bullet();

    //更新子弹坐标
    void updatePosition();
public:
    //子弹资源
   QPixmap Bullet_pic;
    //子弹坐标
   int bullet_x;
   int bullet_y;
   //子弹状态
   bool bullet_state;
   //子弹速度：每个时钟周期前进的像素数
    int bullet_speed;
   //子弹边界检测
   QRect bullet_rect;


};

#endif // BULLET_H
