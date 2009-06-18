#include "mxloader.h"
#include "config.h"
#include "mainwindow.h"
MXLoader::MXLoader()
{
;
}

void MXLoader::start()     //start load mosaix - if no configuration - create it
{
        conf_file = QDir::homePath() + CONFFILE;
   conf_dir = QDir::homePath() + CONFDIR;
   if (!QFile::exists(conf_file)) //first run Mosaix
    {
       QDir cdir (conf_dir);
       if (cdir.exists()) {
       cdir.mkpath(conf_dir);
       cdir.mkpath(conf_dir + "/hotlinks");
   }
    createConfig();
}
load();
}

void MXLoader::createConfig() {
    //сначала главные настройки

    QSettings *main = new QSettings (conf_file, QSettings::IniFormat, this);
    main->beginGroup("Application");
    main->setValue("MainPage", "http://google.com");
    main->endGroup();
    main->beginGroup("Directories");
    main->setValue("DownloadDir", QDir::tempPath());
    main->setValue("HistoryFile", QDir::homePath() + CONFDIR +  "/history.ghi");
    main->endGroup();
    main->beginGroup("Window");
    main->setValue("GlobalHistory", true);
    main->setValue("SessionHistory", true);
    main->setValue("CacheManager", true);
    main->setValue("ShowDate", true);
    main->setValue("ShowTime", true);
    main->setValue("Position",  QPoint (0,0));
    main->setValue("Size",  QSize (640, 480));
    main->endGroup();
    main->beginGroup("Toolbars");
    main->setValue("Mosaic", true);
    main->setValue("Web", true);
    main->setValue("ManagerViews", true);
    main->setValue("Location", true);
    main->setValue("Hotlink", true);
    main->setValue("StatusBar", true);
    main->endGroup();
    main->beginGroup("Proxy");
    main->setValue("HttpProxy", ""); //other proxies coming soon
    main->endGroup();
    main->beginGroup("Mail");
    main->setValue("Name", "");
    main->setValue("Password", "");
    main->setValue("Host", "");
    main->setValue("Address", "");
    main->setValue("Port", "");
    main->endGroup();
    main->beginGroup("Files");
    main->setValue("ToolBarConfig", conf_dir + "/toolbars.ini");
    main->setValue("AudioConfig", conf_dir + "/audio.ini");
  //  main->setValue("HotlistConfig", conf_dir + "/hotlists.ini");
    main->setValue("MiscConfig", conf_dir +  "/misc.ini");
  main->setValue("HotlinkList", conf_dir + "/hotlinks/default1.ini");
    main->setValue("HotlinkbarConfig", conf_dir + "/hotlinkbar.ini");


    main->endGroup();
    main->sync();

    //теперь тулбары (then toolbars)
    QSettings *tbar = new QSettings (conf_dir + "/toolbars.ini", QSettings::IniFormat, this);
    //what buttons show? by default, all!
    tbar->beginGroup("Mosaic");
    tbar->setValue("OpenFile", true);
    tbar->setValue("SaveFile", true);
    tbar->setValue("Print", true);
    tbar->setValue("PrintPreview",true);
    tbar->setValue("Copy", true);
    tbar->setValue("Paste",true);
    tbar->setValue("Find", true);
    tbar->setValue("SearchCache", true);
    tbar->setValue("ManagerViews", true);
    tbar->setValue("Help", true);
    tbar->endGroup();
    tbar->beginGroup("Web");
    tbar->setValue("Back", true);
    tbar->setValue("Forward", true);
    tbar->setValue("NoImages", true);
    tbar->setValue("Reload", true);
    tbar->setValue("Home", true);
    tbar->setValue("Stop",true);
    tbar->setValue("News", true); //news not implemented!
    tbar->setValue("E-Mail", true);
    tbar->setValue("Add2Hot", true);
    tbar->setValue("CurHotlist", true); // Current HotList
    tbar->endGroup();
    tbar->beginGroup("HotlinkBar");
    tbar->setValue("NumberButtions", 1);

    tbar->endGroup();
    tbar->beginGroup("Options");
    tbar->setValue("ButtonText", false);
    tbar->endGroup();
    tbar->sync();

    //then build hotlinkbar
    QSettings *hbar = new QSettings (conf_dir + "/hotlinkbar.ini", QSettings::IniFormat, this);
    //2 bookmarks - LOR and Linuxforum.ru
    hbar->beginGroup("Item0");
    hbar->setValue("name", "LOR");
    hbar->setValue("url", "http://linux.org.ru");
    hbar->endGroup();
    hbar->beginGroup("Item1");
    hbar->setValue("name", "LinuxForum");
    hbar->setValue("value", "http://linuxforum.ru");
    hbar->endGroup();
    hbar->sync();
    //tehn build hotlinks
  //  QSettings *hlinks = new QSettings (conf_dir +"/hotlinks.ini", QSettings::IniFormat, this);
  //  hlinks->beginGroup("Files");
    //Key is number, starting 0
    //hlinks->setValue(0,conf_dir + "/default1.ini");
   // hlinks->endGroup();
   // hlinks->sync();
    //build hotlink DEFAULT1.HOT  (wich is from Mosaic 3.0 description file default1.ini
    QSettings *df = new QSettings (conf_dir + "/hotlinks/default1.ini", QSettings::IniFormat, this);
    df->beginGroup("Info");
    df->setValue("MenuItems", 7);
    df->setValue("Menu0", 10);
    df->setValue("Menu1", 20);
    df->setValue("Menu2", 10);
    df->setValue("Menu3", 14);
    df->setValue("Menu4", 6);
    df->setValue("Menu5", 1);
    df->setValue("Menu6", 1);
    df->setValue("Menu7", 1);
df->endGroup();
df->sync();

delete main;
delete tbar;
delete hbar;
//delete hlinks;
delete df;
    //DONE, then continue boot process

}

