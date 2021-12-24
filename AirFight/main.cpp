#include "mainsens.h"
#include <QApplication>
#include <QResource>
#include <uigame.h>
#include "config.h"
UIgame* UI;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册二进制资源
    QResource::registerResource(gameRCC_PATH);

    UIgame myUI;
    UI=&myUI;
    myUI.show();
    Mainsens w;




    return a.exec();
}
