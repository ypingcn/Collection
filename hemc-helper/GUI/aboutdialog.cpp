#include "aboutdialog.h"

#include <QUrl>
#include <QSettings>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QDesktopServices>

AboutDialog::AboutDialog(QWidget * parent) : QDialog(parent)
{
    labIcon = new QLabel(this);
    labIcon->resize(10,10);
    QPixmap pic_tmp(":imgs/helper.png");
    QPixmap pic=pic_tmp.scaled(60,60,Qt::KeepAspectRatio);
    labIcon->setPixmap(pic);

    labCont = new QLabel();
    QSettings setting;
    labCont->setText(tr("%1<br>A simple tool.").arg(setting.applicationName()));

    btnThx = new QPushButton();
    btnThx->setText(tr("Thanks"));
    btnAuthor = new QPushButton();
    btnAuthor->setText(tr("Author"));

    QObject::connect(btnThx,&QPushButton::clicked,this,&AboutDialog::thanks);
    QObject::connect(btnAuthor,&QPushButton::clicked,this,&AboutDialog::visitauthor);

    QHBoxLayout * line1 = new QHBoxLayout();
    line1->addWidget(labIcon);
    line1->addWidget(labCont);
    QHBoxLayout * line2 = new QHBoxLayout();
    line2->addWidget(btnThx);
    line2->addWidget(btnAuthor);

    QGridLayout * MainLayout = new QGridLayout(this);
    MainLayout->addLayout(line1,0,0);
    MainLayout->addLayout(line2,1,0);
    MainLayout->setSizeConstraint(QLayout::SetFixedSize);

}

void AboutDialog::visitauthor()
{
    QDesktopServices::openUrl(QUrl(QString("https://ypingcn.github.io/wiki")));
}

void AboutDialog::thanks()
{
    QDesktopServices::openUrl(QUrl(QString("https://github.com/gzhemc-helper")));
}
