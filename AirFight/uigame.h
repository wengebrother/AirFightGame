#ifndef UIGAME_H
#define UIGAME_H

#include <QWidget>
#include <QPushButton>
#include "mainsens.h"
#include "map.h"
#include <QSound>
class UIgame : public QWidget
{
    Q_OBJECT
public:
    explicit UIgame(QWidget *parent = nullptr);
    //~UIgame();

    void paintEvent(QPaintEvent *);



signals:

    void startGameSignal();
    void quitAppSignal();
public slots:
     void sendSignal();
     void getFromMasensSlot();

public:
    QPushButton* start_btn;
    QPushButton* quit_btn;
    QPixmap UI_map;
    QPixmap UI_button;
    Map testMap;
    QSound* bgm;

};

#endif // UIGAME_H
