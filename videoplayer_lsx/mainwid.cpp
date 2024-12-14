#include "mainwid.h"
#include "ui_mainwid.h"
#include<QDebug>
MainWid::MainWid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWid)
{
    ui->setupUi(this);
    ConnectSignSlot();
}

MainWid::~MainWid()
{
    delete ui;
}

bool MainWid::ConnectSignSlot()
{
    connect(ui->CtrlBarWid,&CtrlBar::SigPlayorPause,this,&MainWid::PlayOrPauseBtn_clicked);
    return true;
}
void MainWid::PlayOrPauseBtn_clicked()
{
qDebug()<<"on_PlayOrPauseBtn_clicked";

}
