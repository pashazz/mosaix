#ifndef MXHTLPROP_H
#define MXHTLPROP_H
#include <QDateTime>
#include <QtGui>
#include "mxcoremethods.h"
#include "config.h"


namespace Ui {
    class MXHotlinkProperties;
}

class MXHotlinkProperties : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MXHotlinkProperties)
public:
    explicit MXHotlinkProperties(QWidget *parent, bool isFolder, QStringList data, QString config, QString menuID, QString itemID = "");
    virtual ~MXHotlinkProperties();

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::MXHotlinkProperties *m_ui;
    QString conf;
    bool folder;
    QString menu;
    QString item;
    MXCoreMethods *core;

private slots:
    void on_buttonBox_rejected();
    void on_btnTimestamp_clicked();
    void on_buttonBox_accepted();
};

#endif // MXHTLPROP_H
