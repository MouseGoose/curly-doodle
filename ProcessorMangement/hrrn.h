#ifndef HRRN_H
#define HRRN_H

#include<QTime>
#include<QTimer>
#include <QWidget>
#include<QMessageBox>
#include<QTabWidget>
#include<QTableWidgetItem>
#include<QVector>
#include"pm.h"

namespace Ui {
class HRRN;
}

class HRRN : public QWidget
{
    Q_OBJECT

public:
    explicit HRRN(QWidget *parent = nullptr);
    ~HRRN();

    int count1=0;
    int count2=0;

    double seconds=0;

    QTime time3;
    QTimer timer3;

    QVector<pcer> pm4;     //存储进程
    QVector<pcer> save;

    QTableWidgetItem *item[5];      //QTableWidget控件

    void Create_Ftable();

    void Insert_Item();

    void initial(PM* pm);

    void HRRN_method(double ltm);

    void Re_table();

private slots:
    void update();

    void on_beg_clicked();

    void on_stop_clicked();

    void on_reset_clicked();

private:
    Ui::HRRN *ui;
};

#endif // HRRN_H
