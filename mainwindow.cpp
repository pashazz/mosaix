#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), core (new MXCoreMethods)
{
    load();
  hdata = new HotlinkData(op.hotlinkList);

    ui->setupUi(this);
    createWindow();
    createMenus();
    createToolbars();
    createHotlinkBar();
    connectAll();
    initMgr();
    createOtherMenus();
    statusBar()->showMessage(tr("For help, press F1"));

if (qApp->arguments().count() == 1)
    openUrl(op.homePage);
else
    openUrl(qApp->arguments().at(1));
//managerviews
tabs << tr("Session History") << tr("Global History") << "src" << tr("Hotlist View") << tr("Cache View") << tr("News View") << tr("Help View") ;
ui->tabLeft->setTabText(0, tabs.at(0));
curIndex = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus(){
    //connects

    makeHotlistsMenu();
ui->txtSource->setFont(op.srcFont);

    //tuning
    ui->actExit->setMenuRole(QAction::QuitRole);
    ui->actAbout->setMenuRole(QAction::AboutRole);
    ui->actSettings->setMenuRole(QAction::ApplicationSpecificRole);
    //Exit statustip is different
#ifdef Q_WS_X11
    ui->actExit->setStatusTip(tr("Quit Mosaix for Linux/BSD"));
#endif

#ifdef Q_WS_MAC
   QString m;
   m.append("Mac OS X ");
   switch(QSysInfo::MacintoshVersion) {
   case QSysInfo::MV_10_0:
       m.append("Cheetah");     break;
   case QSysInfo::MV_10_1:
       m.append("Puma");         break;
   case QSysInfo::MV_10_2:
       m.append("Jaguar";       break;
   case QSysInfo::MV_10_3:
       m.append("Panther");     break;
   case QSysInfo::MV_10_4:
       m.append("Tiger");       break;
   case QSysInfo::MV_10_5:
       m.append("Leopard");     break;
   case QSysInfo::MV_10_6:
       m.append("Show Leopard");
   }
   ui->actExit->setStatusTip(tr("Quit Mosaix for %1").arg(m)));

#endif

#ifdef Q_WS_WIN
   QString wv
   wv.append("Windows ");
   switch (QSysInfo::WindowsVersion) {
       case QSysInfo::WV_32s:
               wv.append ("3.1");   break;
       case QSysInfo::WV_95:
               wv.append("95");     break;
       case QSysInfo::WV_98:
               wv.append("98");     break;
       case QSysInfo::WV_Me:
               wv append("ME");     break;
       case QSysInfo::WV_NT:
               wv.append("NT");     break;
       case QSysInfo::WV_2000:
               wv.append("2000");   break;
       case QSysInfo::WV_XP:
               wv.append("XP");     break;
       case QSysInfo::WV_2003:
               wv.append("Server 2003");    break;
       case QSysInfo::WV_VISTA:
               wv.append("Vista");  break;
       case QSysInfo::WV_WINDOWS7
               wv.append("7");      break;
       case QSysInfo::WV_CE:
    void makeGroup(const MXBookmarkList &list,  QMenu *parent = 0);
    void makeTree(const MXBookmarkList &list, QTreeWidgetItem *treeParent = 0);
           wv.append("CE");         break;
       case QSysInfo::WV_CENET:
           vw.append("CE .NET");    break;
       case QSysInfo::WV_CE_5:
           wv.append("CE 5");        break;
       case QSysInfo::WV_CE_6:
           wv.append("CE 6");
    }
ui->actExit->setStatusTip(tr("Quit Mosaix for %1").arg(wv);
#endif

//create context menus
//toolbars context menu
 cmToolbars = new QMenu (this);

cmToolbars->addAction(ui->actMosaicTb);
cmToolbars->addAction(ui->actWebTb);
cmToolbars->addAction(ui->actManager);
cmToolbars->addAction(ui->actLocTb);
cmToolbars->addAction(ui->actNcsa);
cmToolbars->addSeparator();
cmToolbars->addAction(ui->actHotlinkTb);
cmToolbars->addAction(ui->actStatus);
cmToolbars->addSeparator();
cmToolbars->addAction(ui->actManagerConf);
cmToolbars->addAction(ui->actHBarConf);
cmToolbars->addSeparator();
cmToolbars->addAction(ui->actToolConf);
cmToolbars->addAction(ui->actButText);

cmToolbars->addAction(ui->actDefaultLayout);

connect (ui->statusBar, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onToolbarMenu(QPoint)), Qt::DirectConnection);
connect (ui->tbMosaic, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onToolbarMenu(QPoint)), Qt::DirectConnection);
connect(ui->tbWeb, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onToolbarMenu(QPoint)), Qt::DirectConnection);
connect (ui->tbLocation, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onToolbarMenu(QPoint)), Qt::DirectConnection);
//connect (ui->tbGlobe, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onToolbarMenu(QPoint)), Qt::DirectConnection);

