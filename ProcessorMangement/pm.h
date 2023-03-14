#ifndef PM_H
#define PM_H

#include <QWidget>
#include<QVector>
#include<QDebug>
#include<QFile>
#include<QMessageBox>
#include<QString>
#include<QTime>
#include<QTimer>

static int speed=100;
static double rtm=0;


struct pcer			//进程
{
    QString	name;			//进程名称
    int		level;			//进程优先级
    double  runtime;		//进程运行时间
    double submittime;     //进程提交时间
    double cycletime;      //进程周转时间
    QString  arrivetime;		//进程进入时间
    QString	leavetime;		//进程离开时间
    double atm;
    double ltm;
    const pcer operator =(const pcer p)
    {
        name=p.name;
        level=p.level;
        runtime=p.runtime;
        arrivetime=p.arrivetime;
        leavetime=p.leavetime;
        submittime=p.submittime;
        atm=p.atm;
        ltm=p.ltm;
        return *this;
    }
};

class PM            //进程管理器类
{
public:
    PM()=default;
    PM(PM& pm);
    bool Create_pc(QString str);		//创建新进程并插入
    void Check_pc();		//查看所有已存在的进程
    bool Auto_Create();
    QVector<pcer> pmemmory;     //存储进程

};

#endif // PM_H
