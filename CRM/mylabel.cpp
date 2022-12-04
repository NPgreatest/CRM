#include "mylabel.h"


mylabel::mylabel(QWidget *parent):QLabel(parent)
{

}

void mylabel::enterEvent(QEvent *event)
{
   // setStyleSheet("border:6px solid;"
    //              "border-color:rgb(255,0,0);"
   //               "background-color: rgb(0, 0, 255);");
}

void mylabel::leaveEvent(QEvent *event)
{
  //  setStyleSheet("border:0px");
  //  setText(" ");
//    setAlignment(Qt::AlignCenter);
}

void mylabel::mousePressEvent(QMouseEvent *event)
{

    emit clicked();
}

