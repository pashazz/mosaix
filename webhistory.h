#ifndef WEBHISTORY_H
#define WEBHISTORY_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class WebHistoryItem;

class WebHistory : public QWebHistoryInterface
{
	Q_OBJECT

public:
	WebHistory(QObject * parent = 0);
	~WebHistory();
	void addHistoryEntry(const QString & url);
	bool historyContains(const QString & url) const;
	QList<WebHistoryItem *> items() const;

private:
	QList<WebHistoryItem *> pItems;
	void loadHistory();
	void saveHistory() const;
	WebHistoryItem * find(const QString & url) const;

public slots:
	void clear();

signals:
	void itemsChanged();
};

#endif // WEBHISTORY_H
