#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>
#include "authenticationdialog.h"

class Tab;
class NetworkDiskCache;
class NetworkCookieJar;

class NetworkAccessManager : public QNetworkAccessManager
{
    Q_OBJECT

public:
    NetworkAccessManager(QObject * parent = 0);
    ~NetworkAccessManager();

private:
	static NetworkCookieJar * pNetworkCookieJar;
	static NetworkDiskCache * pNetworkDiskCache;
	static int pRefCount;
	QString pErrorPage;
      AuthenticationDialog  *pAuthenticationDialog;
private slots:
    void authenticate(QNetworkReply * reply,
                      QAuthenticator * authenticator);
	void authenticateProxy(const QNetworkProxy & proxy,
						   QAuthenticator * authenticator);
	void checkNetworkReply(QNetworkReply *);
	void processSslErrors(QNetworkReply * reply,
						  const QList<QSslError> & errors);
};

#endif // NETWORKACCESSMANAGER_H
