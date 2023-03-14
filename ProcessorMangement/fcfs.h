#ifndef FCFS_H
#define FCFS_H
#include<QTime>
#include<QTimer>
#include <QWidget>
#include<QMessageBox>
#include<QTabWidget>
#include<QTableWidgetItem>
#include<QVector>
#include"pm.h"

namespace Ui {
class FCFS;
}

class FCFS : public QWidget
{
    Q_OBJECT

public:
    explicit FCFS(QWidget *parent = nullptr);
    ~FCFS();

    QTime time;
    QTimer timer;

    int count1;
    int count2;
    double seconds=0;
    QVector<pcer> pm2;     //存储进程
    QVector<pcer> save;

    QTableWidgetItem *item[5];      //QTableWidget控件

    void Create_Ftable();

    void Insert_Item();

    void initial(PM* pm);
private slots:
    void on_beg_clicked();

    void update();

    void on_beg_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::FCFS *ui;

};

#endif // FCFS_H
