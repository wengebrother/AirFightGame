#ifndef UIGAME_H
#define UIGAME_H

#include <QWidget>
#include <QPushButton>
#include "mainsens.h"
#include "map.h"
class UIgame : public QWidget
{
    Q_OBJECT
public:
    explicit UIgame(QWidget *parent = nullptr);
    //~UIgame();

    void paintEvent(QPaintEvent *);



signals:

    void startGameSignal();
public slots:
     void sendSignal();

public:
    QPushButton* start_btn;
    QPixmap UI_map;
    QPixmap UI_button;
    Map testMap;

};

#endif // UIGAME_H
