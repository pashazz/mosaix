#include "hotlink.h"
#include  <QtDebug>

HotlinkData::HotlinkData(QString fileName)
        : dbfile(fileName)

{
    //open new connection
       if (!QSqlDatabase::drivers().contains("QSQLITE")){
        QMessageBox::warning(0, QObject::tr("Critical error"), QObject::tr("Unable to load database SQLITE driver. You need to compile qt-sql with sqlite database support"));
        return;

   }
       QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
       db.setDatabaseName(fileName);
       if(db.open()){
           qDebug() << tr("mosaix: hotlink file open: %1 (format - SQLite3)").arg(fileName);
           //checking tables
          QStringList tables = db.tables();
          if (tables.isEmpty()) //пустая база
          {
              qDebug() << "mosaix: No tables, create TOP table";
              QSqlQuery q ("CREATE TABLE Unitiled_TOP (id INTEGER PIMARY KEY, name TEXT, url TEXT, date TEXT, sort_id INTEGER)", db);
                        }

       } else {
           qDebug() << tr("mosaix: error open file %1 - error %2").arg(fileName, db.lastError().text());}

}

QList <QTreeWidgetItem*> HotlinkData::treeData() {
QList <QTreeWidgetItem*>  par;
    QSqlDatabase db = QSqlDatabase::database();
QStringList tables = db.tables();
//берем таблицу TOP
QStringList top;
foreach (QString table, tables) {
    if (table.endsWith("_TOP")){top  << table;;}

}
foreach (QString table, top) {
    QTreeWidgetItem *parent = new QTreeWidgetItem(0);
QString display = table;

display.remove("_TOP", Qt::CaseSensitive);
parent->setText(0, display);
parent->setIcon(0,QIcon(":/icons/icons/open-folder.png"));
//working with top table
  makeTable(parent, table);
  par.append(parent);

}
return par;
}

void HotlinkData::makeTable(QTreeWidgetItem *parent, QString tableName) {
  const QString folder = ":/icons/icons/open-folder.png";
      const QString paper = ":/icons/icons/document-new.png";
      tableName = workstr(tableName);
      QString ptable = patable(tableName);
    QString sq = "SELECT * FROM " +ptable +" ORDER BY sort_id";
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    query.prepare(sq);
    if (!query.exec()) {
        qDebug() << "SQL error: " << query.lastError().text() << query.executedQuery();
    }
    int iname = query.record().indexOf("name");
    int iurl = query.record().indexOf("url");
    int idate = query.record().indexOf("date");

    while (query.next()) {
        QTreeWidgetItem *myItem = new QTreeWidgetItem(parent);
        QString name = query.value(iname).toString();
        QString url = query.value(iurl).toString();
        myItem->setText(0, name);
        myItem->setText(1, url);
        if (url != "MENU"){
        QString date = query.value(idate).toString();
         myItem->setText(2, date);
         myItem->setIcon(0, QIcon(paper));
         parent->addChild(myItem);

    }
        else {
          //menu
            makeTable(myItem, name);
            myItem->setIcon(0, QIcon(folder));
            parent->addChild(myItem);
        }
    }

}

HotlinkData::~HotlinkData() {
QSqlDatabase db = QSqlDatabase::database();
db.close();
}

QAction* HotlinkData::addHotlink(QString parentName, const QStringList  &htl) {
    parentName = workstr(parentName);
    QSqlDatabase db = QSqlDatabase::database();
//ищем родителя
    QString ptable = patable(parentName);
    QSqlQuery q;
    q.prepare("INSERT INTO "+ ptable+" (name, url, date, sort_id) VALUES (:name, :url, :date, (SELECT sort_id FROM "+ptable+" ))");

    q.bindValue(":name", htl.at(0));
    q.bindValue(":url", htl.at(1));
    q.bindValue(":date", htl.at(2));
   bool good = q.exec();
   if (good) {
       qDebug() <<"mosaix: Query done, no errors - " + htl.at(0);
       QAction *act = new QAction(htl.at(1), this);
       act->setStatusTip(htl.at(2));
       act->setText(htl.at(0));
       return act;
   }
   qDebug() << tr("mosaix: hotlink.cpp:116 error executing SQL query -  %1, query %2").arg(q.lastError().text(), q.executedQuery());
   return 0;
}

