#ifndef MXSETTINGS_H
#define MXSETTINGS_H
#include <QtCore>
#include <QPoint>
#include <QObject>
#include <QSize>
#include <QDate>
#include <QDateTime>
typedef QPair <QString, QString> MXBookmark; // <Name, URL>
typedef QList<MXBookmark> MXBookmarkList;
struct MXHotlink {
QString name;
QString url;
QDateTime time;
};

 struct MXOptions {
public:
     //Main
//applicattion
QString homePage;
QString downloadDir;
QString historyFile;
//window
bool globalHistory;
bool seesionHistory;
bool showDate;
bool showTime;
QPoint position;
QSize size;
//toolbars
bool mosaic;
bool web;
bool managerviews;
bool location;
bool hotlinkbar;
bool statusbar;
//proxy
QString httpProxy;
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
QString hotlistConfig;
QString miscConfig;
QString hotlinkList;
QString hotBarConfig;
    //ToolBars
//mosaic
bool openFile;
bool saveFile;
bool print;
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
//hotlinkbar
int numberButtons;
//options
bool buttontext;
//hotbar
MXBookmarkList bookmarks;

//
};



#endif // MXSETTINGS_H
