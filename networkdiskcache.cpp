#include "networkdiskcache.h"

NetworkDiskCache::NetworkDiskCache(QObject * parent)
        : QNetworkDiskCache(parent)
{
    QDir dir;
    dir.mkpath(QDir::homePath() + "/.mosaix/cache");
    dir.cd(QDir::homePath() + "/.mosaix/cache");

    setCacheDirectory(dir.path());
}
