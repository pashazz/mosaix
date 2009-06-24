#ifndef HOTLINK_H
#define HOTLINK_H
#include <QtSql>
#include <QStringList>
#include <MXSettings.h>
#include <QMenu>
#include <QAction>
#include <QDateTime>
#include <QMessageBox>
#include <QtGui>
#include "config.h"


class HotlinkData: public QObject
{
    Q_PROPERTY (QString fileName READ fileName WRITE setFileName)
public:
    HotlinkData(QString fileName);
    ~HotlinkData();
    QMenu insertFolder(QString parentName,QString after,QString title); //добавлять hotlink будем ДО объекта с именем after
    QAction insertHotlink(QString parentName,QString after,const QStringList &htl);
    void remove (QString title, bool isFolder);
    void alphabetize(QString folderName);
    void alphabetize(); //for all
    bool updateTimestamp(QString title);
    bool updateTimestamp(); //for all
    QMenu* addFolder(QString parentname,QString title);
    QAction* addHotlink (QString parentName, const QStringList &htl); //добавляем hotlink в конец списка
    void deleteHotlink (QString title);
    void deleteFolder(QString title);
    QList<QTreeWidgetItem*> treeData();
    QString fileName();
    void setFileName(QString file);
        void updateHotlink(QString oldname, QString name, QString url, QDateTime date);
    void renameTable (QString oldname, QString newname);


    private:
    QString dbfile;
    void makeTable(QTreeWidgetItem *parent, QString tableName);
    QString workstr (QString s) {s = s.replace(" ", "_");return s;}
    QString printable(QString s) {s = s.replace("_", " ");return s;}


    };


#endif // HOTLINK_H