bool HotlinkData::deleteFolder(QString title) {
     title = workstr(title);
    QSqlDatabase db = QSqlDatabase::database();
    QString ptable = patable(title);
    QSqlQuery q ("DROP TABLE IF EXISTS " + ptable);
    return true;
}

void HotlinkData::renameTable(QString oldname, QString newname) {

}

QString HotlinkData::patable(QString parentname) {
      QSqlDatabase db = QSqlDatabase::database();
   QString ptable;
foreach (QString table, db.tables())
   {
        if (table == parentname) {ptable=table; break;}
        else if (table.startsWith(parentname) || table.endsWith("_TOP")) {ptable=table; break;}
    }
    return ptable;
}
bool HotlinkData::updateHotlink(QString parentname,QString oldname, QString name, QString url, QDateTime date) {
    parentname = workstr(parentname);
    QString ptable = patable(parentname);
    QString sq = "UPDATE "+ptable+" SET name = :name,url = :url,date = :date WHERE name = :oldname";


}
QMenu* HotlinkData::addFolder(QString parentname, QString title) {

parentname = workstr(parentname);
      QSqlDatabase db = QSqlDatabase::database();
   QString ptable = patable(parentname);

     if (parentname.isEmpty()) {title.append("_TOP");}
   QSqlQuery q ("CREATE TABLE " + title +" (id INTEGER PIMARY KEY, name TEXT, url TEXT, date TEXT)", db);
   if (!parentname.isEmpty()) {
      QSqlQuery query;
      title = workstr(title);
         query.prepare("INSERT INTO "+ ptable+" (name, url, date, sort_id) VALUES (:name, :url, :date, (SELECT sort_id FROM "+ptable+" ))");
q.bindValue(":name", title);
q.bindValue(":url", "MENU");
q.bindValue(":date", "N/A");

if (!q.exec()) {qDebug() << "SQL error: " + q.lastError().text() + ", query " + q.executedQuery();}
   }
   QMenu *menu = new QMenu (printable(title), 0);
   return menu;
}
bool HotlinkData::deleteHotlink(QString parentname,QString title) {
    QSqlDatabase db = QSqlDatabase::database();
    parentname = workstr(parentname);
    QString ptable = patable(parentname);
qDebug() << ptable << title;
    QSqlQuery q;
q.prepare("DELETE FROM " + ptable +" WHERE name=:name");
q.bindValue(":name", title);
bool good = q.exec();
if (good)
  qDebug() <<"mosaix: Query done, no errors - " + title+" deleted";
else {
     qDebug() << tr("mosaix: error executing SQL query -  %1").arg(db.lastError().text());

return good;

}
}

QAction* HotlinkData::insertHotlink(QString parentName, QStringList links, QStringList htl) {
    QAction *act = addHotlink(parentName, htl);
    sort(links, parentName, false);
}

void HotlinkData::sort(QStringList links, QString parentName, bool recursive) {
    QSqlDatabase db = QSqlDatabase::database();
    parentName = workstr(parentName);
    QString ptable = patable(parentName);
    int i;
    foreach (QString link, links) {
        QSqlQuery q;
        q.prepare("UPDATE "+ ptable +" SET sort_id=:sort_id WHERE name=:name");
        q.bindValue(":sort_id", i);
        q.bindValue(":name", link);
        if(!q.exec()) {
            qDebug() << "SQL error: " + q.lastError().text() << q.executedQuery();
        }
        //использование good
        i++;
        //это таблица?
        if (recursive){
        if (db.tables().contains(link) || db.tables().contains(workstr(link)))
            {
    //получим items
            QSqlQuery getItems ("SELECT name FROM " + link);
            qDebug () << "Mosaix: " + getItems.lastError().text();
            QStringList items;
            int itemid = getItems.record().indexOf("name");
            while (getItems.next()) {
             items.append(getItems.value(itemid).toString());
             }
            items.sort();
            sort(items, link);}
    }
    }

}
QMenu* HotlinkData::insertFolder(QString parentName, QStringList links, QString title) {
    addFolder(parentName, title);
    sort(links, parentName, false);
}
