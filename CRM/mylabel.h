#ifndef MYLABEL_H
#define MYLABEL_H
#include <QObject>
#include <QDebug>
#include <QLabel>
class mylabel:public QLabel
{
    Q_OBJECT
public:
    mylabel(QWidget *parent = 0);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void clicked(void); // 声明鼠标左击中信号
};
#endif // MYLABEL_H







