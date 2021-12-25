#include "mainsens.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include <QSound>
#include <QPushButton>
#include <QDebug>
#include <uigame.h>
extern UIgame* UI;
Mainsens::Mainsens(QWidget *parent)
    : QWidget(parent)
{

    //初始化场景
    initSence();

    //添加出场按钮
    QPushButton *fireButton=new QPushButton(this);
    fireButton->setText("起飞");
    fireButton->move(490,400);
    fireButton->setFixedSize(100,100);
    //fireButton->setParent(this);


    QPushButton *backButton=new QPushButton(this);
    backButton->setText("退出游戏");
    backButton->setFixedSize(80,80);
    backButton->move(500,50);
    //radius设置为按钮边长的一半就可以变成圆形了
    backButton->setStyleSheet("QPushButton{border-radius:40px;\
                                      color:rgb(255,255,255);\
                                 border-image:url(:/resFlie/clip1.png);\
                              }");


    //连接信号
    connect(fireButton,SIGNAL(clicked()),this,SLOT(functionSlot()));
    connect(backButton,SIGNAL(clicked()),this,SLOT(back2UI()));
    connect(UI,SIGNAL(startGameSignal()),this,SLOT(getSubWidgetSignal()));
    connect(fireButton,SIGNAL(clicked()),this,SLOT(changeNoOneStateOfPlayer()));
    //启动游戏
    playGame();

    //显式追踪鼠标
    setMouseTracking(true);

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

    //隐藏边框
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    //设置定时器
    m_Timer.setInterval(gameTimeRate);

    //初始化敌机出场间隔记时参数
    enemPlaneOut_count=0;

    //升力判定标志初始化
    isWin=false;

    //初始化爆炸效果路径
   bombPlayer.str=bombPlayerPicPath;
   bombPlayer.PathSet();
   for(int k=0;k<bombNum;k++){
   bombs[k].str=bombPicPath;
   bombs[k].PathSet();
   }

    //随机数种子
    srand((unsigned int)time(NULL));

    //移动控制标志
    for(int i=0;i<4;i++){

        moveFlag[i]=false;
    }

    //创建积分器
    QFont ft;
    ft.setPointSize(16);
    strOfscore ="0";
    score =new QLabel(this);
    score->setText(strOfscore);
    score->setFixedSize(100,100);
    score->move(490,260);
    score->setFont(ft);

    //计时
    strOfTime="0";
    noOneTimeLabel=new QLabel(this);
    noOneTimeLabel->setFixedSize(100,100);
    noOneTimeLabel->move(490,200);
    noOneTimeLabel->setText(strOfTime);
    noOneTimeLabel->setFont(ft);



    //测试代码

}

void Mainsens::updatePosition()
{
      //更新地图坐标
      m_map.mapPosition();

      //更新子弹位置
       m_plane_hero.weaponSystem_shoot();

      //更新敌机坐标

      for(int i=0;i<enemNum;i++){
          if(enemPlaneS[i].enemy_state==false){
              enemPlaneS[i].updatePos();
          }
      }

      //更新玩家生命状态
      if(m_plane_hero.stateOfLife==false){

          //当玩家被击落后，更新为未出场状态，飞机回到初始位置
          m_plane_hero.stateOfReady=false;
          m_plane_hero.m_Plane_X=(screeWidth-m_plane_hero.m_heroPlane.width())/2+240;
          m_plane_hero.m_Plane_Y=(screeWidth-m_plane_hero.m_heroPlane.height())/2+300;
          //更新边框位置，跟图像保持一致
          m_plane_hero.m_heroPlaneRect.moveTo(m_plane_hero.m_Plane_X,m_plane_hero.m_Plane_Y);
          //更新飞机的生命状态，被击落后立马复活
          m_plane_hero.stateOfLife=true;


      }


      //更新敌机爆炸的位置
      for(int k=0;k<bombNum;k++){
          if(bombs[k].bomb_state==false){
              bombs[k].updateInfo();
          }

      }
      //更新玩家爆炸的位置
      if(bombPlayer.bomb_state==false){
         bombPlayer.updateInfo();
      }

      //更新玩家分数 QString::number(m_plane_hero.scoersOfPlayer, 10);
      strOfscore =QString("击落：%1").arg(m_plane_hero.scoersOfPlayer);
      score->setText(strOfscore);



      //更新玩家的时间显示
       strOfTime=QString("隐身：%1").arg(m_plane_hero.noOneTime/100);
       noOneTimeLabel->setText(strOfTime);

      //更新玩家的无敌状态
      if(m_plane_hero.noOneState==true){
          m_plane_hero.noOneTime--;
          if(m_plane_hero.noOneTime<=0){

              m_plane_hero.noOneState=false;
          }

      }



}

