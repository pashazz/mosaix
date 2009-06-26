#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "MXSettings.h"
#include "mxcoremethods.h"
#include "mxbuttonconf.h"
#include "mxloader.h"
#include <QtGui>
#include <QtWebKit>
#include <QUrl>
 #include <QTreeWidgetItem>
#include "mxhtlprop.h"
#include "mxdownloadinterface.h"
#include "aboutdialog.h"
#include "hotlink.h"
#include "webpage.h"
#include "webhistory.h"

namespace Ui
{
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //constructor & destructor
    MainWindow (QWidget *parent = 0);
    ~MainWindow();
    //main functions
     void openUrl (QString url);
     void readSettings();
     void saveMySettings();


private slots:

void on_actInsFld_triggered();
void on_actHotFont_triggered();
void on_actInsItem_triggered();
void on_twHotlinks_itemSelectionChanged();
void on_twHotlinks_itemActivated(QTreeWidgetItem* item, int column);
void on_actOneRoot_triggered(bool checked);
void on_actHotMenu_triggered(bool checked);
void on_actHotStart_triggered(bool checked);
void on_actAbout_triggered();
void on_actSrcFont_triggered();
void on_cmdSourceSave_clicked();
void on_actPrSet_triggered();
void on_actPrintPr_triggered();
void on_actPrint_triggered();
void on_actSaveText_triggered();
void on_actSave_triggered();
void on_actionOpenLocal_triggered();
void on_actOpen_triggered();
void on_actHotDelete_triggered();
void on_txtHotlist_textChanged(QString );
void on_twHotlinks_customContextMenuRequested(QPoint pos);
void on_actAlphabet_triggered();
void on_actHotlinkPropreties_triggered();
void on_actAdd2hot_triggered();
void on_actPresent_triggered(bool checked);
void on_twHotlinks_itemDoubleClicked(QTreeWidgetItem* item, int column);
void on_actDefaultLayout_triggered();
void on_actCopy_triggered();
void on_actStatus_triggered(bool checked);
void loadPage();
void onStarted();
void onFinished(bool);
void onUrlChanged(QUrl url);
void on_actToolConf_triggered();
void on_actLocTb_triggered(bool checked);
void on_actWebTb_triggered(bool checked);
void on_actMosaicTb_triggered(bool checked);
void on_actHome_triggered();
void on_actButText_triggered(bool checked);
void on_actExit_triggered();
void updateTimer();
void onToolbarMenu (QPoint p);
void onBrowserMenu(QPoint p);
void onTitleChanged(QString title);
void onIconChanged ();
void setStatusBarMessage(QString);
void onShowInfo();
void onShortcut();
void onSpawn();
void onPixel ();

void onLoadAnchor();
void onAddAnchor();
void onQueryLink();
void onChangeFont();
void onTabChanged(int);
void onCustomMenuClicked (QAction*);
    void onHLProperties ( QString, QString, QDateTime, int);

private:

//creators
    Ui::MainWindow *ui;
    void createMenus();
    void createToolbars();
    void createWindow();
    void connectAll();
    void createBrowserMenu();
    void createHotlinkBar();
    void createManager() ;
    void makeMenu(QMenu* menu, QTreeWidgetItem *item);
    QMenu* menuData(QList<QTreeWidgetItem *>w);
    QUrl guessUrlFromString(const QString &string);

//core
    MXCoreMethods *core;
//options variables
    MXOptions op;
    //Hotlinks variables and functions

    void makeHotlistsMenu();
    void createOtherMenus();

    QMenu* getMenuForItem (int index);

    void load();
    QDir plugdir;
    QStringList pluginFilenames;
    void addPlugin(QObject *pl);
    void initMgr();
    //labels & menus
    QLabel *time;
    QTimer *timer;
    QPushButton *yes;
    QPushButton *stop;
    QComboBox *addr;
    QMenu *cmToolbars;
    QMenu *cmBrowser;
    QMenu *cmLink;
    QMenu *cmHotTree;
    QMenu *srcManager;
    QProgressBar *progress;
    QMenu *cacheManager;
    QMenu *hotManager;
    QMenu *hstManager;
    HotlinkData *hdata;
    //current webpage
    QStringList tabs;
    QList <MXDownloadInterface *> plugins;
    WebPage *page;
    WebHistory *history;
    //actions
    QAction *spawn; //spawn mosaic
    QAction *info; //header information
    QAction *shortcut; //create internet shortcut
    QAction *pixerColor;
    QAction *openInNewWindow;
    QAction *add2hot;
    QAction *pixel;
    QToolBar *hotBar;
    QMenu *hotlists;
    int curIndex;
    protected:
    void closeEvent(QCloseEvent *e);
    void changeEvent(QEvent *e);
    void loadPlugins();
    QStringList collectItems (QTreeWidgetItem *parent);
    QMenu* getMenuByTitle (QMenu *parent,QString title);
    void makeOneRootMenu(QList<QTreeWidgetItem*> wd);
    QTreeWidgetItem* gp ();
QWebHitTestResult *r;
};

#endif // MAINWINDOW_H
