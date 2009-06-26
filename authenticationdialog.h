#ifndef AUTHENTICATIONDIALOG_H
#define AUTHENTICATIONDIALOG_H

#include <QtCore>
#include <QtGui>
#include <QtWebKit>
#include "ui_authenticationdialog.h"

class AuthenticationDialog : public QDialog,
                             private Ui::Dialog
{
    Q_OBJECT

public:
    AuthenticationDialog(QWidget * parent = 0);
    QString user() const;
    QString password() const;
};

#endif // AUTHENTICATIONDIALOG_H
