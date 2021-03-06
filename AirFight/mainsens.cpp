#include "mainsens.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSound>
Mainsens::Mainsens(QWidget *parent)
    : QWidget(parent)
{
    //初始化场景
    initSence();

    //启动游戏
    playGame();

}

Mainsens::~Mainsens()
{
}

void Mainsens::initSence()
{
    //设置窗口固定尺寸
    setFixedSize(screeWidth,screehight);

    //设置标题
    setWindowTitle(gameTitle);

    //加载图标
    setWindowIcon(QIcon(gameIconPath));

    //设置定时器
    m_Timer.setInterval(gameTimeRate);

    //初始化敌机出场间隔记时参数
    enemPlaneOut_count=0;

    //随机数种子
    srand((unsigned int)time(NULL));

    //测试代码

}

void Mainsens::updatePosition()
{
      //更新地图坐标
      m_map.mapPosition();
      //战机开火
      m_plane_hero.weaponSystem_shoot();

      //更新敌机坐标

      for(int i=0;i<enemNum;i++){
          if(enemPlaneS[i].enemy_state==false){
              enemPlaneS[i].updatePos();
          }
      }

      //更新爆炸的位置
      for(int k=0;k<bombNum;k++){
          if(bombs[k].bomb_state==false){
              bombs[k].updateInfo();
          }

      }
}

void Mainsens::playGame()
{
    //启动背景音乐
    QSound::play(bgmPath);
    //启动定时器
    m_Timer.start();
    //监听定时器发出的信号
    connect(&m_Timer,&QTimer::timeout,[=](){\

    enemPlaneComeOn();
    updatePosition();
    colliDetec();

    update();
    });
}

void Mainsens::paintEvent(QPaintEvent *)
{
       QPainter painter(this);
       //绘制背景
       painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
       painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);


       //绘制英雄飞机
       painter.drawPixmap(m_plane_hero.m_Plane_X,m_plane_hero.m_Plane_Y,m_plane_hero.m_heroPlane);


       //绘制子弹
       for(int i=0;i<bulletNum;i++){
           if(m_plane_hero.weaponLeft.bullets[i].bullet_state==false){
               painter.drawPixmap(m_plane_hero.weaponLeft.bullets[i].bullet_x\
                                  ,m_plane_hero.weaponLeft.bullets[i].bullet_y\
                                  ,m_plane_hero.weaponLeft.bullets[i].Bullet_pic);

           }


           if(m_plane_hero.weaponRight.bullets[i].bullet_state==false){
               painter.drawPixmap(m_plane_hero.weaponRight.bullets[i].bullet_x\
                                  ,m_plane_hero.weaponRight.bullets[i].bullet_y\
                                  ,m_plane_hero.weaponRight.bullets[i].Bullet_pic);

           }
       }



       //绘制敌机
       for(int i=0;i<enemNum;i++){
           if(enemPlaneS[i].enemy_state==false){
               painter.drawPixmap(enemPlaneS[i].enemyPlane_x,enemPlaneS[i]\
                                  .enemyPlane_y,enemPlaneS[i].enemyPlane_pic);
           }
       }


       //绘制爆炸效果
       for(int n=0;n<bombNum;n++){
           if(bombs[n].bomb_state==false){
               painter.drawPixmap(bombs[n].bomb_x,bombs[n].bomb_y,\
                           bombs[n].bomb_pics[bombs[n].bomb_index]\
                       );
           }

       }


}






void Mainsens::mouseMoveEvent(QMouseEvent * event)
{
    //跟随鼠标的位置
    int x = event->x()-m_plane_hero.m_heroPlaneRect.width()/2;
    int y = event->y()-m_plane_hero.m_heroPlaneRect.height()/2;

   //边界检测
    if(x<=0){
        x=0;
    }
    if(x>=screeWidth-m_plane_hero.m_heroPlaneRect.width()){

       x=screeWidth-m_plane_hero.m_heroPlaneRect.width();
    }
    if(y<=0){
        y=0;
    }
    if(y>=screehight-m_plane_hero.m_heroPlaneRect.height()){
      y=screehight-m_plane_hero.m_heroPlaneRect.height();
    }

    m_plane_hero.followMouse(x,y);

}

void Mainsens::enemPlaneComeOn()
{
    enemPlaneOut_count++;
    if(enemPlaneOut_count<interval){
        return;
    }
    enemPlaneOut_count=0;
    for(int i=0;i<enemNum;i++){
        if(enemPlaneS[i].enemy_state){
            enemPlaneS[i].enemy_state=false;
            enemPlaneS[i].enemyPlane_x=rand()%(screeWidth-enemPlaneS[i].enemyPlane_rect.width());
            enemPlaneS[i].enemyPlane_y=0;

            break;
        }
    }
}

void Mainsens::colliDetec()
{
    //遍历判断所有非空闲的子弹和敌机的边框是否重叠
    for(int m=0;m<enemNum;m++){

        if(enemPlaneS[m].enemy_state){
            continue;
        }

        for(int i=0;i<bulletNum;i++){

            if(m_plane_hero.weaponLeft.bullets[i].bullet_state==false){

                if(m_plane_hero.weaponLeft.bullets[i]\
                   .bullet_rect.intersects(enemPlaneS[m]\
                   .enemyPlane_rect)){

                    m_plane_hero.weaponLeft.bullets[i].bullet_state=true;
                    enemPlaneS[m].enemy_state=true;



                    //碰撞后的爆炸效果
                    for(int g=0;g<bombNum;g++){
                        if(bombs[g].bomb_state){
                            QSound::play(bombBgmPath);
                            bombs[g].bomb_state=false;
                            bombs[g].bomb_x=enemPlaneS[m].enemyPlane_x;
                            bombs[g].bomb_y=enemPlaneS[m].enemyPlane_y;
                            break;
                        }
                    }
                }
            }

             if(m_plane_hero.weaponRight.bullets[i].bullet_state==false){
                if(m_plane_hero.weaponRight.bullets[i]\
                        .bullet_rect.intersects(enemPlaneS[m]\
                        .enemyPlane_rect)){
                    m_plane_hero.weaponRight.bullets[i].bullet_state=true;
                    enemPlaneS[m].enemy_state=true;


                    for(int s=0;s<bombNum;s++){
                        if(bombs[s].bomb_state){
                            QSound::play(bombBgmPath);
                            bombs[s].bomb_state=false;
                            bombs[s].bomb_x=enemPlaneS[m].enemyPlane_x;
                            bombs[s].bomb_y=enemPlaneS[m].enemyPlane_y;
                            break;
                        }
                    }
                }
            }
        }
    }
}



