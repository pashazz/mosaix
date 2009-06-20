#include "mxloader.h"
#include "config.h"
#include "mainwindow.h"
#include <QtDebug>
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
MainWindow *w = new MainWindow ();
w->show();
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
    main->setValue("ShowDay", true);
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
     main->setValue("MiscConfig", conf_dir +  "/misc.ini");
  main->setValue("HotlinkList", conf_dir + "/hotlinks/DEFAULT1.HOT");
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
    hbar->setValue("url", "http://linuxforum.ru");
    hbar->endGroup();
    hbar->sync();



delete main;
delete tbar;
delete hbar;

    //DONE, then continue boot process

}







