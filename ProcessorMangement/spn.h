#ifndef SPN_H
#define SPN_H

#include<QTime>
#include<QTimer>
#include <QWidget>
#include<QMessageBox>
#include<QTabWidget>
#include<QTableWidgetItem>
#include<QVector>
#include<QInputDialog>
#include <QButtonGroup>
#include"pm.h"

namespace Ui {
class SPN;
}

class SPN : public QWidget
{
    Q_OBJECT

public:
    explicit SPN(QWidget *parent = nullptr);
    ~SPN();

    QVector<pcer> pm3;     //存储进程
   QVector<pcer> save;

    int count1=0;
    int count2=0;
    double seconds=0;

    QTime time2;
    QTimer timer2;

    QTableWidgetItem *item[5];      //QTableWidget控件

    QButtonGroup *groupButton;

    int sign=1;             //判断抢占式和非抢占式的标志,默认是非抢占式


    void initial(PM* pm);

    void Create_table();

    void Insert_Item();

private slots:

    void update();

    void on_beg_clicked();

    void on_stop_clicked();

    void on_insert_clicked();

    void Process_mode();


    void on_reset_clicked();

private:
    Ui::SPN *ui;
};

#endif // SPN_H
