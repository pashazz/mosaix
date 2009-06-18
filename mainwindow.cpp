#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>

MainWindow::MainWindow(MXOptions &opt,QString &hotlink,  QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenus();
    createToolbars();
    op = opt;
    hlink = hotlink;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createMenus(){
    hotListParser();
}
void MainWindow::createToolbars(){
    ;
}
void MainWindow::hotListParser() {

    QSettings *stg = new QSettings (hlink,QSettings::IniFormat, this);
    stg->beginGroup("Info");
    QString fnValue = stg->value("FileName").toString();
    QFileInfo f (fnValue);
    QString fileName = f.canonicalFilePath();

    int i = stg->value("MenuItems", -1).toInt();
    stg->endGroup();
    int x;
    if (i == -1)
        return;
    for (x = 0; x >= i; ++x) {
        /*
          There is code to parse .HOT file

          */
       MXBookmarkList userMenu;


        QString myName, myLevel;


        //x from 0 to 7 in tests
        QSettings *sets = new QSettings (fileName, QSettings::IniFormat, this);
    //get number of items of THIS menu from stg
    //array of items of this Menu

    QString keyName = "Menu" + x;
    int items = stg->value(keyName).toInt();
    //get menu name
     sets->beginGroup("User Menu" + x);

     QStringList keys = sets->childKeys();
     QString key;

     foreach (key, keys) {
         if (key == "Menu_Name") {
             myName = sets->value(key).toString();
             continue;}
         if (key == "Menu_Type"){
             myLevel = sets->value(key, "FUCK").toString();
             continue;
         }
         if (key.startsWith("Item")) {
             /*parse item here */
              MXBookmark item;
             QString itemString = sets->value(key).toString();
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


void MainWindow::makeGroup(const MXBookmarkList &list, const QString &parent) {//parent is a name Menu_Name, not a UserMenu#!
    MXBookmark item;
    foreach (item, list) {
        if (item.name == "MENU") {
            //recursive call makeGroup;
            //get UserMenu by number
            QString menuID = item.url;
            if (menuID.startsWith("UserMenu")) { //"UserMenu" contains 8 symbols
             QString menuNubmer = menuID.right(menuID.count() - 8);
             bool *ok;
             int num = menuNubmer.toInt(ok);
             if (!*ok) {return;}
             //build a simple QAction
             QString menuName = menuNames.at(num);
             QAction *submenu = new QAction (menuName, this);


             //get this UserMenu
             MXBookmarkList m = menu.at(num);
             makeGroup(m);

            }


        }
        else {
            //get a parent menu
            if (parent.isEmpty()) { //TopMenu
                QAction *userAction  = new QAction (item.name, this);
                connect(userAction, SIGNAL(triggered()), this, SLOT (onCustomMenuClicked()));


            }

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

QAction MainWindow::getActionByName(const QString &name) {
    QAction *act = new QAction (this);

}
void MainWindow::openUrl(QString url) {}
