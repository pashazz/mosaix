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
    QMenu* insertFolder(QString parentName,QStringList links,QString title); //добавлять hotlink будем ДО объекта с именем after
    QAction* insertHotlink(QString parentName,QStringList links, QStringList htl);
    void remove (QString title, bool isFolder);
    void alphabetize(QString folderName);
    void alphabetize(); //for all
    bool updateTimestamp(QString title);
    bool updateTimestamp(); //for all
    QMenu* addFolder(QString parentname,QString title);
    QAction* addHotlink (QString parentName, const QStringList &htl); //добавляем hotlink в конец списка
    bool deleteHotlink (QString parentname, QString title);
    bool deleteFolder(QString title);
    QList<QTreeWidgetItem*> treeData();
    QString fileName();
    void setFileName(QString file);
    bool updateHotlink(QString parentname,QString oldname, QString name, QString url, QDateTime date);
    void renameTable (QString oldname, QString newname);
    void sort(QStringList links, QString parentName, bool recursive = true);
    private:
    QString dbfile;
    void makeTable(QTreeWidgetItem *parent, QString tableName);
    QString workstr (QString s) {s = s.replace(" ", "_");return s;}
    QString printable(QString s) {s = s.replace("_", " ");return s;}
    QString patable (QString parentname);


    };


#endif // HOTLINK_H