void MXLoader::load(){
    QTextStream out (stdout);
    MXOptions opt;
   QSettings *stg;
   stg = new QSettings (conf_file, QSettings::IniFormat, this);
out << tr("mosaix: reading main.ini config\n");
   stg->beginGroup("Application");
   opt.homePage = stg->value("MainPage", "http://google.com").toString();
   stg->endGroup();
   stg->beginGroup("Directories");
   opt.downloadDir = stg->value("DownloadDir", QDir::tempPath()).toString();
   opt.historyFile = stg->value("HstoryFile", "").toString();
   stg->endGroup();
   stg->beginGroup("Window");
   opt.globalHistory = stg->value("GlobalHistory", true).toBool();
   opt.sessionHistory = stg->value("SessionHistory", true).toBool();
   opt.cacheManager = stg->value("CacheManager", true).toBool();
   opt.showDate = stg->value("ShowDate", true).toBool();
   opt.showTime = stg->value("ShowTime", true).toBool();
   opt.position = stg->value("Position", QPoint (0,0)).toPoint();
   opt.size = stg->value("Size", QSize (640, 480)).toSize();
   stg->endGroup();
   //toolbars
   stg->beginGroup("Toolbars");
   opt.mosaic = stg->value("Mosaic", true).toBool();
   opt.web = stg->value("Web", true).toBool();
   opt.managerviews = stg->value("ManagerViews",true).toBool();
   opt.location = stg->value("Location", true).toBool();
   opt.hotlinkbar = stg->value("Hotlink", true).toBool();
   opt.statusbar = stg->value("StatusBar", true).toBool();
   stg->endGroup();
   stg->beginGroup("Proxy");
   opt.httpProxy = stg->value("HhttpProxy").toString();
   stg->endGroup();
   stg->beginGroup("Mail");
  opt.mailName = stg->value("Name").toString();
  opt.mailPassword = stg->value("Password").toString();
  opt.mailHost = stg->value("Host").toString();
  opt.mailAddress = stg->value("Address").toString();
  opt.mailPort = stg->value("Port").toInt();
  stg->endGroup();
  stg->beginGroup("Files");
  opt.tbConfig = stg->value("ToolBarConfig", conf_dir + "/toolbars.ini").toString();
  opt.aConfig = stg->value("AudioConfig", conf_dir + "/audio.ini").toString();
  opt.miscConfig = stg->value("MiscConfig", conf_dir + "/misc.ini").toString();
  opt.hotBarConfig = stg->value("HotlinkBarConfig", conf_dir+ "/hotlinkbar.ini").toString();
  stg->endGroup();
delete stg;
stg = new QSettings (opt.tbConfig, QSettings::IniFormat, this);
out << tr("mosaix: reading Toolbars\n");
stg->beginGroup("Mosaic");
opt.openFile = stg->value("OpenFile", true).toBool();
opt.saveFile = stg->value("SaveFile", true).toBool();
opt.print = stg->value("Print", true).toBool();
opt.printPreview = stg->value("PrintPreview", true).toBool();
opt.copy = stg->value("Copy", true).toBool();
opt.paste = stg->value("Paste", true).toBool();
opt.find = stg->value("Find", true).toBool();
opt.searchCache = stg->value("SearchCache", true).toBool();
opt.managerViewsTB = stg->value("ManagerViews",true).toBool();
opt.help = stg->value("Help", true).toBool();
stg->endGroup();
stg->beginGroup("Web");
opt.back = stg->value("Back",true).toBool();
opt.forward = stg->value("Forward", true).toBool();
opt.noimages = stg->value("NoImages", true).toBool();
opt.reload = stg->value("Reload", true).toBool();
opt.home = stg->value("Home", true).toBool();
opt.stop = stg->value("Stop", true).toBool();
opt.news = stg->value("News",true).toBool();
opt.email = stg->value("E-Mail", true).toBool();
opt.add2hot = stg->value("Add2Hot",true).toBool();
opt.curhotlist = stg->value("CurHotList", true).toBool();
stg->endGroup();
stg->beginGroup("HotinkBar");
stg->value("NumberButtons", -1).toBool();
stg->endGroup();
stg->beginGroup("Options");
opt.buttontext = stg->value("ButtonText", false).toBool();
stg->endGroup();
delete stg;


/***********************************************************************
  There will be code - loading other configs

  IT IS COMING SOON!!!!!!






  ************************************************************************/

//loading hotlinks
out << tr("mosaix: loading hotlists\n");

//switching to MainWindow
MainWindow *w = new MainWindow (opt, opt.hotlinkList, 0) ;
w->show();
//loading done
}

