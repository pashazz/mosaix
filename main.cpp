#include "mxloader.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MXLoader *mx = new MXLoader ();
    mx->start();
    return a.exec();
}
