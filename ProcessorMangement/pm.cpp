#include "pm.h"

PM::PM(PM& pm)
{
    for(int i=0;i<pm.pmemmory.size();i++)
        pmemmory[i]=pm.pmemmory[i];
}

void PM::Check_pc()
{
    return;
}

bool PM::Create_pc(QString str)
{
    QString sign="/";
    pcer tem;
     int num=str.count(sign, Qt::CaseInsensitive);
     if(num!=2)
         return false;
     else
     tem.name=str.section('/',0,0);
     tem.runtime=str.section('/',1,1).toDouble();
     tem.level=str.section('/',2,2).toInt();
     tem.submittime=str.section('/',3,3).toInt();
     pmemmory.push_back(tem);
    return true;
}

bool PM::Auto_Create()
{
    QString process[999];
    QString filename="../ProcessorMangement/process.txt";
    QFile file("../ProcessorMangement/process.txt");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QTextStream ifs(&file);
        int i=0;
        while(ifs.atEnd()==false)
        {
            process[i]=ifs.readLine();
            pcer tem;
             tem.name=process[i].section('/',0,0);
             tem.runtime=process[i].section('/',1,1).toDouble();
             tem.level=process[i].section('/',2,2).toInt();
             tem.submittime=process[i].section('/',3,3).toDouble();
             i++;
             pmemmory.push_back(tem);
        }
    }
    else
        return false;

    return true;

}
