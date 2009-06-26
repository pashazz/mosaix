#ifndef NETWORKDISKCACHE_H
#define NETWORKDISKCACHE_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class NetworkDiskCache : public QNetworkDiskCache
{
    Q_OBJECT

public:
    NetworkDiskCache(QObject * parent = 0);
};

#endif // NETWORKDISKCACHE_H
