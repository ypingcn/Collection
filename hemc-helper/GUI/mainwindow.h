#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "centralwidget.h"
#include "settingdialog.h"
#include "aboutdialog.h"

#include <QMainWindow>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QString homeUrl="http://www.gdut.edu.cn",eduUrl="http://jwgldx.gdut.edu.cn",libUrl="http://library.gdut.edu.cn";
    QAction * aboutAction,* helpAction,* quitAction,* setAction, *cleanAction;

    CentralWidget * c;
    AboutDialog * a;
    SettingDialog * s;

    void about();
    void help();
    void quit();
    void set();
    void clean();

    void readSetting();
    void writeSetting();

    bool cleanAllSettings = false;
public slots:
    void setNewUrls(QString newHomeUrl,QString newEduUrl,QString newLibUrl); //get newest urls from SettingDialog and set it
};

#endif // MAINWINDOW_H
