#ifndef MXINPUT_H
#define MXINPUT_H

#include <QtGui/QDialog>

namespace Ui {
    class MXInput;
}

class MXInput : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(MXInput)
public:
    explicit MXInput(QWidget *parent = 0);
    virtual ~MXInput();
    QString text() ;

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::MXInput *m_ui;

private slots:
    void on_cmdCancel_clicked();
    void on_cmdOK_clicked();
};

#endif // MXINPUT_H
