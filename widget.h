#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <form.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    ~Widget();

private:
    Ui::Widget *ui;
    Form *qss_control;
};

#endif // WIDGET_H
