#ifndef MAP_H
#define MAP_H
#include <QPixmap>

class Map
{
public:
    Map();

    void mapPosition();

public:
    //复合关系 子地图对象
    QPixmap m_map1;
    QPixmap m_map2;


    //地图Y轴坐标
    int m_map1_posY;
    int m_map2_posY;

    //滚动速度
    int mapRollSpeed;

};

#endif // MAP_H
