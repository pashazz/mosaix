#include "mxloader.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    app.setQuitOnLastWindowClosed( false );
    MXLoader *mx = new MXLoader ();
    mx->start();
    return a.exec();
}