createBrowserMenu();
//create a hotlink menu
cmHotTree = new QMenu (this);
cmHotTree->addAction(ui->actHotlinkPropreties);
cmHotTree->addAction(ui->actHotDelete);
cmHotTree->addSeparator();
cmHotTree->addAction(ui->actAlphabet);



}
void MainWindow::createToolbars(){
    //first, Mosaic toolbar
if (op.openFile)
    ui->tbMosaic->addAction(ui->actOpen);
if (op.saveFile)
    ui->tbMosaic->addAction(ui->actSave);
ui->tbMosaic->addSeparator();
if (op.print)
    ui->tbMosaic->addAction(ui->actPrint);
if (op.printPreview)
    ui->tbMosaic->addAction(ui->actPrintPr);
ui->tbMosaic->addSeparator();
if (op.copy)
    ui->tbMosaic->addAction(ui->actCopy);
if (op.paste)
    ui->tbMosaic->addAction(ui->actPaste);
ui->tbMosaic->addSeparator();
if (op.find)
    ui->tbMosaic->addAction(ui->actFind);
if(op.searchCache) {

    //connect HERE

    ui->tbMosaic->addAction(ui->scache);

}
ui->tbMosaic->addSeparator();

if (op.managerViewsTB)
    ui->tbMosaic->addAction(ui->actManager);

ui->tbMosaic->addSeparator();

/*if (op.help)
    ui->tbMosaic->addAction(ui->actHelp);
*/
//code to check separators

ui->tbMosaic->setVisible(op.mosaic);


//then, Web Toolbar
if (op.back)
    ui->tbWeb->addAction(ui->actBack);
if (op.forward)
    ui->tbWeb->addAction(ui->actForward);
ui->tbWeb->addSeparator();
if (op.noimages) {
    //copy of "reload text only"
    QAction *act = new QAction ("Rel Img", this); //Find icon, idiot!
    act->setToolTip(tr("Don`t Reload Images"));
    act->setStatusTip(tr("When reloading page,get images from local cache"));

}
if (op.reload)
    ui->tbWeb->addAction(ui->actReload);
ui->tbWeb->addSeparator();
if (op.home)
    ui->tbWeb->addAction(ui->actHome);
if (op.stop)
    ui->tbWeb->addAction(ui->actStopTransf); //find icon!
ui->tbWeb->addSeparator();
if (op.news)
    ui->tbWeb->addAction(ui->actNews);
if (op.email)
    ui->tbWeb->addAction(ui->actMail);
if (op.curhotlist)
    ui->tbWeb->addAction(ui->actAdd2hot);
ui->tbWeb->setVisible(op.web);

//then Location toolbar
//first, layout
yes = new QPushButton (QIcon(":/icons/icons/yes.png"),"", this);
connect (yes, SIGNAL(clicked()), this, SLOT(loadPage()));
yes->setFlat(true);
yes->setToolTip(tr("Load URL"));
ui->tbLocation->addWidget(yes);
stop = new QPushButton (QIcon(":/icons/icons/process-stop.png"), "", this);
connect(stop, SIGNAL(clicked()), ui->webView, SLOT(stop()));
stop->setEnabled(false);
stop->setFlat(true);
stop->setToolTip(tr("Cancel Load"));
ui->tbLocation->addWidget(stop);
addr = new QComboBox (this);
addr->setEditable(true);
addr->setToolTip(tr("URL"));
addr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

//connect
ui->tbLocation->addWidget(addr);
//visiblity
ui->tbLocation->setVisible(op.location);
ui->actLocTb->setChecked(op.location);
//then NCSA Globe
//QLabel *globe = new QLabel (this);
///globe->setCursor(Qt::OpenHandCursor);
///globe->setPixmap(QPixmap(":/icons/icons/minilogo.png"));
//ui->tbGlobe->addWidget(globe);

//style
if (op.buttontext){
      ui->tbMosaic->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbWeb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }
//set buttons checked or no (toolbars)
ui->actButText->setChecked(op.buttontext);
ui->actMosaicTb->setChecked(op.mosaic);
ui->actWebTb->setChecked(op.web);
ui->actHotlinkTb->setChecked(op.hotlinkbar);
ui->actStatus->setChecked(op.statusbar);
ui->actStopTransf->setEnabled(false);

//set statusBar
ui->statusBar->setVisible(op.statusbar);
time = new QLabel (ui->statusBar);

    //timer
progress = new QProgressBar(this);
connect (ui->webView, SIGNAL(loadProgress(int)), progress, SLOT(setValue(int)));
progress->setEnabled(false);
ui->statusBar->addPermanentWidget(progress);

timer = new QTimer (this);
connect (timer, SIGNAL (timeout()), this, SLOT (updateTimer()));
timer->start(1000);
ui->statusBar->addPermanentWidget(time);


//add actions to Hotlink Manage toolbar




//and a Source Manager

}


void MainWindow::makeHotlistsMenu() {
QList<QTreeWidgetItem*> main;

main = hdata->treeData();
QMenu *hotlists = menuData(main);
connect (hotlists, SIGNAL(triggered(QAction*)), this, SLOT(onCustomMenuClicked(QAction*)));
menuBar()->insertMenu(ui->menu_Tools->menuAction(), hotlists);
ui->twHotlinks->addTopLevelItems(main);

ui->txtHotlist->setText(op.hotlinkList);

  }

