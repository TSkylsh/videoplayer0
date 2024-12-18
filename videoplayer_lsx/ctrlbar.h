#ifndef CTRLBAR_H
#define CTRLBAR_H

#include <QWidget>

namespace Ui {
class CtrlBar;
}

class CtrlBar : public QWidget
{
    Q_OBJECT
public:
    explicit CtrlBar(QWidget *parent = 0);
    ~CtrlBar();

private slots:
    void on_PlayOrPauseBtn_clicked();

private:
    Ui::CtrlBar *ui;
signals:
    void SigPlayorPause();
};

#endif // CTRLBAR_H
