#include "centralwidget.h"

#include <QUrl>
#include <QGridLayout>
#include <QMessageBox>
#include <QDesktopServices>

CentralWidget::CentralWidget(QWidget *parent) : QWidget(parent)
{
    btnHome = new QPushButton();
    btnHome->setText(tr("homepage"));
    btnEdu = new QPushButton();
    btnEdu->setText(tr("education system"));
    btnLib = new QPushButton();
    btnLib->setText(tr("library"));

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(btnHome);
    layout->addWidget(btnEdu);
    layout->addWidget(btnLib);

    QObject::connect(btnHome,&QPushButton::clicked,this,&CentralWidget::visitHome);
    QObject::connect(btnEdu,&QPushButton::clicked,this,&CentralWidget::visitEdu);
    QObject::connect(btnLib,&QPushButton::clicked,this,&CentralWidget::visitLib);
}

void CentralWidget::visitHome()
{
//    QMessageBox::information(this, tr("Visit homepage"), tr("visit homepage by default browser"));
    QDesktopServices::openUrl(QUrl(homeUrl));
}

void CentralWidget::visitEdu()
{
//    QMessageBox::information(this, tr("Visit education system"), tr("visit education system by default browser"));
    QDesktopServices::openUrl(QUrl(eduUrl));
}

void CentralWidget::visitLib()
{
//    QMessageBox::information(this, tr("Visit library"), tr("visit library by default browser"));
    QDesktopServices::openUrl(QUrl(libUrl));
}

void CentralWidget::getUrls(QString homeUrl, QString eduUrl, QString libUrl)
{
    this->homeUrl = homeUrl;
    this->eduUrl = eduUrl;
    this->libUrl = libUrl;
}
