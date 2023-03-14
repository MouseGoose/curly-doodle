#include "fcfs.h"
#include "ui_fcfs.h"
int sign=1;

FCFS::FCFS(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FCFS)
{
    ui->setupUi(this);
    time.setHMS(0,0,0,0);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));
}

FCFS::~FCFS()
{
    delete ui;
}

void FCFS::initial(PM *pm)
{
    for(auto i:pm->pmemmory)
    {
        pm2.push_back(i);
    }
    pm2.front().atm=pm2.front().submittime;
    pm2.front().cycletime=0;
    rtm=pm2.front().runtime;
    Create_Ftable();
    return;
}

void FCFS::update()
{
    //未到达提交时间，等待
    if(pm2.front().submittime>(seconds+0.00001))
    {
        seconds+=0.1;
        if(pm2.front().submittime<seconds+0.00001)
        {
            pm2.front().atm=seconds;
            seconds=pm2.front().atm;
            pm2.front().cycletime=pm2.front().atm-pm2.front().cycletime+pm2.front().runtime;
         }

        QString til="time:";
        til.append(QString::number(seconds,'f',1));
        ui->label->setText(til);
        return;
    }

    //开始运行
    seconds+=0.1;
    rtm=rtm-0.1;
    QString til="time:";
    til.append(QString::number(seconds,'f',1));
    ui->label->setText(til);
    if(rtm-0.00001<0)
    {
        pm2.front().ltm=seconds;
        Insert_Item();
    }

    return;
}

void FCFS::Create_Ftable()
{
    ui->table->clear();
    ui->table2->clear();
    ui->table2->setRowCount(0);
    ui->table->setRowCount(0);
    QStringList horizontalHeaderLabel1 = { "待执行进程" };
    ui->table->setHorizontalHeaderLabels(horizontalHeaderLabel1);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setColumnCount(3);
    ui->table->setColumnWidth(1,200);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    QStringList header1;
    header1<<"进程名"<<"预计执行时间"<<"提交时间";
    ui->table->setHorizontalHeaderLabels(header1);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->horizontalHeader()->setFixedHeight(45);


    QStringList horizontalHeaderLabel2 = { "已结束进程" };
    ui->table2->setHorizontalHeaderLabels(horizontalHeaderLabel2);
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table2->setColumnCount(4);
    ui->table2->setColumnWidth(1,200);
    ui->table2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->table2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    QStringList header2;
    header2<<"进程名"<<"开始时间"<<"结束时间"<<"周转时间";
    ui->table2->setHorizontalHeaderLabels(header2);
    ui->table2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table2->horizontalHeader()->setFixedHeight(45);

    count1=0;
    count2=0;

    for(pcer i:pm2)
    {
        ui->table->insertRow(count1);
        QString tem;
        item[0]=new QTableWidgetItem(i.name);
        tem=QString::number(i.runtime,'f',1);
        item[1]=new QTableWidgetItem(tem);
        tem=QString::number(i.submittime,'f',1);
        item[2]=new QTableWidgetItem(tem);
        ui->table->setItem(count1,0,item[0]);
        ui->table->setItem(count1,1,item[1]);
        ui->table->setItem(count1,2,item[2]);
        count1++;
    }
    count1=0;

    return;
}

void FCFS::Insert_Item()
{
    double   tem=pm2.front().ltm;

    ui->table2->insertRow(count2);
    QTableWidgetItem* nm=new QTableWidgetItem(pm2.front().name);
    QTableWidgetItem *at=new QTableWidgetItem(QString::number(pm2.front().atm,'f',1));
    QTableWidgetItem *lt=new QTableWidgetItem(QString::number(pm2.front().ltm,'f',1));
     QTableWidgetItem *ct=new QTableWidgetItem(QString::number(pm2.front().cycletime,'f',1));
    ui->table2->setItem(count2,0,nm);
    ui->table2->setItem(count2,1,at);
    ui->table2->setItem(count2,2,lt);
    ui->table2->setItem(count2,3,ct);
    count2++;

    ui->table->removeRow(0);
    save.push_back(pm2.front());
    pm2.pop_front();
    if(pm2.isEmpty())
    {
        timer.stop();
        double  cycle_time;         //平均周转时间
        double  cycle_time_weight;      //平均带权周转时间
        int row_count=ui->table2->rowCount();
        for(int i=1;i<row_count;i++)
        {
            double tm=ui->table2->model()->index(i,2).data().toDouble();
            cycle_time=cycle_time+tm;
        }
        cycle_time=cycle_time/row_count;

        for(int i=1;i<row_count;i++)
        {
            double tm=ui->table2->model()->index(i,2).data().toDouble()/save[i-1].runtime;
            cycle_time_weight=cycle_time_weight+tm;
        }

        cycle_time_weight=cycle_time_weight/row_count;


        ui->avtime->setText(QString::number(cycle_time,'f',1));
        ui->avwtime->setText(QString::number(cycle_time_weight,'f',1));
        QMessageBox::information(this,"提示","所有进程已运行完毕");
        return;
    }

    //当前一个进程已经结束，但是后一个进程还没有提交
    if(pm2.front().submittime>seconds)
    {
        pm2.front().cycletime=tem;
        return;
    }

    //进程已提交，开始运行
    pm2.front().atm=tem;
    pm2.front().cycletime=seconds-pm2.front().submittime+pm2.front().runtime;
    rtm=pm2.front().runtime;
}



void FCFS::on_beg_clicked()
{
    if(pm2.size()==0)
    {
       QMessageBox::information(this,"警告","当前没有创建任何进程");
       return;
    }
    timer.start(speed);
}

void FCFS::on_beg_2_clicked()
{
    timer.stop();
}

void FCFS::on_pushButton_clicked()
{
    for(auto i:save)
    {
        i.cycletime=0;
        pm2.push_back(i);
    }
    seconds=0;
    save.clear();
    rtm=pm2.front().runtime;
   Create_Ftable();
}









