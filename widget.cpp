#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "QPainter"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qss_control=new Form(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

void Widget::paintEvent(QPaintEvent *event)
{

}

Widget::~Widget()
{
    delete ui;
}