void MainWindow::onCustomMenuClicked(QAction *act) { //slot on custom menu triggered
if (!act->statusTip().isEmpty())
    openUrl(act->statusTip());

}



void MainWindow::openUrl(QString url) {
ui->webView->load (QUrl(guessUrlFromString(url)));

}

void MainWindow::on_actExit_triggered()
{
    this->close();
}


void MainWindow::on_actButText_triggered(bool checked)
{
    if (checked) {
          ui->tbMosaic->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbWeb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}
    else {
          ui->tbMosaic->setToolButtonStyle(Qt::ToolButtonIconOnly);
    ui->tbWeb->setToolButtonStyle(Qt::ToolButtonIconOnly);}
core->writeSetting("ButtonText", "Options", checked, op.tbConfig);

}

void MainWindow::updateTimer() {
    //checking settings
    QString msg;
    if (op.showDay)
        msg.append(QDateTime::currentDateTime().toString("ddd"));
    if (op.showDate)
        msg.append(QDateTime::currentDateTime().toString(" dd.MM.yyyy"));
    if (op.showTime)
        msg.append(QDateTime::currentDateTime().toString(" h:mm:ss"));
    time->setText(msg.trimmed());
    time->update();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    saveMySettings();
   e->accept();

}



void MainWindow::on_actHome_triggered()
{
    openUrl(op.homePage);
}

void MainWindow::on_actMosaicTb_triggered(bool checked)
{
    ui->tbMosaic->setVisible(checked);
}



void MainWindow::on_actWebTb_triggered(bool checked)
{
    ui->tbWeb->setVisible(checked);
}

void MainWindow::on_actLocTb_triggered(bool checked)
{
    ui->tbLocation->setVisible(checked);
}

void MainWindow::onToolbarMenu(QPoint p) {
   QWidget* w = static_cast<QWidget*>(QObject::sender());
   cmToolbars->exec(w->mapToGlobal(p));
}

void MainWindow::readSettings() {
    saveMySettings();
    //clean all toolbars and hostlists;
    ui->tbLocation->clear();
    ui->tbMosaic->clear();
    ui->tbWeb->clear();
    statusBar()->removeWidget(progress);
    statusBar()->removeWidget(time);

    ui->twHotlinks->clear();
    load();
    createWindow();
    createMenus();
    createToolbars();
    connectAll();
    update();

}

void MainWindow::createWindow() {
 //reading size and location settings
   resize (op.window.first);
   move (op.window.second);
   ui->webView->resize(op.webBrowser.first);
   ui->webView->move (op.webBrowser.second);
   ui->manViews->resize(op.managerLocation.first);
    ui->manViews->move(op.managerLocation.second);

    }

void MainWindow::on_actToolConf_triggered()
{
MXButtonConf *frm = new MXButtonConf(this, op);

if (frm->exec() == QDialog::Accepted)
    readSettings();
}

