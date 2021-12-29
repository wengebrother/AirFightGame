#include "bossplane.h"
#include "enemyplane.h"
#include "config.h"
BossPlane::BossPlane()
{
    enemyBoss_pic.load(enemBossPath);

    enemyPlane_x=0;
    enemyPlane_y=0;
}

BossPlane::~BossPlane()
{

}
