#include "mainwindow.h"

#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QSettings>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>


MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent)
{

    this->setWindowTitle(tr("HEMC - helper"));
    this->resize(200,200);

    helpAction = new QAction(tr("Help"));
    helpAction->setStatusTip(tr("Help about HEMC-helper"));
    aboutAction = new QAction(QIcon(":/imgs/about.png"),tr("About"));
    aboutAction->setStatusTip(tr("About HEMC-helper"));
    quitAction = new QAction(QIcon(":/imgs/exit.png"),tr("Quit"));
    quitAction->setStatusTip(tr("Quit HEMC-helper"));
    setAction = new QAction(QIcon(":imgs/setting.png"),tr("Setting"));
    setAction->setStatusTip(tr("Change settings"));
    cleanAction = new QAction(QIcon(":/imgs/clean.png"),tr("Clean Setting"));
    setAction->setStatusTip(tr("Clean and use default setting"));
    QMenu * file = menuBar()->addMenu(tr("Menu"));
    file->addAction(helpAction);

    QToolBar * tool = addToolBar(tr("tool"));
    tool->setObjectName("tool");
    tool->addAction(setAction);
    tool->addAction(cleanAction);
    tool->addAction(aboutAction);
    tool->addAction(quitAction);

    QObject::connect(aboutAction,&QAction::triggered,this,&MainWindow::about);
    QObject::connect(helpAction,&QAction::triggered,this,&MainWindow::help);
    QObject::connect(quitAction,&QAction::triggered,this,&MainWindow::quit);
    QObject::connect(setAction,&QAction::triggered,this,&MainWindow::set);
    QObject::connect(cleanAction,&QAction::triggered,this,&MainWindow::clean);

    c = new CentralWidget();
    c->getUrls(homeUrl,eduUrl,libUrl);
    setCentralWidget(c);

    statusBar();

    readSetting();
}

MainWindow::~MainWindow()
{

}

void MainWindow::help()
{
    QMessageBox::information(this, tr("Help"), tr("Under construction"));
}

void MainWindow::quit()
{
    if(QMessageBox::Yes == QMessageBox::question( this,tr("Exit"),tr("Sure to exit?"),QMessageBox::Yes|QMessageBox::No,QMessageBox::No) )
    {
        if(!cleanAllSettings)
            writeSetting();
        this->close();
    }

}

void MainWindow::about()
{
    a = new AboutDialog(this);
    a->exec();
}

void MainWindow::set()
{
    s = new SettingDialog(this);
    s->getUrls(homeUrl,eduUrl,libUrl);
    QObject::connect(s,&SettingDialog::sendNewUrls,this,&MainWindow::setNewUrls);
    s->exec();
}

void MainWindow::setNewUrls(QString newHomeUrl, QString newEduUrl, QString newLibUrl)
{
    this->homeUrl = newHomeUrl;
    this->eduUrl = newEduUrl;
    this->libUrl = newLibUrl;
    c->getUrls(homeUrl,eduUrl,libUrl);
}

void MainWindow::clean()
{
    if(QMessageBox::Yes == QMessageBox::question(this,tr("Clean setting"),tr("Sure to clean all information?"),QMessageBox::Yes | QMessageBox::No,QMessageBox::No))
    {
        QSettings setting;
        setting.clear();
        cleanAllSettings = true;
        homeUrl = eduUrl = libUrl = "http://";
    }
}

void MainWindow::readSetting()
{
    QSettings setting;
    setting.beginGroup("MainWindows");
    if(setting.contains("state"))
        restoreState(setting.value("state").toByteArray());
    if(setting.contains("size"))
        resize(setting.value("size").toSize());
    setting.endGroup();
}

void MainWindow::writeSetting()
{
    QSettings setting;
    setting.beginGroup("MainWindows");
    setting.setValue("state",saveState());
    setting.setValue("size",size());
    setting.endGroup();
}
