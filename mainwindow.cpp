#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include "config.h"

MainWindow::MainWindow(MXOptions &opt,QString &hotlink,  QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), core (new MXCoreMethods), op(opt), hlink(hotlink)
{
    //filling vars

    ui->setupUi(this);
    createMenus();
    createToolbars();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus(){
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
//style
if (op.buttontext){
      ui->tbMosaic->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ui->tbWeb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    }


}
void MainWindow::hotListParser() {

    QSettings *stg = new QSettings (hlink,QSettings::IniFormat, this);
    stg->beginGroup("Info");
    QString fnValue = stg->value("FileName").toString();

    QFileInfo f (fnValue);
    QString fileName = f.absoluteFilePath();
    if (!QFile::exists(fileName)) {

    }
    QSettings *sets = new QSettings (fileName, QSettings::IniFormat, this);


    int i = stg->value("MenuItems", -1).toInt();
    stg->endGroup();
    int x;
    if (i == -1) {
        return;}
    for (x = 0; x <= i; ++x) {
        /*
          There is code to parse .HOT file

          */
       MXBookmarkList userMenu;


        QString myName, myLevel;


        //x from 0 to 7 in tests
    //get number of items of THIS menu from stg
    //array of items of this Menu

    QString keyName = "Menu" + x;
    int items = stg->value(keyName).toInt();
    //get menu name
    QString group = "User Menu" + QVariant(x).toString();
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
         topMenu = x;

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
core->writeSetting("ButtonText", "Options", checked, op.tbConfig);

}
