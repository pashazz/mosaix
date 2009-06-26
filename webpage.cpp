#include "webpage.h"
#include "networkaccessmanager.h"


QNetworkAccessManager * WebPage::pDownloadManager = 0;
int WebPage::pRefCount = 0;

WebPage::WebPage(QObject * parent, QString downDir)
        : QWebPage(parent), dir(downDir)
{

	setForwardUnsupportedContent(true);

	if(pRefCount == 0)
	{
		pDownloadManager = new QNetworkAccessManager();
	}
	pRefCount++;

	NetworkAccessManager * networkAccessManager =
			new NetworkAccessManager(this);
	setNetworkAccessManager(networkAccessManager);

    connect(this, SIGNAL(downloadRequested(const QNetworkRequest &)),
            this, SLOT(download(const QNetworkRequest &)));
	connect(this, SIGNAL(unsupportedContent(QNetworkReply *)),
			this, SLOT(processContent(QNetworkReply *)));
}

WebPage::~WebPage()
{
	if(pRefCount == 1)
	{
		delete pDownloadManager;
	}
	pRefCount--;
}



QString WebPage::userAgentForUrl(const QUrl & /*url*/) const
{
    return "Mosaix 0.1 Milestone 0 (%Platform%; %Locale%)";
}

QString WebPage::chooseFile(QWebFrame * /*parentFrame*/,
							 const QString & suggestedFile)
{
	return QFileDialog::getOpenFileName(view(), tr("Upload file"),
								 suggestedFile, tr("All Files (*)"));
}

QString WebPage::saveFileName(QUrl url)
{
				   url.toString().section('/', -1);
	QString fileName =
		QFileDialog::getSaveFileName(view(), tr("Save file"),
                                                                         dir, tr("All Files (*)"));
	return fileName;
}

void WebPage::addDownload(QString fileName,
						  QNetworkReply * reply)
{

}

void WebPage::download(const QNetworkRequest & request)
{
	QString fileName = saveFileName(request.url());
	if(!fileName.isEmpty())
	{
		QNetworkReply * reply = pDownloadManager->get(request);
		addDownload(fileName, reply);
	}
}

void WebPage::processContent(QNetworkReply * reply)
{
	QTextStream out(stderr);
	out << "UC: " << reply->url().toString() << " - " << reply->error() << endl;

	if(reply->error() == QNetworkReply::NoError)
	{
		QString fileName = saveFileName(reply->url());
		if(!fileName.isEmpty())
		{
			QNetworkReply * newReply =
					pDownloadManager->get(QNetworkRequest(reply->url()));
			addDownload(fileName, newReply);
		}
	}
	reply->abort();
}
