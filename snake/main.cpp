#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.init();
    w.show();
    while(true)
    {
        w.repaint();

        QTime countDown;
        countDown.start();
        while(countDown.elapsed()<300)
            QCoreApplication::processEvents();

        w.updateSnake();

        if(w.isDead())
        {
            QMessageBox::StandardButton choice;
            choice = QMessageBox::information(nullptr,QObject::tr("Over"),QObject::tr("Game Over,again?"),
                                              QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);

            if(choice == QMessageBox::Yes)
            {
               w.init();
               w.repaint();
            }
            else if(choice == QMessageBox::No)
                return 0;

        }

        if(!w.isVisible())
            return 0;
    }
    return a.exec();
}
