#ifndef RECOMMAND_H
#define RECOMMAND_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <algorithm>
#include <qlist.h>
#include <qvector.h>
#include <qmath.h>
#include <iostream>
#include"utils.h"
namespace Ui {
class recommand;
}

class recommand : public QMainWindow
{
    Q_OBJECT

public:
    explicit recommand(QWidget *parent = nullptr,int id=1);
    ~recommand();

private slots:
    void on_taget_linkActivated(const QString &link);
    void tar_click();
    void rec_click_1();
    void rec_click_2();
    void rec_click_3();
    void ass_click();
    void on_pushButton_clicked();

private:
    Ui::recommand *ui;
    int cur_id,ass_id,rec1,rec2,rec3;
    void update_info();
    QString change_img(int id);
    void change_id(int id);
    QSqlQuery *query;
    QSqlDatabase db;
    QString name,info;
    int sweet;
    QList<QVector<double>> dis(QVector<double> tar);
    QList<QVector<double> > geo_dis(QList<QVector<double> > x,QList<QVector<double> > y);
    int euclid(int id);
    double support(int id);
    double join_support(int id1,int id2);
    QList<QVector<double> > association(int id);
};

#endif // RECOMMAND_H
