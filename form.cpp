#include "form.h"
#include "ui_form.h"
#include "QFile"
#include "QDebug"
#include "QPainter"
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form),enable_flag(true),top_circle_selection(false),
    bottom_circle_selection(false),form_selection(false)
{
    ui->setupUi(this);
    ui->pushButton_left_1->hide();
    ui->pushButton_left_2->hide();
    form_setenable(true);
    //设置按钮可以连续触发
    ui->pushButton_left_1->setAutoRepeat(true); //设置是否允许自动重复
    ui->pushButton_left_1->setAutoRepeatDelay(100);//设置重复操作的时间
    ui->pushButton_left_1->setAutoRepeatInterval(100);//设置自动操作的间隔
    ui->pushButton_left_2->setAutoRepeat(true);
    ui->pushButton_left_2->setAutoRepeatDelay(100);
    ui->pushButton_left_2->setAutoRepeatInterval(100);
    //初始化
    ui->label_top->setText("100");
    ui->label_bottom->setText("100");
    current_label_flag_y=ui->label_flag->pos().y();
    //this->setAttribute(Qt::WA_StyledBackground);
}

Form::~Form()
{
    delete ui;
}

void Form::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    if(enable_flag)
    {
        QPoint position_bottom=ui->widget_bottom->mapFromGlobal(QCursor::pos());
        bottom_circle_selection=ui->widget_bottom->geometry().contains(QPoint(position_bottom.x(),position_bottom.y()+346));

        QPoint position_top=ui->widget_top->mapFromGlobal(QCursor::pos());
        top_circle_selection=ui->widget_top->geometry().contains(position_top);

        QPoint position_form=this->mapFromGlobal(QCursor::pos());
        form_selection=this->geometry().contains(position_form);

        QString widget_selection={"QWidget{\
                               border:3px solid white;\
                               border-radius:23px;\
                               min-width:40px;\
                               max-width:40px;\
                               min-height:40px;\
                               max-height:40px;\
                               background-color:rgb(0, 85, 255);\
                               }"};
        QString widget_no_selection={"QWidget{\
                               border:3px solid white;\
                               border-radius:23px;\
                               min-width:40px;\
                               max-width:40px;\
                               min-height:40px;\
                               max-height:40px;\
                               background-color:transparent;\
                               }"};
        QString label_selection={"QLabel{background-image: url(:/arrow-enable2.png);\
                                 min-height:20px;\
                                 min-width:20px;\
                                 max-height:20px;\
                                 max-width:20px;  }"};
        QString label_no_selection={"QLabel{background-image: url(:/arrow-enable1.png);\
                                    min-height:20px;\
                                    min-width:20px;\
                                    max-height:20px;\
                                    max-width:20px;  }"};
        if(form_selection&&(top_circle_selection||bottom_circle_selection))
        {
            ui->pushButton_left_1->show();
            ui->pushButton_left_2->show();
            if(top_circle_selection)
            {
                ui->widget_top->setStyleSheet(widget_selection);
                ui->label_center_1->setStyleSheet(label_selection);
                ui->widget_bottom->setStyleSheet(widget_no_selection);
                ui->label_center_2->setStyleSheet(label_no_selection);
            }
            else if(bottom_circle_selection)
            {
                ui->widget_top->setStyleSheet(widget_no_selection);
                ui->label_center_1->setStyleSheet(label_no_selection);
                ui->widget_bottom->setStyleSheet(widget_selection);
                ui->label_center_2->setStyleSheet(label_selection);
            }
        }
        else
        {
                ui->pushButton_left_1->hide();
                ui->pushButton_left_2->hide();
                ui->widget_top->setStyleSheet(widget_no_selection);
                ui->label_center_1->setStyleSheet(label_no_selection);
                ui->widget_bottom->setStyleSheet(widget_no_selection);
                ui->label_center_2->setStyleSheet(label_no_selection);
        }
    }
    update();
}

void Form::paintEvent(QPaintEvent *event)
{
    if(enable_flag)
    {
        if(top_circle_selection||bottom_circle_selection)
            filling_block(QColor(Qt::white));
        else
            filling_block(QColor(Qt::transparent));
    }
}


bool Form::form_setenable(bool flag)
{
    QString qss;
    if(flag)
    {
        QFile qssfile(":/control_enable.qss");
        qssfile.open(QFile::ReadOnly);
        if(qssfile.isOpen())
        {
            qss=QLatin1String(qssfile.readAll());
            setStyleSheet(qss);
            qssfile.close();
            enable_flag=true;
            return true;
        }
        return false;
    }
    else
    {
        QFile qssfile(":/control_disable.qss");
        qssfile.open(QFile::ReadOnly);
        if(qssfile.isOpen())
        {
            qss=QLatin1String(qssfile.readAll());
            setStyleSheet(qss);
            qssfile.close();
            enable_flag=false;
            return true;
        }
        return false;
    }
    return false;
}

bool Form::form_isenable()
{
    return enable_flag;
}

bool Form::top_circle_isselected()
{
    return top_circle_selection;
}