void Mainsens::iswinOfPlay()
{

    //更新玩家胜利状态判断
    if(m_plane_hero.scoersOfPlayer>=winFlagNum){
        m_plane_hero.scoersOfPlayer=0;
        isWin=true;
    }
    else{
        isWin=false;
    }

    //胜利之后的音乐特效
    if(isWin){

         isWin=false;
         bgm->stop();
         winBgm->play();
    }



}

void Mainsens::playGame()
{
    //启动背景音乐
    bgm = new QSound(bgmPath, this);
    bgm->setLoops(-1);
    bgm->play();

    winBgm = new QSound(winBgmPath, this);
    //启动定时器
    m_Timer.start();
    //监听定时器发出的信号
    connect(&m_Timer,&QTimer::timeout,[=](){
    enemPlaneComeOn();
    updatePosition();
    colliDetec();//子弹和敌机的碰撞检测
    moveControl();
    iswinOfPlay();
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
       if(m_plane_hero.stateOfLife){
           painter.drawPixmap(m_plane_hero.m_Plane_X,m_plane_hero.m_Plane_Y,m_plane_hero.m_heroPlane);

       }



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


       //绘制敌机爆炸效果
       for(int n=0;n<bombNum;n++){
           if(bombs[n].bomb_state==false){
               painter.drawPixmap(bombs[n].bomb_x,bombs[n].bomb_y,\
                           bombs[n].bomb_pics[bombs[n].bomb_index]\
                       );
           }

       }

       //绘制 玩家爆炸效果
       if(bombPlayer.bomb_state==false){
           painter.drawPixmap(bombPlayer.bomb_x,bombPlayer.bomb_y,\
                       bombPlayer.bomb_pics[bombPlayer.bomb_index]\
                   );


       }


}

void Mainsens::mouseMoveEvent(QMouseEvent *event)
{

    if(event->x()>screeMouse){
       this->setCursor(Qt::ArrowCursor); //显示鼠标
       m_plane_hero.trigger_limit=false;
    }
    //鼠标在规定区域并且飞机已经出场的情况下才可以发射子弹
    else
        {
        //qDebug("隐藏鼠标");
        this->setCursor(Qt::BlankCursor); //隐藏鼠标
        if(m_plane_hero.stateOfReady){

           m_plane_hero.trigger_limit=true;
        }else{
          m_plane_hero.trigger_limit=false;
        }

    }

}

void Mainsens::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){

     m_plane_hero.trigger=true;
    }

}


void Mainsens::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){

     m_plane_hero.trigger=false;
    }



}


void Mainsens::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_W){
         moveFlag[0]=true;
     }
    if(event->key()==Qt::Key_S){
         moveFlag[1]=true;
     }
    if(event->key()==Qt::Key_A){
         moveFlag[2]=true;
     }
    if(event->key()==Qt::Key_D){
         moveFlag[3]=true;
     }


}

