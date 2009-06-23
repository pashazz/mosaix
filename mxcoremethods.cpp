#include "mxcoremethods.h"
#include <QSettings>
#include <QtDebug>
#include <QStringList>
MXCoreMethods::MXCoreMethods()
{
    ;
}
void MXCoreMethods::writeSetting(const QString &key , const QString &group, const QVariant &value, const QString &file) {
   QSettings *stg = new QSettings (file, QSettings::IniFormat, this);
    stg->beginGroup(group);
    stg->setValue(key, value);
    stg->endGroup();
    stg->sync();
qDebug() << tr ("mosaix:settings wrote in config file %1: group %2, key %3, value %4").arg(file, group,key, value.toString());
}

QString MXCoreMethods::getHotlinkID(QString file, QString title, bool isMenu, QString menu)
{
    if(isMenu) {
    QSettings stg  (file, QSettings::IniFormat, this);
QStringList lstGr  = stg.childGroups();
QString group;
QString gr, k;

foreach (gr, lstGr) {
    stg.beginGroup(gr);
    foreach (k, stg.allKeys()) { //first for menus
        if (k == "Menu_Name") //here get menu name
        {
            QString name = stg.value(k).toString();
            if (name == title)

            {stg.endGroup();
                qDebug() << tr ("group found: title %1, ID %2").arg(title, gr);
                return gr;}

        }

    }
    //если это не так
    stg.endGroup();
}
 }
    else {
            QSettings stg  (file, QSettings::IniFormat, this);
stg.beginGroup(menu);
QStringList keys = stg.allKeys();
QString key;
foreach (key, keys) {
    //get title
    QString res = stg.value(key).toString();
    QStringList l = res.split(',');
    QString value = l.at(0);
    if (value == title){
        stg.endGroup();
        qDebug() << tr ("key found: title %1, ID %2").arg(title, key);
        return key;}


}
//если и это не так
stg.endGroup();
    }
    }
