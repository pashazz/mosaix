#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "MXSettings.h"
#include "mxcoremethods.h"
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
    MainWindow (MXOptions &opt, QString &hotlink, QWidget *parent = 0);
    ~MainWindow();
    //main functions
     void openUrl (QString url);

private slots:
void on_actButText_triggered(bool checked);
void on_actExit_triggered();
void onCustomMenuClicked ();
private:
//creators
    Ui::MainWindow *ui;
    void createMenus();
    void createToolbars();
//core
    MXCoreMethods *core;
//options variables
    MXOptions op;
    //Hotlinks variables and functions

    void hotListParser();
    void makeHotlistsMenu();
    void makeGroup(const MXBookmarkList &list,  QMenu *parent = 0);
    MXBookmark getItemByName (const QString &name);

    int topMenu;
    QString hlink;
    QStringList menuNames;
    MXMenu menu;

};

#endif // MAINWINDOW_H
