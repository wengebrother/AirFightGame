#include "map.h"
#include <QPixmap>
#include <config.h>
Map::Map()
{
    //加载地图路径
    m_map1.load(gameMapPath);
    m_map2.load(gameMapPath);

    //初始化地图Y坐标
    m_map1_posY=-screehight;
    m_map2_posY=0;

    //初始化地图滚动速度
     mapRollSpeed=gameMapRollSpeed;


}

void Map::mapPosition()
{
    m_map1_posY+=mapRollSpeed;
    m_map2_posY+=mapRollSpeed;
     if(m_map1_posY>=0)
     {
         m_map1_posY=-screehight;

     }
     if(m_map2_posY>=screehight)
     {
         m_map2_posY=0;

     }

}
