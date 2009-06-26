#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class NetworkAccessManager;


class WebPage : public QWebPage
{
    Q_OBJECT

public:
    WebPage(QObject * parent, QString downDir);
	~WebPage();

protected:
    QString userAgentForUrl(const QUrl & url) const;
	QString chooseFile(QWebFrame * parentFrame,
					   const QString & suggestedFile);

private:
	static QNetworkAccessManager * pDownloadManager;
	static int pRefCount;
	QString saveFileName(QUrl url);
	void addDownload(QString fileName,
					 QNetworkReply * reply);
QString dir;
private slots:
	void download(const QNetworkRequest & request);
	void processContent(QNetworkReply * reply);
};

#endif // WEBPAGE_H
