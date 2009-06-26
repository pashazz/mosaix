#include "webhistoryitem.h"

WebHistoryItem::WebHistoryItem(QString url,
							   QString title,
							   QDateTime dateTime,
							   QIcon icon,
							   QObject * parent)
		: QObject(parent),
		  pUrl(url),
		  pTitle(title),
		  pDateTime(dateTime),
		  pIcon(icon)
{

}

QString WebHistoryItem::url() const
{
	return pUrl;
}

QString WebHistoryItem::title() const
{
	return pTitle;
}

QDateTime WebHistoryItem::dateTime() const
{
	return pDateTime;
}

QIcon WebHistoryItem::icon() const
{
	return pIcon;
}
