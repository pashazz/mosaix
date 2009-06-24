#ifndef MXHTLPROP_H
#define MXHTLPROP_H
#include <QDateTime>
#include <QtGui>
#include "mxcoremethods.h"
#include "config.h"
const int Stopped = 0;
const int Running = 1;
const int Folder =5;
const int Item = 10;
const int Create = 20;
const int Change = 50;

namespace Ui {
    class MXHotlinkProperties;
}

class MXHotlinkProperties : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MXHotlinkProperties)
public:
    explicit MXHotlinkProperties(QWidget *parent, bool isFolder, bool create,  QStringList data);
    virtual ~MXHotlinkProperties();
 signals:
void onSavingProperties(QString name, QString url, QDateTime time, int status);
protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::MXHotlinkProperties *m_ui;
    bool folder;
    QString oldname;
    bool isCreate;

private slots:
    void on_buttonBox_rejected();
    void on_btnTimestamp_clicked();
    void on_buttonBox_accepted();

};

#endif // MXHTLPROP_H
