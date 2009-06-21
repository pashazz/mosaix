#include "mxhtlprop.h"
#include "ui_mxhtlprop.h"

MXHotlinkProperties::MXHotlinkProperties(QWidget *parent, bool isFolder, QStringList data, QString config, QString menuID, QString itemID) :
    QDialog(parent),
    m_ui(new Ui::MXHotlinkProperties), conf(config), folder (isFolder), menu(menuID), item(itemID), core(new MXCoreMethods)
{
    m_ui->setupUi(this);
    m_ui->txtTitle->setText(data.at(0));
    if (isFolder) {
    m_ui->lblURL->setEnabled(false);
    m_ui->txtURL->setVisible(false);
    m_ui->txtDate->setVisible(false);
    m_ui->lblDate->setEnabled(false);

    }
    else {
     m_ui->txtURL->setText(data.at(1));
     m_ui->txtDate->setText(data.at(2));
    }
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
    //применяем изменения
    QString value;
    QString key;
    if (folder){
        key = "Menu_Name";
        value = m_ui->txtTitle->text();
    }
    else
    {
        key = item;
        value.append(m_ui->txtTitle->text() + ",");
        value.append(m_ui->txtURL->text() + ",");
        value.append(m_ui->txtDate->text());
    }
    core->writeSetting(key, menu, value, conf);
    close();

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
