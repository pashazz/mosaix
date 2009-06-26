#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>

class WebHistory;
class WebHistoryItem;

class LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QWidget * parent = 0);

private:
	QStringListModel * pStringListModel;

public slots:
    void setUrl(const QUrl & url);

private slots:
    void submitUrl();
	void updateCompleteList();

signals:
    void urlSubmitted(const QUrl &);
};

#endif // LINEEDIT_H
