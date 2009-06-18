#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "MXSettings.h"
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
void onCustomMenuClicked ();
private:


//creators
    Ui::MainWindow *ui;
    void createMenus();
    void createToolbars();

//options variables
    MXOptions op;
    //Hotlinks variables and functions

    void hotListParser();
    void makeHotlistsMenu();
    void makeGroup(const MXBookmarkList &list, const QString &parent = "");
    MXBookmark getItemByName (const QString &name);
    QAction getActionByName (const QString &name);
    int topMenu;
    QString hlink;
    QStringList menuNames;
    MXMenu menu;

};

#endif // MAINWINDOW_H