void MainWindow::load() {
   QString conf_file = QDir::homePath() + CONFFILE;
   QString conf_dir = QDir::homePath() + CONFDIR;
    QTextStream out (stdout);
   QSettings *stg;
   stg = new QSettings (conf_file, QSettings::IniFormat, this);
out << tr("mosaix: reading main.ini config\n");
   stg->beginGroup("Application");
   op.homePage = stg->value("MainPage", "http://google.com").toString();
   stg->endGroup();
   stg->beginGroup("Directories");
   op.downloadDir = stg->value("DownloadDir", QDir::tempPath()).toString();
   op.historyFile = stg->value("HstoryFile", "").toString();
   stg->endGroup();
   stg->beginGroup("Window");
   op.globalHistory = stg->value("GlobalHistory", true).toBool();
   op.sessionHistory = stg->value("SessionHistory", true).toBool();
   op.cacheManager = stg->value("CacheManager", true).toBool();
   op.showDate = stg->value("ShowDate", true).toBool();
   op.showDay = stg->value("ShowDay", true).toBool();
   op.showTime = stg->value("ShowTime", true).toBool();
   op.window.second = stg->value("Position", QPoint (0,0)).toPoint();
   op.window.first = stg->value("Size", QSize (640, 480)).toSize();
   stg->endGroup();
   //toolbars
   stg->beginGroup("Toolbars");
   op.mosaic = stg->value("Mosaic", true).toBool();
   op.web = stg->value("Web", true).toBool();
   op.managerviews = stg->value("ManagerViews",true).toBool();
   op.location = stg->value("Location", true).toBool();
   op.hotlinkbar = stg->value("Hotlink", true).toBool();
   op.statusbar = stg->value("StatusBar", true).toBool();
   stg->endGroup();
   stg->beginGroup("Proxy");
   op.httpProxy = stg->value("HhttpProxy").toString();
   stg->endGroup();

   stg->beginGroup("Cache");
   op.cacheDir = stg->value("Directory").toString();
   op.cacheLimit = stg->value("Limit").toInt();
   stg->beginGroup("Mail");
  op.mailName = stg->value("Name").toString();
  op.mailPassword = stg->value("Password").toString();
  op.mailHost = stg->value("Host").toString();
  op.mailAddress = stg->value("Address").toString();
  op.mailPort = stg->value("Port").toInt();
  stg->endGroup();
  stg->beginGroup("Files");
  op.tbConfig = stg->value("ToolBarConfig", conf_dir + "/toolbars.ini").toString();
  op.aConfig = stg->value("AudioConfig", conf_dir + "/audio.ini").toString();
  op.miscConfig = stg->value("MiscConfig", conf_dir + "/misc.ini").toString();
  op.hotlinkList = stg->value("HotlinkList", conf_dir + "/hotlinks/DEFAULT1.HOT").toString();

  op.hotBarConfig = stg->value("HotlinkBarConfig", conf_dir+ "/hotlinkbar.ini").toString();
  stg->endGroup();
delete stg;
stg = new QSettings (op.tbConfig, QSettings::IniFormat, this);
out << tr("mosaix: reading Toolbars\n");
stg->beginGroup("Mosaic");
op.openFile = stg->value("OpenFile", true).toBool();
op.saveFile = stg->value("SaveFile", true).toBool();
op.print = stg->value("Print", true).toBool();
op.printPreview = stg->value("PrintPreview", true).toBool();
op.copy = stg->value("Copy", true).toBool();
op.paste = stg->value("Paste", true).toBool();
op.find = stg->value("Find", true).toBool();
op.searchCache = stg->value("SearchCache", true).toBool();
op.managerViewsTB = stg->value("ManagerViews",true).toBool();
op.help = stg->value("Help", true).toBool();
stg->endGroup();
stg->beginGroup("Web");
op.back = stg->value("Back",true).toBool();
op.forward = stg->value("Forward", true).toBool();
op.noimages = stg->value("NoImages", true).toBool();
op.reload = stg->value("Reload", true).toBool();
op.home = stg->value("Home", true).toBool();
op.stop = stg->value("Stop", true).toBool();
op.news = stg->value("News",true).toBool();
op.email = stg->value("E-Mail", true).toBool();
op.add2hot = stg->value("Add2Hot",true).toBool();
op.curhotlist = stg->value("CurHotList", true).toBool();

stg->endGroup();
stg->beginGroup("Options");
op.buttontext = stg->value("ButtonText", false).toBool();
op.srcFont = stg->value("SrcFont").value<QFont>();


stg->endGroup();
delete stg;
out  << "mosaix:reading locations\n";


stg = new QSettings (op.miscConfig, QSettings::IniFormat, this);
stg->beginGroup("Size");
QString w = "WebBrowser";
QString m = "ManagerViews";
op.webBrowser.first = stg->value(w).toSize();
op.managerLocation.first = stg->value(m).toSize();
stg->endGroup();
stg->beginGroup("Position");
op.webBrowser.second = stg->value(w).toPoint();
op.managerLocation.second = stg->value(m).toPoint();
stg->endGroup();
delete stg;

//loading hotlinks
out << tr("mosaix: loading hotlists\n");

}

void MainWindow::loadPage() {
    openUrl(addr->lineEdit()->text());

}

void MainWindow::connectAll() {
   connect (addr->lineEdit(), SIGNAL(returnPressed()), this, SLOT(loadPage()));
   connect(yes, SIGNAL (clicked()), this, SLOT(loadPage()));
    connect (stop, SIGNAL(clicked()), this, SLOT(loadPage()));
   connect (ui->webView, SIGNAL(customContextMenuRequested(QPoint)),this, SLOT(onBrowserMenu(QPoint)));
    connect (ui->webView, SIGNAL(titleChanged(QString)), this, SLOT(onTitleChanged(QString)));
connect (ui->webView, SIGNAL (iconChanged()), this, SLOT (onIconChanged()));
connect (ui->webView, SIGNAL (statusBarMessage(QString)), this, SLOT (setStatusBarMessage(QString)));
    connect (ui->actBack, SIGNAL(triggered()), ui->webView, SLOT(back()));
    connect (ui->actForward, SIGNAL (triggered()), ui->webView, SLOT(forward()));
    connect (ui->actReload, SIGNAL (triggered()), ui->webView, SLOT(reload()));
    connect (ui->actStopTransf, SIGNAL(triggered()), ui->webView, SLOT(stop()));
   connect (ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT (onUrlChanged(QUrl)));
   connect (ui->webView, SIGNAL(loadStarted()), this, SLOT(onStarted()));
   connect (ui->webView, SIGNAL (loadFinished(bool)), this, SLOT(onFinished(bool)));
   connect (ui->tabLeft, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged(int)));
}

void MainWindow::onUrlChanged(QUrl url) {
if (addr->lineEdit()->text() != url.toString())
    addr->lineEdit()->setText(url.toString());


}
void MainWindow::onStarted() {
    stop->setEnabled(true);
    ui->actStopTransf->setEnabled(true);
    progress->setEnabled(true);
    currentPage = 0;
    }

