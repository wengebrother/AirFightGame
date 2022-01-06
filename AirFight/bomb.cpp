#include "bomb.h"
#include <QString>
Bomb::Bomb()
{



    //坐标初始化
    bomb_x=0;
    bomb_y=0;
    //状态初始化
    bomb_state=true;

    //当前播放图片下标
    bomb_index=0;

    //爆炸间隔记录
    bomb_cont=0;


}


void Bomb::updateInfo()
{
    bomb_cont++;
    if(bomb_state||bomb_cont<bombIn){
        return;
    }

    bomb_cont=0;

    //切换爆炸图片下标
    bomb_index++;

    if(bomb_index>bombMax-1){
        bomb_index=0;
        bomb_state=true;

    }

}

void Bomb::updateBossInfo()
{
    bomb_cont++;
    if(bomb_state||bomb_cont<bombIn){
        return;
    }

    bomb_cont=0;

    //切换爆炸图片下标
    bomb_index++;

    if(bomb_index>bombBossMax-1){
        bomb_index=0;
        bomb_state=true;

    }
}

void Bomb::PathSet()
{

    QString str2;
    //将所有的爆炸效果图放入数组中

    for(int m=1; m<= bombMax ;m++)
    {
        str2=QString(str).arg(m);
        bomb_pics.push_back(QPixmap(str2));
    }
}

void Bomb::PathBossSet()
{
    QString str2;
    //将所有的爆炸效果图放入数组中

    for(int m=1; m<= bombBossMax ;m++)
    {
        str2=QString(str).arg(m);
        bomb_pics.push_back(QPixmap(str2));
    }
}

