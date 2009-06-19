#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "MXSettings.h"
#include "mxcoremethods.h"
#include "mxbuttonconf.h"
#include "mxloader.h"
#include <QtGui>

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

private slots:


void on_actToolConf_triggered();
void on_actLocTb_triggered(bool checked);
void on_actWebTb_triggered(bool checked);
void on_actMosaicTb_triggered(bool checked);
void on_actHome_triggered();
void on_actButText_triggered(bool checked);
void on_actExit_triggered();
void onCustomMenuClicked ();
void updateTimer();
void onToolbarMenu (QPoint p);
private:
//creators
    Ui::MainWindow *ui;
    void createMenus();
    void createToolbars();
    void createWindow();

//core
    MXCoreMethods *core;
//options variables
    MXOptions op;
    MXLoader *par;
    //Hotlinks variables and functions

    void hotListParser();
    void makeHotlistsMenu();
    void makeGroup(const MXBookmarkList &list,  QMenu *parent = 0);
    MXBookmark getItemByName (const QString &name);
    void load();
    int topMenu;
    QString hlink;
    QStringList menuNames;
    MXMenu menu;

    //labels & menus
    QLabel *time;
    QTimer *timer;
    QPushButton *yes;
    QPushButton *stop;
    QComboBox *addr;
    QMenu *cmToolbars;
    protected:
    void closeEvent(QCloseEvent *e);

};

#endif // MAINWINDOW_H
