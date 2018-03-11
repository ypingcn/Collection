#include "imagewindow.h"

#include <QDir>
#include <QMessageBox>

ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setMouseTracking(true);
    mousePress = false;

    layout = new QVBoxLayout(this);
    picture = new QLabel();
    layout->addWidget(picture);

    QDir dir(currentPath);
    QStringList filters;
    filters.append("*.jpg");
    allFile = dir.entryList(filters,QDir::Files|QDir::Readable, QDir::Name);

    imageIndex = 0;
    if(allFile.size() != 0)
        picture->setPixmap(QPixmap(currentPath+"/"+allFile[imageIndex]));
    else
    {
        QMessageBox::warning(this,
                             QObject::tr("Size Error"),
                             QObject::tr("Image file doesn't exist"),
                             QMessageBox::Ok);
        picture->setPixmap(QPixmap(":/error_default.png"));
    }

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
