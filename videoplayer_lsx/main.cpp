#include "mainwid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWid w;
    w.show();

    return a.exec();
}