void MainWindow::onFinished(bool good) {

    stop->setEnabled(false);
       ui->actStopTransf->setEnabled(false);
    progress->setEnabled(false);
    currentPage = ui->webView->page();
    //get source
ui->txtSource->setPlainText(ui->webView->page()->mainFrame()->toHtml());
}

void MainWindow::saveMySettings() {
    //saving settings
    //toolbars
    core->writeSetting("Mosaic", "Toolbars",  ui->tbMosaic->isVisible(), QDir::homePath() + CONFFILE);
    core->writeSetting("Web", "Toolbars", ui->tbWeb->isVisible(), QDir::homePath() + CONFFILE);
    core->writeSetting("Location", "Toolbars", ui->tbLocation->isVisible(), QDir::homePath() + CONFFILE);
    core->writeSetting("StatusBar", "Toolbars", statusBar()->isVisible(), QDir::homePath() + CONFFILE);
    //write size and location of controls
    core->writeSetting("WebBrowser", "Size",  ui->webView->size(), op.miscConfig);
    core->writeSetting ("WebBrowser", "Position", ui->webView->mapToGlobal(ui->webView->pos()), op.miscConfig);
    core->writeSetting("ManagerViews", "Size", ui->manViews->size(), op.miscConfig);
    core->writeSetting("ManagerViews", "Position", ui->manViews->mapToGlobal(ui->manViews->pos()), op.miscConfig);

}

void MainWindow::on_actStatus_triggered(bool checked)
{
    statusBar()->setVisible(checked);
}
void MainWindow::createBrowserMenu() {
    cmBrowser = new QMenu (this);
    cmBrowser->addAction(ui->actSave);
    cmBrowser->addAction(ui->actSaveText);
    cmBrowser->addSeparator();
   //document header
info = new QAction (tr("Document Header Infomation"), this);
connect (info, SIGNAL(triggered()), this, SLOT(onShowInfo()));
cmBrowser->addAction(info);
cmBrowser->addSeparator();
shortcut = new QAction (tr("Create Internet Shortcut"), this);
connect (shortcut, SIGNAL(triggered()), this, SLOT(onShortcut()));
cmBrowser->addAction(shortcut);
cmBrowser->addSeparator();
spawn = new  QAction (tr("Spawn Mosaic from current page"), this);
connect (spawn, SIGNAL (triggered()), this, SLOT (onSpawn()));
cmBrowser->addAction(spawn);
cmBrowser->addSeparator();
pixel  = new QAction (tr("Pixel Color"), this);
connect (pixel, SIGNAL(triggered()), this, SLOT(onPixel()));
cmBrowser->addAction(pixel);
cmLink  =new QMenu (this);


}
void MainWindow::onBrowserMenu(QPoint p) {

   QWidget* w = static_cast<QWidget*>(QObject::sender());

r =  ui->webView->page()->mainFrame()->hitTestContent(p);
QUrl url = r.linkUrl();
if (!url.isEmpty()) {
       QMenu *cmLink = new QMenu(this);
       cmLink->addAction(ui->actCopy);
       cmLink->addSeparator();
        QAction *cmLLoad = new QAction(tr("Load Anchor to Disk"), cmLink);
       QObject::connect(cmLLoad, SIGNAL(triggered()), this, SLOT(onLoadAnchor()));
       cmLLoad->setStatusTip(tr("Save the item to the local disk"));
       cmLink->addAction(cmLLoad);
        QAction *cmLAdd = new QAction(tr("Add Anchor to Hotlist"), cmLink);
       QObject::connect(cmLAdd, SIGNAL(triggered()), this, SLOT(onAddAnchor()));
       cmLAdd->setStatusTip(tr("Add Anchor to the Hotlist"));
       cmLink->addAction(cmLAdd);
        QAction *cmLInfo = new QAction(tr("Query the link for information on the file, Query Link"), cmLink);
       QObject::connect(cmLInfo, SIGNAL(triggered()), this, SLOT(onQueryLink()));
       cmLInfo->setStatusTip("");
       cmLink->addAction(cmLInfo);
       cmLink->addSeparator();
        QAction *cmLFont = new QAction(tr("Change font"), cmLink);
       QObject::connect(cmLFont, SIGNAL(triggered()), this, SLOT(onChangeFont()));
       cmLFont->setToolTip("");
       cmLink->addAction(cmLFont);
       cmLink->addSeparator();
        QAction *cmLShortcut = new QAction(tr("Create Internet Shortcut"), cmLink);
       QObject::connect(cmLShortcut, SIGNAL(triggered()), this, SLOT(onShortcut()));
       cmLShortcut->setStatusTip(tr("Create a file with the URL for drag and drop"));
       cmLink->addAction(cmLShortcut);
       cmLink->addSeparator();
        QAction *cmLSpawn = new QAction(tr("Spawn MosaiX from Anchor"), cmLink);
       QObject::connect(cmLSpawn, SIGNAL(triggered()), this, SLOT(onSpawn()));
       cmLink->addAction(cmLSpawn);
       cmLink->addSeparator();
        QAction *cmLPixel = new QAction(tr("Pixel Color"), cmLink);
       QObject::connect(cmLPixel, SIGNAL(triggered()), this, SLOT(onPixel()));
       cmLPixel->setStatusTip("");
       cmLink->addAction(cmLPixel);

       cmLink->exec(w->mapToGlobal(p));
       return;
   }


   cmBrowser->exec(w->mapToGlobal(p));

}

