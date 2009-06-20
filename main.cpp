#include "mxloader.h"
#include "config.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
a.setApplicationName(APP_NAME);
a.setApplicationVersion(APP_VERS);
    MXLoader *mx = new MXLoader ();
    mx->start();
    return a.exec();
}
