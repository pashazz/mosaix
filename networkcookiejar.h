#ifndef NETWORKCOOKIEJAR_H
#define NETWORKCOOKIEJAR_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class NetworkCookieJar : public QNetworkCookieJar
{
    Q_OBJECT

public:
    NetworkCookieJar(QObject * parent = 0);
    ~NetworkCookieJar();

private:
    void storeCookies() const;
    void loadCookies();
};

#endif // NETWORKCOOKIEJAR_H
