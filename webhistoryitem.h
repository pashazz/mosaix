#ifndef WEBHISTORYITEM_H
#define WEBHISTORYITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class WebHistoryItem : public QObject
{
	Q_OBJECT

public:
	WebHistoryItem(QString url,
				   QString title,
				   QDateTime dateTime,
				   QIcon icon,
				   QObject * parent = 0);
	QString url() const;
	QString title() const;
	QDateTime dateTime() const;
	QIcon icon() const;


private:
	QString pUrl;
	QString pTitle;
	QDateTime pDateTime;
	QIcon pIcon;
};

#endif // WEBHISTORYITEM_H
