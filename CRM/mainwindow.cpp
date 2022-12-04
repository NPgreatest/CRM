#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<qdebug.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("mysql");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
     if (!ok)QMessageBox::information(this, "infor", "link failed");
     query=new QSqlQuery();
     query->prepare("select shop_id,shop_name,shop_sweet,information from shop");
     query->exec();
     QString id,name,info;
     int sweet,i=0;
     model=new QStandardItemModel();
     model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("ID")));
     model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("name")));
     model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("sweet")));
     while(query->next()){
        id = query->value("shop_id").toString();
        name = query->value("shop_name").toString();
        info = query->value("information").toString();
        sweet = query->value("shop_sweet").toString().toInt();
        model->setItem(i,0,new QStandardItem(id));
        model->setItem(i,1,new QStandardItem(name));
        model->setItem(i,2,new QStandardItem(QString::number(sweet)));
        i++;qDebug()<<i<<id;
     }
     ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::change_img(int id)
{
    return QString("border-image: url(:/image/pic/")+QString::number(id)+QString(".jpg);");
}
void MainWindow::on_pushButton_clicked()
{
    recom =new recommand(nullptr,ui->tableView->selectionModel()->currentIndex().row()+1);
    recom->show();

}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    ui->img->setStyleSheet(change_img(index.row()+1));
}