bool Form::bottom_circle_isselected()
{
    return bottom_circle_selection;
}

int Form::top_circle_number()
{
    int temp=ui->label_top->text().toInt();
    return temp;
}

int Form::bottom_circle_number()
{
    int temp=ui->label_bottom->text().toInt();
    return temp;
}

void Form::filling_block(QColor color)
{
        QPainter p(this);
        //方形区域
        QRect rect(QPoint(ui->widget_right->pos().x(),
                   ui->widget_right->pos().y()+current_label_flag_y),
                   QSize(46,
                   ui->widget_right->height()-current_label_flag_y-23));
        QPainterPath path_2;
        path_2.addRect(ui->widget_right->pos().x(),
                       ui->widget_right->pos().y()+current_label_flag_y,
                       46,
                       ui->widget_right->height()-current_label_flag_y-23);
        //下方圆形区域
        QPainterPath path;
        QRect rect_2(QPoint(rect.x(),rect.y()+ui->widget_right->height()-current_label_flag_y-46),
                     QSize(46,46));
        path.moveTo(rect_2.x()+23,rect_2.y()+23);
        path.arcTo(rect_2,0.0f,180.0f);
        //区域相减，获取不规则区域
        path_2=path_2-path;
        p.fillPath(path_2,QBrush(color));
        qDebug()<<rect<<"\n"<<ui->widget_right->pos()<<"\n"<<current_label_flag_y<<"\n"<<rect_2<<"\n";
}

void Form::moving_arrows()
{
    int temp1=ui->label_flag->y()/2;
    int temp2=(ui->widget_right->height()-ui->label_flag->pos().y())/2;
    ui->gridLayout_3->setContentsMargins(0,temp1,0,temp2);
}

void Form::on_pushButton_left_2_clicked() //减按钮
{
    if(top_circle_selection)
       {
            int temp_top=ui->label_top->text().toInt();
            int temp_bottom=ui->label_bottom->text().toInt();
            temp_top-=1;
            if(temp_top<0)
                temp_top=0;
            ui->label_top->setText(QString::number(temp_top));
            //标志移动
            QPoint current_label_flag_position=ui->label_flag->pos();
            int k=(temp_top*(ui->widget_right->height()-92))/static_cast<double>(temp_top+temp_bottom);
            QPoint new_label_flag_positon(current_label_flag_position.x(),k+46);
            ui->label_flag->setGeometry(new_label_flag_positon.x(),new_label_flag_positon.y(),46,3);
            current_label_flag_y=ui->label_flag->pos().y();
        }
        else if(bottom_circle_selection)
        {
            int temp_bottom=ui->label_bottom->text().toInt();
            int temp_top=ui->label_top->text().toInt();
            temp_bottom-=1;
            if(temp_bottom<0)
                temp_bottom=0;
            ui->label_bottom->setText(QString::number(temp_bottom));
            //标志移动
            QPoint current_label_flag_position=ui->label_flag->pos();
            int k=(temp_top*(ui->widget_right->height()-92))/static_cast<double>(temp_top+temp_bottom);
            QPoint new_label_flag_positon(current_label_flag_position.x(),k+46);
            ui->label_flag->setGeometry(new_label_flag_positon.x(),new_label_flag_positon.y(),46,3);
            current_label_flag_y=ui->label_flag->pos().y();
        }
        moving_arrows();
        update();
}

void Form::on_pushButton_left_1_clicked()//加按钮
{
    if(top_circle_selection)
    {
        int temp_top=ui->label_top->text().toInt();
        int temp_bottom=ui->label_bottom->text().toInt();
        temp_top+=1;
        if(temp_top>1000)
            temp_top=1000;
        ui->label_top->setText(QString::number(temp_top));
        //标志的移动
        QPoint current_label_flag_position=ui->label_flag->pos();
        int k=(temp_top*(ui->widget_right->height()-92))/static_cast<double>(temp_top+temp_bottom);
        QPoint new_label_flag_positon(current_label_flag_position.x(),k+46);
        ui->label_flag->setGeometry(new_label_flag_positon.x(),new_label_flag_positon.y(),46,3);
        current_label_flag_y=ui->label_flag->pos().y();
    }
    else if(bottom_circle_selection)
    {
        int temp_top=ui->label_top->text().toInt();
        int temp_bottom=ui->label_bottom->text().toInt();
        temp_bottom+=1;
        if(temp_bottom>1000)
            temp_bottom=1000;
        ui->label_bottom->setText(QString::number(temp_bottom));
        //标志的移动
        QPoint current_label_flag_position=ui->label_flag->pos();
        int k=(temp_top*(ui->widget_right->height()-92))/static_cast<double>(temp_top+temp_bottom);
        QPoint new_label_flag_positon(current_label_flag_position.x(),k+46);
        ui->label_flag->setGeometry(new_label_flag_positon.x(),new_label_flag_positon.y(),46,3);
        current_label_flag_y=ui->label_flag->pos().y();
    }
    moving_arrows();
    update();
}
