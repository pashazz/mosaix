#include "mxhtlprop.h"
#include "ui_mxhtlprop.h"

MXHotlinkProperties::MXHotlinkProperties(QWidget *parent, bool isFolder, bool create, QStringList data) :
    QDialog(parent),
    m_ui(new Ui::MXHotlinkProperties), folder (isFolder), isCreate(create)
{
    m_ui->setupUi(this);
    m_ui->txtTitle->setText(data.at(0));
    if (isFolder) {
    m_ui->lblURL->setEnabled(false);
    m_ui->txtURL->setVisible(false);
    m_ui->txtDate->setVisible(false);
    m_ui->lblDate->setEnabled(false);
    m_ui->btnTimestamp->setVisible(false);
    }
    else {
     m_ui->txtURL->setText(data.at(1));
     m_ui->txtDate->setText(data.at(2));
    }
    oldname = m_ui->txtTitle->text();
}

MXHotlinkProperties::~MXHotlinkProperties()
{
    delete m_ui;
}

void MXHotlinkProperties::changeEvent(QEvent *e)
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

void MXHotlinkProperties::on_buttonBox_accepted()
{

    QDateTime d;
int st;
st+=Running;
    if(!folder){
        st += Item;

  d = d.fromString (m_ui->txtDate->text(), DATE_FORMAT);}
    else{
       m_ui->txtTitle->setText(  m_ui->txtTitle->text().replace(" ", "_"));
st += Folder;
if (isCreate) {st += Create;} else {st+=Change;}
   emit onSavingProperties( m_ui->txtTitle->text(), m_ui->txtURL->text(), d, st);

   close();
}
}



void MXHotlinkProperties::on_btnTimestamp_clicked()
{

  //get current time
    QDateTime time = QDateTime::currentDateTime();
  //get current time in string
    QString strt = time.toString(DATE_FORMAT);
    m_ui->txtDate->setText(strt);

}

void MXHotlinkProperties::on_buttonBox_rejected()
{
 close();
}
