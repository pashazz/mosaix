#include "authenticationdialog.h"

AuthenticationDialog::AuthenticationDialog(QWidget * parent)
    : QDialog(parent)
{
    setupUi(this);
}

QString AuthenticationDialog::user() const
{
    return lineEdit->text();
}

QString AuthenticationDialog::password() const
{
    return lineEdit_2->text();
}
