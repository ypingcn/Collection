#ifndef WIDGET_H
#define WIDGET_H

#include "include/libdes/libdes.h"

#include <QWidget>
#include <QLibrary>


typedef Libdes* (*getLibdes)();

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;


private slots:
    void sbox_difference();
    void digit_change();
};

#endif // WIDGET_H
