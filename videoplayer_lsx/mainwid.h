#ifndef MAINWID_H
#define MAINWID_H

#include <QMainWindow>

namespace Ui {
class MainWid;
}

class MainWid : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWid(QWidget *parent = 0);
    ~MainWid();

private:
    Ui::MainWid *ui;
};

#endif // MAINWID_H