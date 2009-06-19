#ifndef MXBUTTONCONF_H
#define MXBUTTONCONF_H
#include "mxcoremethods.h"
#include <QtGui>

namespace Ui {
    class MXButtonConf;
}

class MXButtonConf : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MXButtonConf)
public:
    explicit MXButtonConf(QWidget *parent, const QString &tbConf);
    virtual ~MXButtonConf();

protected:
    virtual void changeEvent(QEvent *e);


private:
    Ui::MXButtonConf *m_ui;
    MXCoreMethods *core;
    QString conf;
private slots:
    void onClick (QAbstractButton *b);
};

#endif // MXBUTTONCONF_H
