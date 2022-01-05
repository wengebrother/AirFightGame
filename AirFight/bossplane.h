#ifndef BOSSPLANE_H
#define BOSSPLANE_H
#include "enemyplane.h"

class BossPlane :public EnemyPlane
{
public:
    BossPlane();
    ~BossPlane();

    void updateBossPos();

public:
    //BOSS资源
    QPixmap enemyBoss_pic;

    //移动方向
    enum direction {Up, Down, Right,Left} directionNow;

    //血条比例
    float rateOfBlood;

    //当前血量
    int nowHp;

    //总血量
    int bloodOfLife ;
};

#endif // BOSSPLANE_H
