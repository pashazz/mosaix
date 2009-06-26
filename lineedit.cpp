#include "lineedit.h"
#include "webhistory.h"
#include "webhistoryitem.h"

LineEdit::LineEdit(QWidget * parent)
        : QLineEdit(parent)
{
    connect(this, SIGNAL(returnPressed()), this, SLOT(submitUrl()));

	pStringListModel = new QStringListModel(this);
	QCompleter * completer = new QCompleter(pStringListModel, this);
	setCompleter(completer);

	WebHistory * webHistory =
			qobject_cast<WebHistory *>
				(QWebHistoryInterface::defaultInterface());
	connect(webHistory, SIGNAL(itemsChanged()),
			this, SLOT(updateCompleteList()));
	updateCompleteList();
}

void LineEdit::setUrl(const QUrl & url)
{
    setText(url.toString());
}

void LineEdit::submitUrl()
{
	if(QUrl(text()).scheme().isEmpty())
	{
		if(text()[0] != '/')
		{
			setText(QString("http://") + text());
		} else {
			setText(QString("file://") + text());
		}
	}
    emit urlSubmitted(QUrl(text()));
}

void LineEdit::updateCompleteList()
{
	QList<WebHistoryItem *> items =
		qobject_cast<WebHistory *>
			(QWebHistoryInterface::defaultInterface())->items();
	QStringList completeList;
	foreach(WebHistoryItem * item, items)
	{
		if(!completeList.contains(item->url()))
		{
			completeList << item->url();
		}
	}
	completeList.sort();
	pStringListModel->setStringList(completeList);
}
