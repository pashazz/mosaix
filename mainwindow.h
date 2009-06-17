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
    MainWindow (MXOptions &opt, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
