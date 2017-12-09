#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QSplashScreen>
#include <QDesktopWidget>
#include <QTime>
#include <QNetworkAccessManager>
#include <QUrl>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setApplicationName("hemc-helper");
    QCoreApplication::setOrganizationName("ypingcn");
    QCoreApplication::setOrganizationDomain("https://ypingcn.coding.me");
    QCoreApplication::setApplicationVersion("v0.1.20170219");

    QTranslator trans;
    trans.load("zh-cn.qm");
    a.installTranslator(&trans);


//    QSplashScreen * start = new QSplashScreen;
//    start->setPixmap(QPixmap(":/imgs/hemc.png"));
//    start->show();
//    start->showMessage(QObject::tr("Next station is gzhemc,please get reagy to get off."),Qt::AlignCenter,Qt::white);

//    QTime t;
//    t.start();
//    while(t.elapsed()<1500)
//        QCoreApplication::processEvents();


    MainWindow w;
    w.resize(300,200);
    w.show();
    w.move(( QApplication::desktop()->width()-w.width() )/2,( QApplication::desktop()->height()-w.height() )/2 );
//    start->finish(&w);
//    delete start;

    return a.exec();
}
