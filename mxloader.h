#ifndef MXLOADER_H
#define MXLOADER_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QPoint>
#include <QSize>
#include <QTextStream>
#include "MXSettings.h"
class MXLoader : public QObject
{
public:
    MXLoader();
    void start();

private:
   void createConfig();
   void load();


   //variables
    QString conf_file;
    QString conf_dir;
};

#endif // MXLOADER_H
