#ifndef CONFIG_H
#define CONFIG_H


/**屏幕尺寸参数**/
#define screeWidth  600//480
#define screehight  700
#define screeMouse  480//鼠标显示区域


/******游戏参数配置*******/
#define gameTitle  "模拟空战"
#define gameRCC_PATH "./plane.rcc"
#define gameIconPath "D:/Learn/QTlearnProject/AirFight/AirFight/resFlie/bitbug_favicon.ico"
#define gameTimeRate 10 //定时器更新周期 单位毫秒
#define winFlagNum 100 //玩家击落敌机数量，胜利的判断标志
/*****UI参数配置********/
#define UImapPath "D:/Learn/QTlearnProject/AirFight/AirFight/resFlie/UI12.png"
#define UIbuttomPath "D:/Learn/QTlearnProject/AirFight/AirFight/resFlie/clipboard.png"
#define UIitemPath ":/resFlie/tubiao67.png"
/********地图参数配置************/
#define gameMapPath "D:/Learn/QTlearnProject/AirFight/AirFight/resFlie/background.png"
#define gameMapRollSpeed 2


/*******英雄飞机的配置属性*********/
#define heroPlanPath ":/resFlie/me1.png"


/*******敌机参数配置***********/
#define speed  5  //敌机速度
#define enemNum 30//敌机数量
#define interval  30   //敌机出场间隔，单位是一个定时器周期
#define enemPlanePath ":/resFlie/enemy1.png"


/**********子弹的配置数据**********/
#define bulletPath ":/resFlie/bullet2.png"
#define bulletSpeed 5
#define bulletNum 10 //弹匣中子弹的个数
#define bulletInterval 20   //子弹的发射间隔


/************爆炸参数配置**********/
//敌机爆炸路径
#define bombPicPath  ":/resFlie/enemy1_down%1.png"
//玩家爆炸路径
#define bombPlayerPicPath  ":/resFlie/me_destroy_%1.png"
#define bombNum    5  //爆炸数量
#define bombMax     4   //爆炸图片最大索引
#define bombIn     10    //时间间隔


/************音效参数配置**********/
#define UIbgmPath ":/resFlie/background.wav"
#define bgmPath ":/resFlie/aircraft.wav"
#define bombBgmPath ":/resFlie/down.wav"
#define winBgmPath ":/resFlie/win.wav"
#define qiangBgmPath ":/resFlie/qgun_02.wav"


#endif // CONFIG_H
