#include "imagecarousel.h"

#include <QDebug>

ImageCarousel::ImageCarousel(QWidget *parent)
    : QWidget(parent)
{    
    lastAction = new QAction(tr("Last"),this);
    nextAction = new QAction(tr("Next"),this);
    quitAction = new QAction(tr("Quit"),this);
    connect(lastAction,SIGNAL(triggered()),this,SLOT(updateImage()));
    connect(nextAction,SIGNAL(triggered()),this,SLOT(updateImage()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(closeAll()));
    trayMenu = new QMenu(this);
    trayMenu->addAction(lastAction);
    trayMenu->addAction(nextAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);

    QIcon icon = QIcon(":/tray.png");
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));
    trayIcon->setIcon(icon);
    trayIcon->show();

    trayIcon->setContextMenu(trayMenu);

    window = new ImageWindow();
    window->show();
}

ImageCarousel::~ImageCarousel()
{

}

void ImageCarousel::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Context:
            this->raise();
            break;
        default:
            break;
    }
}

void ImageCarousel::updateImage()
{
    if(QObject::sender() == lastAction)
    {
        qDebug()<<"last";
    }
    else if(QObject::sender() == nextAction)
    {
        qDebug()<<"next";
    }
}

void ImageCarousel::closeAll()
{
    this->close();
}
