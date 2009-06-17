#ifndef MXLOADER_H
#define MXLOADER_H

#include <QObject>
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QPoint>
#include <QSize>
class MXLoader : public QObject
{
public:
    MXLoader();

private:
   void createConfig();
   void load();


   //variables
    QString conf_file;
    QString conf_dir;
};

#endif // MXLOADER_H