void MainWindow::onTitleChanged(QString title) {
setWindowTitle(tr("%1 - Mosaix").arg(title));
}




void MainWindow::on_actCopy_triggered()
{

}
void MainWindow::onIconChanged() {
    setWindowIcon(ui->webView->icon());
}
void MainWindow::setStatusBarMessage(QString msg) {
   ui->statusBar->showMessage(msg);
}

void MainWindow::on_actDefaultLayout_triggered()
{

}



QUrl MainWindow::guessUrlFromString(const QString &string)
{
    QString urlStr = string.trimmed();
    QRegExp test(QLatin1String("^[a-zA-Z]+\\:.*"));

    // Check if it looks like a qualified URL. Try parsing it and see.
    bool hasSchema = test.exactMatch(urlStr);
    if (hasSchema) {
        QUrl url = QUrl::fromEncoded(urlStr.toUtf8(), QUrl::TolerantMode);
        if (url.isValid())
            return url;
    }

    // Might be a file.
    if (QFile::exists(urlStr)) {
        QFileInfo info(urlStr);
        return QUrl::fromLocalFile(info.absoluteFilePath());
    }

    // Might be a shorturl - try to detect the schema.
    if (!hasSchema) {
        int dotIndex = urlStr.indexOf(QLatin1Char('.'));
        if (dotIndex != -1) {
            QString prefix = urlStr.left(dotIndex).toLower();
            QByteArray schema = (prefix == QLatin1String("ftp")) ? prefix.toLatin1() : "http";
            QUrl url =
                QUrl::fromEncoded(schema + "://" + urlStr.toUtf8(), QUrl::TolerantMode);
            if (url.isValid())
                return url;
        }
    }

    // Fall back to QUrl's own tolerant parser.
    QUrl url = QUrl::fromEncoded(string.toUtf8(), QUrl::TolerantMode);

    // finally for cases where the user just types in a hostname add http
    if (url.scheme().isEmpty())
        url = QUrl::fromEncoded("http://" + string.toUtf8(), QUrl::TolerantMode);
    return url;
}

void MainWindow::on_twHotlinks_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
   if (!item->text(1).isEmpty())
       openUrl(item->text(1));

}


void MainWindow::onShowInfo() {}
void MainWindow::onPixel(){}
void MainWindow::onSpawn(){}
void MainWindow::onShortcut(){}

//yanex сделай эти методы

void MainWindow::onLoadAnchor() {}
void MainWindow::onAddAnchor() {}
void MainWindow::onQueryLink() {}
void MainWindow::onChangeFont() {}

void MainWindow::on_actPresent_triggered(bool checked)
{
       if (checked)
       ui->webView->showMaximized();
   else
       ui->webView->showNormal();
}

void MainWindow::createHotlinkBar() {
  QSettings  *stg = new QSettings (op.hotBarConfig, QSettings::IniFormat, this);
QStringList groups = stg->childGroups();
QString group;
foreach (group, groups) {
    stg->beginGroup(group);

    QString url = stg->value("url").toString();
    QString name = stg->value("name").toString();
   //Yanex дальше сам


}
}

void MainWindow::on_actAdd2hot_triggered()
{

}


void MainWindow::on_actHotlinkPropreties_triggered()
{
        QStringList data;
    QTreeWidgetItem *w = ui->twHotlinks->currentItem();
    MXHotlinkProperties *pr;
if (w->columnCount() == 1){
    pr = new MXHotlinkProperties(this, true, false, QStringList(w->text(0)));
}
else {
    data.append(w->text(0));
    data.append(w->text(1));
    data.append(w->text(2));
  pr = new MXHotlinkProperties(this, false, false, data);
  //здесь анпрямую подключаем

}
connect (pr, SIGNAL (onSavingProperties(QString,QString,QDateTime,int)), this, SLOT(onHLProperties(QString,QString,QDateTime,int)));
pr->exec();
}
void MainWindow::alphabetize(QTreeWidgetItem *parent ) {
if (parent == 0) {parent = ui->twHotlinks->topLevelItem(0);}
parent->sortChildren(0, Qt::AscendingOrder);
//получаем группу  -  мы сохраняем имя группы (User MenuX) в menuIDS
//гарантируется, что индексы menuIDS и menuNames совпадают

readSettings();


}



void MainWindow::on_actAlphabet_triggered()
{

  alphabetize();
}

void MainWindow::on_twHotlinks_customContextMenuRequested(QPoint pos)
{
    QWidget *w = dynamic_cast<QWidget*>(sender());
   cmHotTree->exec(w->mapToGlobal(pos));
}

