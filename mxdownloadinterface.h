#ifndef MXDOWNLOADINTERFACE_H
#define MXDOWNLOADINTERFACE_H

#include <QObject>
#include <QtPlugin>

class MXDownloadInterface : public QObject
{

public:

    virtual ~MXDownloadInterface() {}
   virtual bool download (QString source, QString destination) = 0;
    virtual QString name()  const = 0;
    virtual QString about () const = 0;

};

Q_DECLARE_INTERFACE (MXDownloadInterface, "org.pashazz.mosaix.Download/0.1")

#endif // MXDOWNLOADINTERFACE_H
