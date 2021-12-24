#ifndef UIGAME_H
#define UIGAME_H

#include <QWidget>
#include <QPushButton>
#include "mainsens.h"
class UIgame : public QWidget
{
    Q_OBJECT
public:
    explicit UIgame(QWidget *parent = nullptr);
    //~UIgame();

signals:

    void startGameSignal();
public slots:
     void sendSignal();

public:
    QPushButton* start_btn;
    //Mainsens* sens;

};

#endif // UIGAME_H
