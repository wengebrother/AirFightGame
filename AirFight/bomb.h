#ifndef BOMB_H
#define BOMB_H
#include <QVector>
#include <QPixmap>
#include "config.h"
class Bomb
{
public:
    Bomb();
    //更新信息（图标 时间间隔）
    void updateInfo();

public:
    QVector<QPixmap> bomb_pics;

    //爆炸的位置
    int bomb_x;
    int bomb_y;

    //爆炸的状态
    bool bomb_state;

    //爆炸的时间间隔
    int bomb_cont;

    //爆炸图标记录
    int bomb_index;

};

#endif // BOMB_H
