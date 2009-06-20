#include "mxbuttonconf.h"
#include "ui_mxbuttonconf.h"
MXButtonConf::MXButtonConf(QWidget *parent,  MXOptions opt) :
    QDialog(parent),
    m_ui(new Ui::MXButtonConf), core (new MXCoreMethods())
{
    m_ui->setupUi(this);
    getSettings(opt);
    conf = opt.tbConfig;
    connect (m_ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(onClick(QAbstractButton*)));
}

MXButtonConf::~MXButtonConf()
{
    delete m_ui;
}

void MXButtonConf::changeEvent(QEvent *e)
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
void MXButtonConf::onClick(QAbstractButton *b) {
    if ( m_ui->buttonBox->buttonRole(b) == QDialogButtonBox::AcceptRole) {
     core->writeSetting("OpenFile", "Mosaic", m_ui->cbOpenFile->isChecked(), conf);
     core->writeSetting("SaveFile", "Mosaic", m_ui->cbSaveFile->isChecked(), conf);
     core->writeSetting("Print", "Mosaic", m_ui->cbPrint->isChecked(), conf);
     core->writeSetting("PrintPreview", "Mosaic", m_ui->cbPrintPreview->isChecked(), conf);
     core->writeSetting("Copy", "Mosaic", m_ui->cbCopy->isChecked(), conf);
     core->writeSetting("Paste", "Mosaic", m_ui->cbPaste->isChecked(), conf);
     core->writeSetting("Find", "Mosaic", m_ui->cbFind->isChecked(), conf);
     core->writeSetting("SearchCache", "Mosaic", m_ui->cbFind->isChecked(), conf);
     core->writeSetting("ManagerViews", "Mosaic", m_ui->cbManager->isChecked(), conf);
     core->writeSetting("Help", "Mosaic", m_ui->cbHelp->isChecked(), conf);
     core->writeSetting("Back", "Web", m_ui->cbBack->isChecked(), conf);
     core->writeSetting("Forward", "Web", m_ui->cbForward->isChecked(), conf);
     core->writeSetting("NoImages", "Web", m_ui->cbNoImages->isChecked(), conf);
     core->writeSetting("Reload", "Web", m_ui->cbReload->isChecked(), conf);
     core->writeSetting("Home", "Web", m_ui->cbHome->isChecked(), conf);
     core->writeSetting("Stop", "Web", m_ui->cbStop->isChecked(), conf);
     core->writeSetting("News", "Web", m_ui->cbNews->isChecked(), conf);
     core->writeSetting("E-Mail", "Web", m_ui->cbMai->isChecked(), conf);
     core->writeSetting("Add2Hot", "Web", m_ui->cbAdd2hot->isChecked(), conf);
     core->writeSetting("CurHotList", "Web", m_ui->cbCurHot->isChecked(), conf);
     setResult(1);
     this->close();
 }
    else
        setResult(0);
}
void MXButtonConf::getSettings(MXOptions opt) {
m_ui->cbOpenFile->setChecked(opt.openFile);
m_ui->cbSaveFile->setChecked(opt.saveFile);
m_ui->cbPrint->setChecked(opt.print);
m_ui->cbPrintPreview->setChecked(opt.printPreview);
m_ui->cbAdd2hot->setChecked(opt.add2hot);
m_ui->cbBack->setChecked(opt.back);
m_ui->cbCopy->setChecked(opt.copy);
m_ui->cbCurHot->setChecked(opt.curhotlist);
m_ui->cbFind->setChecked(opt.find);
m_ui->cbForward->setChecked(opt.forward);
m_ui->cbHelp->setChecked(opt.help);
m_ui->cbHome->setChecked(opt.home);
m_ui->cbMai->setChecked(opt.email);
m_ui->cbManager->setChecked(opt.managerViewsTB);
m_ui->cbNews->setChecked(opt.news);
m_ui->cbNoImages->setChecked(opt.noimages);
m_ui->cbPaste->setChecked(opt.paste);
m_ui->cbReload->setChecked(opt.reload);
m_ui->cbSearchCache->setChecked(opt.searchCache);
m_ui->cbStop->setChecked(opt.stop);


}
