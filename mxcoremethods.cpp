#include "mxcoremethods.h"
#include <QSettings>
#include <QtDebug>
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
