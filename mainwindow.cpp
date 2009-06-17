#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(MXOptions &opt,QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