void MainWindow::on_txtHotlist_textChanged(QString )
{
    op.hotlinkList = ui->txtHotlist->text();
}



void MainWindow::on_actHotDelete_triggered()
{



}

void MainWindow::on_actOpen_triggered()
{
    bool *ok;
    QString url = QInputDialog::getText(this, " ", tr("Open Document:"), QLineEdit::Normal, "", ok, Qt::CustomizeWindowHint |Qt::WindowTitleHint);
    if (*ok)
        openUrl(url);
}

void MainWindow::on_actionOpenLocal_triggered()
{
    QString fileName  = QFileDialog::getOpenFileName(this, tr("Open"), op.downloadDir, tr("HTML Files(*.htm *.html);;Text files (*.txt);;All files (*.*)"));
    openUrl(fileName);
}

void MainWindow::on_actSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), op.downloadDir, tr("HTML Files(*.htm *.html);;Text files (*.txt);;All files (*.*)"));
    QString html = ui->webView->page()->mainFrame()->toHtml();
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::warning(this, tr("Error"), tr("Error save file %1: %2").arg(fileName, file.errorString()));
    QTextStream out(&file);
    out << html;
    file.close();

}

void MainWindow::on_actSaveText_triggered()
{
    QString fileName = QFileDialog::getSaveFileName( this, tr("Save As Text"),  op.downloadDir, tr("Text files (*.txt);;All files (*.*)"));
    QString text = ui->webView->page()->mainFrame()->toPlainText();
        QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::warning(this, tr("Error"), tr("Error save file %1: %2").arg(fileName, file.errorString()));
    QTextStream out(&file);
    out << text;
    file.close();
}

void MainWindow::on_actPrint_triggered()
{
    QPrintDialog printDialog (this);
    if (printDialog.exec() == QDialog::Accepted)
    {
        ui->webView->print(printDialog.printer());
            }
}

void MainWindow::on_actPrintPr_triggered()
{
    QPrintPreviewDialog *pr = new QPrintPreviewDialog (this);
  connect(pr, SIGNAL(paintRequested(QPrinter*)), ui->webView, SLOT(print(QPrinter*)));
      pr->exec();
}

void MainWindow::on_actPrSet_triggered()
{
    QPageSetupDialog *pg = new QPageSetupDialog (this);
    pg->exec();
}

void MainWindow::on_cmdSourceSave_clicked()
{
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), op.downloadDir, tr("HTML Files(*.htm *.html);;Text files (*.txt);;All files (*.*)"));
    QString html = ui->txtSource->toPlainText();
    QFile file (fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        QMessageBox::warning(this, tr("Error"), tr("Error save file %1: %2").arg(fileName, file.errorString()));
    QTextStream out(&file);
    out << html;
    file.close();
}
void MainWindow::onTabChanged(int i) {

    const int ignore = 2; //source view
   for (int x =0; x <= ui->tabLeft->count(); ++x)
    {
           ui->tabLeft->setTabText(x, "");

   }
   if (i != ignore)
    ui->tabLeft->setTabText(i, tabs.at(i));
   //set menu;
QMenu *toDelete = getMenuForItem(curIndex);
if  (toDelete != 0) {
    menuBar()->removeAction(toDelete->menuAction());}

   curIndex = i;
   QMenu *menu = getMenuForItem(i);
   if (menu != 0) {
       menuBar()->insertMenu(ui->menu_Edit->menuAction(),menu );}



}

void MainWindow::loadPlugins() {
           plugdir = QDir(QDir::homePath() + PLUGINS_DIR);

QString fn;
    foreach ( fn, plugdir.entryList(QDir::Files)) {
       QPluginLoader ldr (plugdir.absoluteFilePath(fn));
       QObject *plugin = ldr.instance();
       if (plugin) {
           addPlugin(plugin);
           pluginFilenames += fn;

    }
   }
}

void MainWindow::addPlugin(QObject *pl) {
    MXDownloadInterface *down = qobject_cast<MXDownloadInterface*> (pl);
    if (down){
       plugins.append(down);

    }
}



void MainWindow::changeEvent(QEvent *e)

{
   QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        //managerviews
tabs << tr("Session History") << tr("Global History") << "src" << tr("Hotlist View") << tr("Cache View") << tr("News View") << tr("Help View") ;
ui->tabLeft->setTabText(0, tabs.at(0));
//status
statusBar()->showMessage(tr("For help, press F1"));
default:
;

}
}

    void MainWindow::initMgr() {
//network acess manager coming soon
cache = new QNetworkDiskCache (this);
cache->setCacheDirectory(op.cacheDir);
cache->setMaximumCacheSize(op.cacheLimit);
netmgr = new QNetworkAccessManager (this);
netmgr->setCache(cache);
ui->webView->page()->setNetworkAccessManager(netmgr);


    }
