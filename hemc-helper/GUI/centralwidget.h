#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QString>

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CentralWidget(QWidget *parent = 0);
    void getUrls(QString homeUrl = 0,QString eduUrl = 0,QString libUrl = 0); // get urls information

private:
    QString homeUrl,eduUrl,libUrl;
    QPushButton * btnHome,* btnEdu,* btnLib;

    void visitHome(); // visit homepage by default browser
    void visitEdu(); // visit education system by default browser
    void visitLib(); // visit library by default browser
};

#endif // CENTRALWIDGET_H
