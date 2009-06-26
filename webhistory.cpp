#include "webhistory.h"
#include "webhistoryitem.h"
#include "MXSettings.h"
WebHistory::WebHistory(QObject * parent)
		: QWebHistoryInterface(parent)
{
	loadHistory();
}

WebHistory::~WebHistory()
{
	saveHistory();
}

void WebHistory::addHistoryEntry(const QString & url)
{
	if(!url.isEmpty())
	{
		WebHistoryItem * item;
		item = new WebHistoryItem(url,
								  QString()/*title*/,
								  QDateTime::currentDateTime(),
								  QIcon()/*icon*/,
								  this);
		pItems += item;
		emit itemsChanged();
	}
}

bool WebHistory::historyContains(const QString & url) const
{
	return find(url);
}

QList<WebHistoryItem *> WebHistory::items() const
{
	return pItems;
}

void WebHistory::loadHistory()
{
	QDir dir;
        dir.mkpath(QDir::homePath() + "/.mosaix");
        dir.cd(QDir::homePath() + "/.mosaix");
	QByteArray historyArray;
        QFile historyFile;
	historyFile.open(QIODevice::ReadOnly);
	while(!(historyArray = historyFile.readLine()).isEmpty())
	{
		QString url = QString::fromUtf8(historyArray.data());
		url = url.trimmed();

		QString title =
				QString::fromUtf8(historyFile.readLine().data()).trimmed();

		QDateTime dateTime =
			QDateTime::fromString(
					QString::fromUtf8(historyFile.readLine().data()).trimmed(),
					"dd.MM.yyyy hh:mm");

		// get icon

		WebHistoryItem * item =
				new WebHistoryItem(url, title, dateTime, QIcon()/*icon*/, this);
		pItems += item;
	}
	historyFile.close();
}

void WebHistory::saveHistory() const
{
	QDir dir;
        dir.mkpath(QDir::homePath() + "/.mosaix");
        dir.cd(QDir::homePath() + "/.mosaix");
	QByteArray historyArray;
	QFile historyFile(dir.path() + "/history");
	historyFile.open(QIODevice::WriteOnly);
	foreach(WebHistoryItem * item, pItems)
	{
		historyArray += item->url().toUtf8();
		historyArray += '\n';
		historyArray += item->title().toUtf8();
		historyArray += '\n';
		historyArray += item->dateTime().
							toString("dd.MM.yyyy hh:mm").
							toUtf8();
		historyArray += '\n';
//		historyArray += item->icon();
//		historyArray += '\n';
	}
	historyFile.write(historyArray);
	historyFile.close();
}

WebHistoryItem * WebHistory::find(const QString & url) const
{
	foreach(WebHistoryItem * item, pItems)
	{
		if(item->url() == url) return item;
	}
	return 0;
}

void WebHistory::clear()
{
	pItems.clear();
	emit itemsChanged();
}
