#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QStandardItemModel>
#include<QString>
#include"recommand.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlQuery *query;
    QSqlDatabase db;
    recommand *recom;
    QStandardItemModel* model;
    QString change_img(int id);

};
#endif // MAINWINDOW_H
