#include "show.h"
#include "ui_show.h"

Show::Show(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Show)
{
    ui->setupUi(this);
}

Show::~Show()
{
    delete ui;
}
