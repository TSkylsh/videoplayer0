#include "ctrlbar.h"
#include "ui_ctrlbar.h"
#include<QDebug>
CtrlBar::CtrlBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CtrlBar)
{
    ui->setupUi(this);
    QIcon icon_play(":/ctrl/icon/play.png");
    ui->PlayOrPauseBtn->setIcon(icon_play);

    QIcon icon_stop(":/ctrl/icon/stop.png");
    ui->StopBtn->setIcon(icon_stop);

    QIcon icon_pause(":/ctrl/icon/pause.png");
    ui->StopBtn->setIcon(icon_stop);
}

CtrlBar::~CtrlBar()
{
    delete ui;
}

void CtrlBar::on_PlayOrPauseBtn_clicked()
{
    qDebug()<<"on_PlayOrPauseBtn_clicked";
}