QMenu* MainWindow::getMenuForItem (int index) {
switch (index) {
        case 0:
        return ui->mnuHistory;
        case 2:
        return srcManager;
        case 3:
        return /*hotlistManager;*/ 0;
        case 4:
        return cacheManager;
        default:
        return 0;
    }
}

void MainWindow::createOtherMenus() {
    srcManager = new QMenu (tr("Source M&anager"),this);
    srcManager->addAction(ui->actSrcFont);

    cacheManager = new QMenu (tr("Cache M&anager"), this);
    cacheManager->addAction(ui->scache);
    cacheManager->addSeparator();
    cacheManager->addAction(ui->actCacheDelete);
    cacheManager->addSeparator();
    cacheManager->addAction(ui->actCacheOptions);
    //hotlist manager coming soon

}

void MainWindow::on_actSrcFont_triggered()
{
    QFontDialog dlg (this);
    bool ok;
    QFont font = QFontDialog::getFont(&ok, op.srcFont, this);
    if (ok) {
        ui->txtSource->setFont(font);
        core->writeSetting("SrcFont", "Options", font, op.tbConfig);

    }
}
void MainWindow::createManager() {
    //set a font for source manager
    ui->txtSource->setFont(op.srcFont);
}

void MainWindow::on_actAbout_triggered()
{
AboutDialog *ab = new AboutDialog (this);
ab->exec();

}
QMenu* MainWindow::menuData(QList<QTreeWidgetItem*> wd) {
    /*!
       эта функция просто принимает результаты treeData и конвертирует их в QMenu

       */

    QMenu *menu = new QMenu (tr("Hotl&ists"), this);
   wd = hdata->treeData();
   foreach (QTreeWidgetItem *w, wd) {
    //set TOP-LEVEL menu
    QMenu *toplevel = new QMenu (w->text(0),this);
    ui->cbGroups->addItem(w->text(0));
    for (int i = 0; i < w->childCount(); ++i) {
        QMenu *mnu = new QMenu (w->child(i)->text(0),this);
        if (w->child(i)->childCount() != 0) { //menu
            makeMenu(mnu, w->child(i));
            toplevel->addMenu(mnu);
            ui->cbGroups->addItem(w->child(i)->text(0));
        }
        else {
            QAction *act = new QAction(this);
           act->setText(w->child(i)->text(0));
           act->setStatusTip(w->child(i)->text(1));
           toplevel->addAction(act);
        }
        }
    menu->addMenu(toplevel);

}
   return menu;
    }


void MainWindow::makeMenu(QMenu* menu, QTreeWidgetItem *item) {


    for(int i = 0; i < item->childCount();++i) {
        if (item->child(i)->childCount() != 0) {
                    QMenu *mnu = new QMenu (menu);
            mnu->setTitle(item->child(i)->text(0));
            makeMenu(mnu, item->child(i));
            menu->addMenu(mnu);
            ui->cbGroups->addItem(item->child(i)->text(0));
        }
        else {
            QAction *act = new QAction(menu);
           act->setText(item->child(i)->text(0));
           act->setStatusTip(item->child(i)->text(1));
           menu->addAction(act);
        }
        }

}
void MainWindow::onHLProperties(QString title, QString url, QDateTime  date, int status) {
if (ui->twHotlinks->currentItem() == 0) {
    //создаем корневой элементЪ
    return;
}
    QString oldname = ui->twHotlinks->currentItem()->text(0);
        if (status == Folder + Change) {
if(oldname != title) {
    hdata->renameTable(oldname, title);
    ui->twHotlinks->currentItem()->setText(0, title);
}
else if (status == Folder + Create){

   /*QMenu *menu = hdata->addFolder(title);
 folderCreated(menu);*/

}
    }

else {
    if (status == Item+ Change) {
        hdata->updateHotlink(oldname, title, url, date);
        ui->twHotlinks->currentItem()->setText(0, title);
        ui->twHotlinks->currentItem()->setText (1, url);
        ui->twHotlinks->currentItem()->setText(2, date.toString(DATE_FORMAT));

    }
    if (status == Item + Create)
    {
QStringList list;
list << title << url << date.toString(DATE_FORMAT);
QTreeWidgetItem *parent;
if (ui->twHotlinks->currentItem()->columnCount() == 1)
    parent = ui->twHotlinks->currentItem();
else
    parent = ui->twHotlinks->currentItem()->parent();
QAction *act =hdata->addHotlink(parent->text(0), list);
 hotlinkCreated(act, title, url, date);

    }

}
}


void MainWindow::folderCreated(QMenu *menu) {
    if (menu) {
        bool np;
        QTreeWidgetItem *parent;
        if(ui->twHotlinks->currentItem() == 0){
            //add a first-level item

        }
if (ui->twHotlinks->currentItem()->columnCount() == 1){
    parent = ui->twHotlinks->currentItem();
}
else {
    parent = ui->twHotlinks->currentItem()->parent();
    }

QTreeWidgetItem *current = new QTreeWidgetItem(parent);
if (np) { //если родитель нативен

}
    }
}
void MainWindow::hotlinkCreated(QAction *act, QString title, QString url, QDateTime date) {}

