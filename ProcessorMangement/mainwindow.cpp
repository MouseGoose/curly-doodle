#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pm=new PM;

    connect(ui->tips,SIGNAL(triggered()),this,SLOT(method()));
    ui->menuHelp->setStyleSheet("color:black;");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pm;
}

void MainWindow::on_BCreate_clicked()
{
    QString process=QInputDialog::getText(this,"进程创建","请输入进程信息",QLineEdit::Normal,"进程名/运行时间/优先级/提交时间");
    if(!pm->Create_pc(process))
       QMessageBox::information(this,"警告","创建失败");
    else
        QMessageBox::information(this,"提示","创建成功");
}

void MainWindow::on_BAuto_clicked()
{
    if(!pm->Auto_Create())
        QMessageBox::information(this,"警告","创建失败");
    else
       QMessageBox::information(this,"提示","创建成功");
    return;
}

void MainWindow::on_BCheck_clicked()
{
    ui->table->clear();
    ui->table->setRowCount(0);
    count=0;
    Create_table();

   //表格中插入已加载的进程
    for(auto i:pm->pmemmory)
    {
       QString level=QString::number(i.level,10);
       QString time=QString::number(i.runtime,'f',1);
       QString subtime=QString::number(i.submittime,'f',1);
       Insert_Item(i.name,time,level,subtime);
    }
    return;
}

void MainWindow::on_BFCFS_clicked()
{
    if(pm->pmemmory.empty())
    {
       QMessageBox::information(this,"警告","当前没有创建任何进程");
       return;
    }
    fcfs=new FCFS;
    fcfs->initial(pm);
    fcfs->show();
    return;
}

void MainWindow::on_BSPN_clicked()
{
    if(pm->pmemmory.empty())
    {
       QMessageBox::information(this,"警告","当前没有创建任何进程");
       return;
    }
    spn=new SPN;
    spn->initial(pm);
    spn->show();
    return;
}

void MainWindow::on_BHRRN_clicked()
{
    if(pm->pmemmory.empty())
    {
       QMessageBox::information(this,"警告","当前没有创建任何进程");
       return;
    }
    hrrn=new HRRN;
    hrrn->initial(pm);
    hrrn->show();
    return;
}

void MainWindow::Create_table()
{
    ui->table->setColumnCount(4);
    ui->table->setColumnWidth(1,200);
    QStringList header;
    header<<"进程名"<<"预计执行时间"<<"优先级"<<"提交时间";
    ui->table->setHorizontalHeaderLabels(header);
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->horizontalHeader()->setFixedHeight(45);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//去掉水平滚动条
    ui->table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);  //去掉垂直滚动条
    ui->table->horizontalHeader()->setStyleSheet(
        "font:15pt '宋体';color: black;};");
    return ;
}



void MainWindow::Insert_Item(QString name,QString time,QString level,QString subtime)
{
    ui->table->insertRow(count);
    item[0]=new QTableWidgetItem(name);
    item[1]=new QTableWidgetItem(time);
    item[2]=new QTableWidgetItem(level);
    item[3]=new QTableWidgetItem(subtime);
    ui->table->setItem(count,0,item[0]);
    ui->table->setItem(count,1,item[1]);
    ui->table->setItem(count,2,item[2]);
    ui->table->setItem(count,3,item[3]);

    count++;
}

void MainWindow::method()
{
    QString filePath = "../ProcessorMangement/help.txt"; // 文件的路径
    QUrl fileUrl = QUrl::fromLocalFile(filePath); // 将文件路径转换为本地文件URL
    QDesktopServices::openUrl(fileUrl); // 使用系统默认程序打开文件
}






