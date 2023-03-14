#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QInputDialog>
#include<QTabWidget>
#include<QTableWidgetItem>
#include<QMenu>
#include"pm.h"
#include"fcfs.h"
#include"spn.h"
#include"hrrn.h"
#include<qprocess.h>
#include <QDesktopServices>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Create_table();

    void Insert_Item(QString name,QString time,QString level,QString subtime);

    PM* pm;                         //进程管理器类
    int count;                      //Table行数

    QTableWidgetItem *item[4];      //QTableWidget控件

public slots:
    void on_BCreate_clicked();      //手动创建进程

    void on_BAuto_clicked();        //自动创建进程

    void on_BCheck_clicked();        //查看已创建进程

    void on_BFCFS_clicked();        //FCFS算法

    void on_BSPN_clicked();         //SJF算法

    void on_BHRRN_clicked();        //HRRN算法

    void method();


private:
    Ui::MainWindow *ui;
    FCFS *fcfs;
    SPN* spn;
    HRRN* hrrn;
};
#endif // MAINWINDOW_H
