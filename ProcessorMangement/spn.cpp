#include "spn.h"
#include "ui_spn.h"

SPN::SPN(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SPN)
{
    ui->setupUi(this);
    time2.setHMS(0,0,0,0);
    connect(&timer2,SIGNAL(timeout()),this,SLOT(update()));
    connect(ui->rB1,SIGNAL(clicked(bool)),
            this,SLOT(Process_mode()));
    connect(ui->rB2,SIGNAL(clicked(bool)),
            this,SLOT(Process_mode()));

    groupButton=new QButtonGroup(this);
        groupButton->addButton(ui->rB1,0);
        groupButton->addButton(ui->rB2,1);
        ui->rB2->setChecked(true);
}

SPN::~SPN()
{
    delete ui;
}

void SPN::initial(PM *pm)
{
    for(auto i:pm->pmemmory)
        pm3.push_back(i);

    //按预计执行时间进行排序
    for(int i=0;i<pm3.size();i++)
    {
        for(int j=0;j<pm3.size()-1-i;j++)
        {
            if(pm3[j].runtime>pm3[j+1].runtime)
            {
                pcer tem=pm3[j];
                pm3[j]=pm3[j+1];
                pm3[j+1]=tem;
            }
        }
    }

    pm3.front().atm=pm3.front().submittime;
    pm3.front().cycletime=0;
    rtm=pm3.front().runtime;
    Create_table();

    return;
}

void SPN::Create_table()
{
    ui->table1->clear();
    ui->table2->clear();
    ui->table2->setRowCount(0);
    ui->table1->setRowCount(0);

    QStringList horizontalHeaderLabel1 = { "待执行进程" };
    ui->table1->setHorizontalHeaderLabels(horizontalHeaderLabel1);
    ui->table1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table1->setColumnCount(3);
    ui->table1->setColumnWidth(1,200);
    QStringList header1;
    header1<<"进程名"<<"预计执行时间"<<"提交时间";
    ui->table1->setHorizontalHeaderLabels(header1);
    ui->table1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table1->horizontalHeader()->setFixedHeight(45);
    ui->table1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->table1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条


    QStringList horizontalHeaderLabel2 = { "已结束进程" };
    ui->table2->setHorizontalHeaderLabels(horizontalHeaderLabel2);
    ui->table2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table2->setColumnCount(4);
    ui->table2->setColumnWidth(1,200);
    QStringList header2;
    header2<<"进程名"<<"开始时间"<<"结束时间"<<"周转时间";
    ui->table2->setHorizontalHeaderLabels(header2);
    ui->table2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table2->horizontalHeader()->setFixedHeight(45);
    ui->table2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->table2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条


    for(pcer i:pm3)
    {
        ui->table1->insertRow(count1);
        QString tem;
        item[0]=new QTableWidgetItem(i.name);
        tem=QString::number(i.runtime,'f',1);
        item[1]=new QTableWidgetItem(tem);
        tem=QString::number(i.submittime,'f',1);
        item[2]=new QTableWidgetItem(tem);
        ui->table1->setItem(count1,0,item[0]);
        ui->table1->setItem(count1,1,item[1]);
        ui->table1->setItem(count1,2,item[2]);
        count1++;
    }
    count1=0;
    count2=0;
    return;
}

void SPN::update()
{
    //未到达提交时间，等待
    if(pm3.front().submittime>(seconds+0.00001))
    {
        seconds+=0.1;
        if(pm3.front().submittime<seconds+0.00001)
        {
            pm3.front().atm=seconds;
            seconds=pm3.front().atm;
            pm3.front().cycletime=pm3.front().atm-pm3.front().cycletime+pm3.front().runtime;
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
    if(rtm-0.0001<0)
    {
        pm3.front().ltm=seconds;
        Insert_Item();
    }

    return;
}

void SPN::Insert_Item()
{
    double   tem=pm3.front().ltm;

    ui->table2->insertRow(count2);
    QTableWidgetItem* nm=new QTableWidgetItem(pm3.front().name);
    QTableWidgetItem *at=new QTableWidgetItem(QString::number(pm3.front().atm,'f',1));
    QTableWidgetItem *lt=new QTableWidgetItem(QString::number(pm3.front().ltm,'f',1));
     QTableWidgetItem *ct=new QTableWidgetItem(QString::number(pm3.front().cycletime,'f',1));
    ui->table2->setItem(count2,0,nm);
    ui->table2->setItem(count2,1,at);
    ui->table2->setItem(count2,2,lt);
    ui->table2->setItem(count2,3,ct);
    count2++;

    ui->table1->removeRow(0);
    save.push_back(pm3.front());
    pm3.pop_front();

    if(pm3.isEmpty())
    {
        timer2.stop();
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
    if(pm3.front().submittime>seconds)
    {
        pm3.front().cycletime=tem;
        return;
    }

    //进程已提交，开始运行
    pm3.front().atm=tem;
    pm3.front().cycletime=seconds-pm3.front().submittime+pm3.front().runtime;
    rtm=pm3.front().runtime;
}

void SPN::on_beg_clicked()
{
    if(pm3.size()==0)
     {
        QMessageBox::information(this,"警告","当前没有创建任何进程");
        return;
     }
    timer2.start(speed);
}

void SPN::on_stop_clicked()
{
    timer2.stop();
}

void SPN::on_insert_clicked()
{
    timer2.stop();
    QString process=QInputDialog::getText(this,"进程创建","请输入进程信息",QLineEdit::Normal,"进程名/运行时间/提交时间");
    pcer tem;
    tem.name=process.section('/',0,0);
    tem.runtime=process.section('/',1,1).toDouble();
    tem.submittime=process.section('/',2,2).toDouble();
    if(sign==0)
    {
        for(pcer i:pm3)
        {         
            if(i.runtime>=tem.runtime)
             {
                pm3.push_front(tem);
                rtm=pm3.front().runtime;
                if(pm3.front().submittime>seconds)
                    pm3.front().atm=pm3.front().submittime;
                else
                    pm3.front().atm=seconds;
                break;
             }
        }
    }
    else
        pm3.push_back(tem);

    ui->table1->clearContents();

    count1=0;

    for(pcer i:pm3)
    {
        ui->table1->insertRow(count1);
        QString tem;
        item[0]=new QTableWidgetItem(i.name);
        tem=QString::number(i.runtime,'f',1);
        item[1]=new QTableWidgetItem(tem);
        tem=QString::number(i.submittime,'f',1);
        item[2]=new QTableWidgetItem(tem);
        ui->table1->setItem(count1,0,item[0]);
        ui->table1->setItem(count1,1,item[1]);
        ui->table1->setItem(count1,2,item[2]);
        count1++;
    }
    count1=0;

    timer2.start(speed);

}

void SPN::Process_mode()
{
    switch (groupButton->checkedId()) {
    case 0:
        sign=0;
        break;
    case 1:
        sign=1;
        break;
    }
}

void SPN::on_reset_clicked()
{
    for(auto i:save)
    {
        i.cycletime=0;
        pm3.push_back(i);
    }
    save.clear();
    seconds=0;
    for(int i=0;i<pm3.size();i++)
    {
        for(int j=0;j<pm3.size()-1-i;j++)
        {
            if(pm3[j].runtime>pm3[j+1].runtime)
            {
                pcer tem=pm3[j];
                pm3[j]=pm3[j+1];
                pm3[j+1]=tem;
            }
        }
    }
    rtm=pm3.front().runtime;

   Create_table();
}














