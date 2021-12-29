#ifndef BOSSPLANE_H
#define BOSSPLANE_H
#include "enemyplane.h"

class BossPlane :public EnemyPlane
{
public:
    BossPlane();
    ~BossPlane();

public:
    //BOSS资源
    QPixmap enemyBoss_pic;
};

#endif // BOSSPLANE_H
