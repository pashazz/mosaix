#ifndef MXBUTTONCONF_H
#define MXBUTTONCONF_H
#include "mxcoremethods.h"
#include <QtGui>
#include "MXSettings.h"

namespace Ui {
    class MXButtonConf;
}

class MXButtonConf : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MXButtonConf)
public:
    explicit MXButtonConf(QWidget *parent, MXOptions opt);
    virtual ~MXButtonConf();

protected:
    virtual void changeEvent(QEvent *e);


private:
    Ui::MXButtonConf *m_ui;
    MXCoreMethods *core;
    QString conf;
    void getSettings(MXOptions opt);
private slots:
    void onClick (QAbstractButton *b);
};

#endif // MXBUTTONCONF_H
