#include "networkcookiejar.h"

NetworkCookieJar::NetworkCookieJar(QObject * parent)
        : QNetworkCookieJar(parent)
{
    loadCookies();
}

NetworkCookieJar::~NetworkCookieJar()
{
    storeCookies();
}

void NetworkCookieJar::storeCookies() const
{
    QDir dir;
    dir.mkpath(QDir::homePath() + "/.mosaix");
    dir.cd(QDir::homePath() + "/.mosaix");
    QByteArray cookieArray;
    QList<QNetworkCookie> cookieList = allCookies();
    foreach(QNetworkCookie cookie, cookieList)
    {
        cookieArray += cookie.toRawForm(QNetworkCookie::Full);
        cookieArray += '\n';
    }
    QFile cookieFile(dir.path() + "/cookies");
    cookieFile.open(QIODevice::WriteOnly);
    cookieFile.write(cookieArray);
    cookieFile.close();
}

void NetworkCookieJar::loadCookies()
{
    QDir dir;
    dir.mkpath(QDir::homePath() + "/.mosaix");
    dir.cd(QDir::homePath() + "/.mosaix");
    QFile cookieFile(dir.path() + "/cookies");
    QList<QNetworkCookie> cookieList;
    QByteArray cookieArray;
    cookieFile.open(QIODevice::ReadOnly);
    while(!(cookieArray = cookieFile.readLine()).isEmpty())
    {
        cookieList += QNetworkCookie::parseCookies(cookieArray);
    }
    cookieFile.close();
    setAllCookies(cookieList);
}
