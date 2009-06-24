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
              QSqlQuery q ("CREATE TABLE Unitiled_TOP (id INTEGER PIMARY KEY, name TEXT, url TEXT, date TEXT)", db);
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
//working with top table
  makeTable(parent, table);
  par.append(parent);

}
return par;
}

void HotlinkData::makeTable(QTreeWidgetItem *parent, QString tableName) {
    QString sq = "SELECT * FROM " + tableName;
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query (sq, db);
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
         parent->addChild(myItem);

    }
        else {
          //menu
            makeTable(myItem, name);
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
    QString ptable;
    foreach (QString table, db.tables()) {
        if (table == parentName) {ptable=table; break;}
        else if (table.startsWith(parentName) || table.endsWith("_TOP")) {ptable=table; break;}

    }
    //добавляем в таблицу
    QSqlQuery q;
    q.prepare("INSERT INTO " + ptable + " (name, url, date) VALUES (:name, :url, :date) ");
    q.bindValue(":name", htl.at(0));
    q.bindValue(":url", htl.at(1));
    q.bindValue(":date", htl.at(2));
   bool good = q.exec();
   if (good) {
       qDebug() <<"mosaix: Query done, no errors - " + htl.at(0);
       QAction *act = new QAction(htl.at(1), this);
       act->setStatusTip(htl.at(2));
       return act;
   }
   qDebug() << tr("mosaix: error executing SQL query -  %1").arg(db.lastError().text());
   return 0;
}

void HotlinkData::deleteFolder(QString title) {
     title = workstr(title);
    QSqlDatabase db = QSqlDatabase::database();
    QString ptable;
    foreach (QString table, db.tables()) {
        if (table == title) {ptable=table; break;}
        else if (table.startsWith(title) || table.endsWith("_TOP")) {ptable=table; break;}

    }
    QSqlQuery q ("DROP TABLE " + ptable);
}

void HotlinkData::renameTable(QString oldname, QString newname) {

}
void HotlinkData::updateHotlink(QString oldname, QString name, QString url, QDateTime date) {}
