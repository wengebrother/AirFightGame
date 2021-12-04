#include "mainsens.h"
#include <QApplication>
#include <QResource>
#include "config.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册二进制资源
    QResource::registerResource(gameRCC_PATH);

    Mainsens w;
    w.show();
    return a.exec();
}
