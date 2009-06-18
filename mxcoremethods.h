#ifndef MXCOREMETHODS_H
#define MXCOREMETHODS_H

#include <QObject>

class MXCoreMethods : public QObject
{
public:
    MXCoreMethods();
    void writeSetting (const  QString &key, const QString &group, const QVariant &value, const QString &file);
 private:


};

#endif // MXCOREMETHODS_H
