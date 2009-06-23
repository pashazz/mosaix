#include "mxinput.h"
#include "ui_mxinput.h"
QString _txt;
MXInput::MXInput(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::MXInput)
{
    m_ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

MXInput::~MXInput()
{
    delete m_ui;
}

void MXInput::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MXInput::on_cmdOK_clicked()
{
_txt = m_ui->txtInput->text();
done (1);}
QString text () {
    return _txt;
}
void MXInput::on_cmdCancel_clicked()
{
done(0);}
