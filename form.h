#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QMouseEvent>
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    bool form_setenable(bool flag); //flag==true 设置使能状态 flag==false 设置失效状态
    bool form_isenable();
    bool top_circle_isselected();
    bool bottom_circle_isselected();

    int top_circle_number(); //获取上方圆框的值
    int bottom_circle_number();//获取下方圆框的值

    void filling_block(QColor color);
    void moving_arrows();
private slots:
    void on_pushButton_left_2_clicked(); //减按键
    void on_pushButton_left_1_clicked();

private:
    Ui::Form *ui;
    bool enable_flag;
    bool top_circle_selection;
    bool bottom_circle_selection;
    bool form_selection;
    int current_label_flag_y;
};

#endif // FORM_H
