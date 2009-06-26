#include "networkaccessmanager.h"
#include "networkdiskcache.h"
#include "networkcookiejar.h"
#include "MXSettings.h"
NetworkCookieJar * NetworkAccessManager::pNetworkCookieJar = 0;
NetworkDiskCache * NetworkAccessManager::pNetworkDiskCache = 0;
int NetworkAccessManager::pRefCount = 0;

NetworkAccessManager::NetworkAccessManager(QObject * parent)
        : QNetworkAccessManager(parent)
{
	pErrorPage = tr("<center><table width='100%' height='100%'>"
					"<tr align='center' valign='middle'><td>"
					"<table><tr align='left'><td><img src=':/errors/not-found.png'>"
					"<big><b>Page %1 not found.</b></big><ul>"
					"<li> Please check typed adress, it can be invalid."
					"<li> Please check your connection.</ul>"
					"</td></tr></table></td></tr></table></center>");

	if(pRefCount == 0)
    {
		pNetworkDiskCache = new NetworkDiskCache();
		pNetworkCookieJar = new NetworkCookieJar();
    }
	pRefCount++;

	setCache(pNetworkDiskCache);
	pNetworkDiskCache->setParent(0);

	setCookieJar(pNetworkCookieJar);
	pNetworkCookieJar->setParent(0);

        pAuthenticationDialog =
                        new AuthenticationDialog();

    connect(this, SIGNAL(authenticationRequired(QNetworkReply *, QAuthenticator *)),
            this, SLOT(authenticate(QNetworkReply *, QAuthenticator *)));
	connect(this, SIGNAL(proxyAuthenticationRequired(const QNetworkProxy &, QAuthenticator *)),
			this, SLOT(authenticateProxy(const QNetworkProxy &, QAuthenticator *)));
	connect(this, SIGNAL(finished(QNetworkReply *)),
			this, SLOT(checkNetworkReply(QNetworkReply *)));
	connect(this, SIGNAL(sslErrors(QNetworkReply *, QList<QSslError>)),
			this, SLOT(processSslErrors(QNetworkReply *, QList<QSslError>)));
}

NetworkAccessManager::~NetworkAccessManager()
{
	if(pRefCount == 1)
    {
		delete pNetworkDiskCache;
		delete pNetworkCookieJar;
    }
	pRefCount--;
}

void NetworkAccessManager::authenticate(QNetworkReply * /*reply*/,
                                        QAuthenticator * authenticator)
{
	if(pAuthenticationDialog->exec() == QDialog::Accepted)
    {
		authenticator->setUser(pAuthenticationDialog->user());
		authenticator->setPassword(pAuthenticationDialog->password());
    }
}

void NetworkAccessManager::authenticateProxy(const QNetworkProxy & proxy,
											 QAuthenticator * authenticator)
{

		authenticator->setUser(pAuthenticationDialog->user());
		authenticator->setPassword(pAuthenticationDialog->password());

}

void NetworkAccessManager::checkNetworkReply(QNetworkReply * reply)
{


	if(reply->error() != QNetworkReply::NoError)
	{
		QTextStream out(stderr);
		out << "FI: " << reply->url().toString() << " - " << reply->error() << endl;
	}

/*	if(reply->error() != QNetworkReply::NoError &&
	   myTab->url() == reply->url())
	{
		myTab->setHtml(pErrorPage.arg(reply->url().toString()));
        }*/

	if(reply->url().scheme() == "mailto" ||
	   reply->url().scheme() == "ftp")
	{
		QDesktopServices::openUrl(reply->url());
	}
}

void NetworkAccessManager::processSslErrors(QNetworkReply * reply,
											const QList<QSslError> & errors)
{
	QTextStream out(stderr);
	out << "SSL: " << " - " << reply->url().toString() << " - " << errors[0].error() << endl;

	reply->ignoreSslErrors();
}
