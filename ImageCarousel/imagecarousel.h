#ifndef IMAGECAROUSEL_H
#define IMAGECAROUSEL_H

#include "imagewindow.h"

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>

class ImageCarousel : public QWidget
{
    Q_OBJECT

public:
    ImageCarousel(QWidget *parent = 0);
    ~ImageCarousel();

private:
    QSystemTrayIcon * trayIcon;
    QMenu * trayMenu;
    QAction * nextAction;
    QAction * lastAction;
    QAction * quitAction;

    ImageWindow * window;

private slots:
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void updateImage();
    void closeAll();
};

#endif // IMAGECAROUSEL_H
