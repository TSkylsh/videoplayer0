#include "mainwid.h"
#include "ui_mainwid.h"

MainWid::MainWid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWid)
{
    ui->setupUi(this);
}

MainWid::~MainWid()
{
    delete ui;
}
