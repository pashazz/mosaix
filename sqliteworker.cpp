#include "sqliteworker.h"
#include <QtCore>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
sqliteworker::sqliteworker()
{
    //initdb
 QSqlDatabase   db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName (QDir::homePath() + DATABASE);
    bool ok = db.open();
    if (!ok)
    {QMessageBox::critical(0, "Database Error", db.lastError().text()); return;}
    //if no tables, etc, create it.




}
