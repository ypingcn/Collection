#include "imagewindow.h"

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setMouseTracking(true);
    mousePress = false;
}

void ImageWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mousePress = true;
        lastPoint = event->pos();
    }
}

void ImageWindow::mouseReleaseEvent(QMouseEvent *event)
{
    mousePress = false;
}

void ImageWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mousePress)
    {
        QPoint nextPoint = event->globalPos();;
        this->move(nextPoint-lastPoint);
    }
}
