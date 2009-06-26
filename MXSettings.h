#ifndef MXSETTINGS_H
#define MXSETTINGS_H
#include <QtCore>
#include <QPoint>
#include <QObject>
#include <QSize>
#include <QDate>
#include <QDateTime>
#include <QFont>



typedef QPair <QSize, QPoint> Location; //first - size, second - position

 struct MXOptions {
public:
     //Main
//applicattion
QString homePage;
QString downloadDir;
QString historyFile;
//window
bool globalHistory;
bool sessionHistory;
bool cacheManager;
bool showDate;
bool showDay;
bool showTime;

//toolbars
bool mosaic;
bool web;
bool managerviews;
bool location;
bool hotlinkbar;
bool statusbar;
//proxy
QString httpProxy;
//cache
QString cacheDir;
int cacheLimit;
//mail
QString mailName;
QString mailPassword;
QString mailHost;
QString mailAddress;
int mailPort;
//files
//ADD to EVERY FIELD QDir::homePath, or YOU will KILLED!!!!!!!
QString tbConfig;
QString aConfig;
//QString hotlistConfig;
QString miscConfig;
QString hotlinkList;
QString hotBarConfig;
    //ToolBars
//mosaic
bool openFile;
bool saveFile;
bool print;
bool printPreview;
bool copy;
bool paste;
bool find;
bool searchCache;
bool managerViewsTB;
bool help;
//web
bool back;
bool forward;
bool noimages;
bool reload;
bool home;
bool stop;
bool news;
bool email;
bool add2hot;
bool curhotlist;
//hotlist manager
bool hOneRoot;
bool hOnMenu;
bool hOnStartup;
QFont hFont;
//options
bool buttontext;
QFont srcFont;
//locations


Location webBrowser;
Location managerLocation;
Location window;


};



#endif // MXSETTINGS_H