void Mainsens::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W){
         moveFlag[0]=false;
     }
    if(event->key()==Qt::Key_S){
         moveFlag[1]=false;
     }
    if(event->key()==Qt::Key_A){
         moveFlag[2]=false;
     }
    if(event->key()==Qt::Key_D){
         moveFlag[3]=false;
     }
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
            enemPlaneS[i].enemyPlane_x=rand()%(screeMouse-enemPlaneS[i].enemyPlane_rect.width());
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

        //敌机与玩家子弹的碰撞检测
        for(int i=0;i<bulletNum;i++){

            //左侧武器的子弹与敌机的碰撞检测
            if(m_plane_hero.weaponLeft.bullets[i].bullet_state==false){

                if(m_plane_hero.weaponLeft.bullets[i]\
                   .bullet_rect.intersects(enemPlaneS[m]\
                   .enemyPlane_rect)){

                    m_plane_hero.weaponLeft.bullets[i].bullet_state=true;
                    enemPlaneS[m].enemy_state=true;

                    //得分
                    m_plane_hero.scoersOfPlayer++;


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

            //右侧武器的子弹与敌机的碰撞检测
             if(m_plane_hero.weaponRight.bullets[i].bullet_state==false){
                if(m_plane_hero.weaponRight.bullets[i]\
                        .bullet_rect.intersects(enemPlaneS[m]\
                        .enemyPlane_rect)){
                    m_plane_hero.weaponRight.bullets[i].bullet_state=true;
                    enemPlaneS[m].enemy_state=true;
                    //得分
                    m_plane_hero.scoersOfPlayer++;

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

       //敌机与玩家碰撞检测
        if(!m_plane_hero.noOneState){
            if(m_plane_hero.m_heroPlaneRect
               .intersects(enemPlaneS[m]
               .enemyPlane_rect)){

                m_plane_hero.stateOfLife=false;
                enemPlaneS[m].enemy_state=true;

                //得分清零
                m_plane_hero.scoersOfPlayer=0;
                //碰撞后的爆炸效果
                if(bombPlayer.bomb_state){
                    QSound::play(bombBgmPath);
                    bombPlayer.bomb_state=false;
                    bombPlayer.bomb_x=m_plane_hero.m_Plane_X;
                    bombPlayer.bomb_y=m_plane_hero.m_Plane_Y;
                    //break;
                }
            }

        }





    }
}



void Mainsens::functionSlot()
{
    m_plane_hero.gotoFight();
}

void Mainsens::getSubWidgetSignal()
{
    qDebug("获得UI信号");
    UI->hide();
    this->show();
}

void Mainsens::back2UI()
{
    qDebug("测试");
    this->hide();
    UI->show();
}

void Mainsens::changeNoOneStateOfPlayer()
{
    m_plane_hero.noOneTime=500;//5秒
    m_plane_hero.noOneState=true;
    qDebug("进入隐身状态");
}

void Mainsens::moveControl()
{
    int y=m_plane_hero.m_Plane_Y;
    int x=m_plane_hero.m_Plane_X;
    //
   if(moveFlag[0]){
       y=m_plane_hero.m_Plane_Y-6;

   }

   if(moveFlag[1]){
       y=m_plane_hero.m_Plane_Y+6;

   }

   if(moveFlag[2]){

       x=m_plane_hero.m_Plane_X-6;
   }

   if(moveFlag[3]){

       x=m_plane_hero.m_Plane_X+6;
   }


     //边界检测
   if(m_plane_hero.stateOfReady){

       if(x<=0){
           x=0;
       }
       if(x>=screeMouse-m_plane_hero.m_heroPlaneRect.width()){

          x=screeMouse-m_plane_hero.m_heroPlaneRect.width();
       }
       if(y<=0){
           y=0;
       }
       if(y>=screehight-m_plane_hero.m_heroPlaneRect.height()){
         y=screehight-m_plane_hero.m_heroPlaneRect.height();
       }



   }

//是否连接按键控制
   if(m_plane_hero.stateOfReady){

     m_plane_hero.followControl(x,y);
   }



}



