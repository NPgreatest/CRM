#include "recommand.h"
#include "ui_recommand.h"
#include<qdebug.h>
#include<QMessageBox>

using namespace std;
recommand::recommand(QWidget *parent,int id) :
    QMainWindow(parent),
    ui(new Ui::recommand)
{
    ui->setupUi(this);
    cur_id=id;
    QObject::connect(ui->taget, &mylabel::clicked, this, &recommand::tar_click);
    QObject::connect(ui->recommand_1, &mylabel::clicked, this, &recommand::rec_click_1);
    QObject::connect(ui->recommand_2, &mylabel::clicked, this, &recommand::rec_click_2);
    QObject::connect(ui->recommand_3, &mylabel::clicked, this, &recommand::rec_click_3);
    QObject::connect(ui->ass_img, &mylabel::clicked, this, &recommand::ass_click);

    db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("mysql");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
     if (!ok)QMessageBox::information(this, "infor", "link failed");
     query=new QSqlQuery();
     query->prepare("select shop_name,shop_sweet,information from shop where shop_id=:idd");
     query->bindValue(":idd",QString::number(cur_id));
     query->exec();
     query->next();
        name = query->value("shop_name").toString();
        info = query->value("information").toString();
        sweet = query->value("shop_sweet").toString().toInt();//qDebug()<<association(5);
        //for(int i=1;i<14;i++){//qDebug()<<euclid(i);
        //qDebug()<<association(i)[0][1];
//qDebug()<<association(i);
       // }
        change_id(cur_id);
}

void recommand::update_info()
{
    ui->name->setText(name);
    ui->sweet->setText(QString::number(sweet));
    ui->information->setText(info);
    ui->taget->setStyleSheet(change_img(cur_id));
}

QString recommand::change_img(int id)
{
    return QString("border-image: url(:/image/pic/")+QString::number(id)+QString(".jpg);");
}

void recommand::change_id(int id)
{
    cur_id=id;
    query->prepare("select shop_name,shop_sweet,information from shop where shop_id=:idd");
    query->bindValue(":idd",QString::number(cur_id));
    query->exec();
    query->next();
    name = query->value("shop_name").toString();
    info = query->value("information").toString();
    sweet = query->value("shop_sweet").toString().toInt();
    update_info();
    ui->ass_img->setStyleSheet(change_img(euclid(cur_id)));
    ui->recommand_1->setStyleSheet(change_img(association(cur_id)[0][1]));
    ui->recommand_2->setStyleSheet(change_img(association(cur_id)[1][1]));
    ui->recommand_3->setStyleSheet(change_img(association(cur_id)[2][1]));
}



recommand::~recommand()
{
    delete ui;
}

void recommand::on_taget_linkActivated(const QString &link)
{

}



void recommand::tar_click()
{

}

void recommand::rec_click_1()
{
      change_id(association(cur_id)[0][1]);
}

void recommand::rec_click_2()
{
      change_id(association(cur_id)[1][1]);
}

void recommand::rec_click_3()
{
      change_id(association(cur_id)[2][1]);
}

void recommand::ass_click()
{
    change_id(euclid(cur_id));
}




void recommand::on_pushButton_clicked()
{
    this->hide();
}



int absolute(int a,int b,int maxx)
{
    if(maxx==0)
    {
        return 0;
    }
    return qAbs(a-b)/maxx;
}

QList<QVector<double>> recommand::dis(QVector<double> tar)
{
    //sort(tar.begin(),tar.end());//默认升序排列
    QList<QVector<double>> res;
    for(int i=0;i<tar.size();i++)
    {
        res.append(QVector<double>());
        for(int k=0;k<tar.size();k++)
        {
            res[i].append(absolute(tar[i],tar[k],max_element(tar.begin(),tar.end())-min_element(tar.begin(),tar.end())));//这里的tar虽然已经排序过了，应该没有问题
        }
    }
    return res;
}

QList<QVector<double> > recommand::geo_dis(QList<QVector<double> > x,QList <QVector<double> > y)
{
    QList<QVector<double>> res;
    for(int i=0;i<x[0].size();i++)//x中每个vector长度相同
    {
        res.append(QVector<double>());
        for(int k=0;k<y[0].size();k++)
        {
            res[i].append(pow(pow(x[i][k],2)+pow(y[i][k],2),0.5));
        }
    }
    return res;
}


int recommand::euclid(int id)
{
    QSqlQuery query;
    query.exec("select shop_id,shop_sweet,shop_price from shop");
    QVector<double> x;
    QVector<double> y;
    while (query.next()) {
        x.append(query.value("shop_sweet").toString().toDouble());
        y.append(query.value("shop_price").toString().toDouble());
    }
    QList<QVector<double>> e=geo_dis(dis(x),dis(y));

    int min_v=9999;
    int min_p=0;
    for(int i=0;i<15;i++)
    {
        if(e[id-1][i]<min_v && e[id-1][i]!=0)
        {
            min_v=e[id-1][i];
            min_p=i;
        }
    }
   //query.exec("select shop_id,shop_sweet,shop_price from shop where shop_id=:idd");
   //query.bindValue(":idd",min_p);
   //query.next();
  return min_p+1;
}


double recommand::support(int id)
{
    QString sentence=QString("select count(*) from (select distinct customer_id from record where shop_id=%1) a").arg(id);
    query->exec(sentence);
    query->next();

    double ta=query->value("count(*)").toDouble();
    query->exec("select count(*) from (select distinct customer_id from record) a");
    query->next();
    double tb=query->value("count(*)").toDouble();
    return ta/tb;
}

double recommand::join_support(int id1,int id2)
{
    QString sentence=QString("select distinct customer_id,shop_id from record where shop_id=%1 or shop_id=%2").arg(id1).arg(id2);
    query->exec(sentence);
    double count=0;
    int last=-1;
    while (query->next()) {
        if(query->value(0).toString().toInt()==last) count++;
        else {
            last=query->value(0).toString().toInt();
        }
    }
    query->exec("select count(*) from (select distinct customer_id from record) a");
    query->next();
    double b=query->value(0).toString().toDouble();
    return count/b;
}

bool cmp(QVector<double> a,QVector<double> b)
{// 如果身高相同
    if(a[0] == b[0])
        // 按照名字降序排序
        return a[1] >= b[1];
    else
        // 按照身高降序排序
        return a[0] >= b[0];
}

QList<QVector<double> > recommand::association(int id)
{
    QList<QVector<double> > res;
    for(int i=1;i<16;i++){
        if(i==id)continue;
        QVector<double> temp;
        temp.push_back(join_support(id,i));
        temp.push_back(i);
        res.append(temp);
    }
    sort(res.begin(),res.begin()+14,cmp);
    return res;
}

