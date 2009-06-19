#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include "config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), core (new MXCoreMethods)
{
    load();
    ui->setupUi(this);

    createWindow();
    createMenus();
    createToolbars();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus(){
    //connects

    hotListParser();
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
    QAction *scache = new QAction (QIcon(":/icons/icons/csearch.png"), tr("Cache Srch"), this);
    scache->setToolTip(tr("Search Cache"));
    scache->setStatusTip(tr("Search Cache for a Text String"));
    //connect HERE

    ui->tbMosaic->addAction(scache);

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
//connect
yes->setFlat(true);
yes->setToolTip(tr("Load URL"));
ui->tbLocation->addWidget(yes);
stop = new QPushButton (QIcon(":/icons/icons/process-stop.png"), "", this);
//connect
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

//set statusBar
ui->statusBar->setVisible(op.statusbar);
time = new QLabel (ui->statusBar);

ui->statusBar->addPermanentWidget(time);
    //timer
timer = new QTimer (this);
connect (timer, SIGNAL (timeout()), this, SLOT (updateTimer()));
timer->start(1000);




}
void MainWindow::hotListParser() {
if (!QFile::exists(hlink)) {
    qDebug() << "mosaix: error reading hotlinks: file does not exists, hotlinks will be disabled!";
}

    QSettings *sets = new QSettings (hlink, QSettings::IniFormat, this);
QStringList groups = sets->childGroups();

QString group;

  foreach(group, groups) {
        /*
          There is code to parse .HOT file

          */
      MXBookmarkList userMenu;
      QString myName, myLevel;
      //array of items of this Menu
      sets->beginGroup(group);
     QStringList keys = sets->allKeys();
     QString key;
     foreach (key, keys) {

         if (key == "Menu_Name") {
             myName = sets->value(key).toString();
             continue;}
   else      if (key == "Menu_Type"){
             myLevel = sets->value(key, "FUCK").toString();
             continue;
         }
    else     if (key.startsWith("Item")) {
             /*parse item here */
              MXBookmark item;
              QString itemString  = "";

             if(sets->contains(key)) {
           itemString = sets->value(key, "fuck").toString();

             QStringList itemList = itemString.split(',');
 //maybe it submenu?
             item.name = itemList.at(0);
             item.url= itemList.at(1);
             if (itemList.count() == 3) {
             item.time = QDateTime::fromString(itemList.at(2), "dd-MMM-yy HH:mm:ss");
             }
             userMenu.append(item);
         }
         }

     }
     if (myLevel == "TOPLEVEL")
topMenu = groups.indexOf(group);
     //Done with menu
    menu.append(userMenu);
    menuNames.append(myName);
    sets->endGroup();
}
    makeHotlistsMenu();



}

void MainWindow::makeHotlistsMenu() {
  MXBookmarkList mnu = menu.at(topMenu);

makeGroup(mnu);


  }


void MainWindow::makeGroup(const MXBookmarkList &list, QMenu *parent) {
    MXBookmark item;
    if (parent == 0) { //then parent = menuHotlists
            parent = ui->menuHotlists;
            //add a first-level point
            QMenu *top = new QMenu (menuNames.at(topMenu), this);
            parent->addMenu(top);
            makeGroup(list, top);
            return;
    }
    foreach (item, list) {
        if (item.name == "MENU") {
            //recursive call makeGroup;
            //get UserMenu by number
            QString menuID = item.url;
            if (menuID.startsWith("UserMenu")) { //"UserMenu" contains 8 symbols
             QString menuNubmer = menuID.right(menuID.count() - 8);

             int num = menuNubmer.toInt();

             //build a simple QMenu
             QString menuName = menuNames.at(num);
             QMenu *submenu = new QMenu (menuName, this);
             parent->addMenu(submenu);
             makeGroup(menu.at(num), submenu);


            }


        }
        else {
            //get a parent menu
                QAction *userAction  = new QAction (item.name, this);
                userAction->setStatusTip(item.url);
                connect(userAction, SIGNAL(triggered()), this, SLOT (onCustomMenuClicked()));
                //add item
                parent->addAction(userAction);



        }
    }

}

void MainWindow::onCustomMenuClicked() { //slot on custom menu triggered
    QObject *obj = sender();
    QAction *act = dynamic_cast<QAction*> (obj);
    MXBookmark curItem = getItemByName(act->text());
    openUrl(curItem.url);


}

    MXBookmark MainWindow::getItemByName(const QString &name) {
    MXBookmarkList list; //foreach
    MXBookmark item; //foreach
    MXBookmark returnItem;
    bool done = false;
    foreach  (list,menu ) {
    foreach (item, list) {
        if (item.name == name) {
            returnItem = item;
            done = true;
           return returnItem;
        }

    }
    }
    if (!done)
       return  returnItem;


     }


void MainWindow::openUrl(QString url) {}

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
core->writeSetting("ButtonText", "opions", checked, op.tbConfig);

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
    //saving settings
    //toolbars
    core->writeSetting("Mosaic", "Toolbars",  ui->tbMosaic->isVisible(), QDir::homePath() + CONFFILE);
    core->writeSetting("Web", "Toolbars", ui->tbWeb->isVisible(), QDir::homePath() + CONFFILE);
    core->writeSetting("Location", "Toolbars", ui->tbLocation->isVisible(), QDir::homePath() + CONFFILE);
    //other coming soon

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
    //clean all toolbars and hostlists;
    //call mxloader to reread settings
    ui->menuHotlists->clear();
    ui->tbLocation->clear();
    ui->tbMosaic->clear();
    ui->tbWeb->clear();
    load();
    createWindow();
    createMenus();
    createToolbars();

}

void MainWindow::createWindow() {
    //reading size and location settings
   resize(op.size);
   move(op.position);
    }

void MainWindow::on_actToolConf_triggered()
{
MXButtonConf *frm = new MXButtonConf(this, op.tbConfig);
frm->show();
if (frm->result() == QDialog::Accepted)
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
   op.position = stg->value("Position", QPoint (0,0)).toPoint();
   op.size = stg->value("Size", QSize (640, 480)).toSize();
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
stg->beginGroup("HotinkBar");
stg->value("NumberButtons", -1).toBool();
stg->endGroup();
stg->beginGroup("opions");
op.buttontext = stg->value("ButtonText", false).toBool();
stg->endGroup();
delete stg;


/***********************************************************************
  There will be code - loading other configs

  IT IS COMING SOON!!!!!!






  ************************************************************************/




//loading hotlinks
out << tr("mosaix: loading hotlists\n");

}
