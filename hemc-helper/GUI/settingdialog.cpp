#include "settingdialog.h"

#include <QComboBox>
#include <QMessageBox>
#include <QHBoxLayout>


SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Setting"));

    labOption = new QLabel(tr("use built-in option"));
    labOption->setMinimumWidth(150);
    labOption->setAlignment(Qt::AlignCenter);
    labHome = new QLabel(tr("homepage url"));
    labHome->setMinimumWidth(150);
    labHome->setAlignment(Qt::AlignCenter);
    labEdu = new QLabel(tr("education system url"));
    labEdu->setMinimumWidth(150);
    labEdu->setAlignment(Qt::AlignCenter);
    labLib = new QLabel(tr("library url"));
    labLib->setMinimumWidth(150);
    labLib->setAlignment(Qt::AlignCenter);

    school = new QComboBox();
    school->setMinimumWidth(200);
    school->addItems(lstSchoolName);
    QObject::connect(school,SIGNAL(currentIndexChanged(int)),this,SLOT(updateEdts(int)));

    edtHome = new QLineEdit();
    edtHome->setMinimumWidth(200);
    edtEdu = new QLineEdit();
    edtEdu->setMinimumWidth(200);
    edtLib = new QLineEdit();
    edtLib->setMinimumWidth(200);

    btnYes = new QPushButton(tr("YES"));
    QObject::connect(btnYes,&QPushButton::clicked,this,&SettingDialog::newUrls);
    btnNo = new QPushButton(tr("NO"));
    QObject::connect(btnNo,&QPushButton::clicked,this,&QDialog::close);

    QHBoxLayout * line0 = new QHBoxLayout;
    line0->addWidget(labOption);
    line0->addWidget(school);
    QHBoxLayout * line1 = new QHBoxLayout;
    line1->addWidget(labHome);
    line1->addWidget(edtHome);
    QHBoxLayout * line2 = new QHBoxLayout;
    line2->addWidget(labEdu);
    line2->addWidget(edtEdu);
    QHBoxLayout * line3 = new QHBoxLayout;
    line3->addWidget(labLib);
    line3->addWidget(edtLib);
    QHBoxLayout * line4 = new QHBoxLayout;
    line4->addStretch();
    line4->addWidget(btnYes);
    line4->addWidget(btnNo);

    QGridLayout * mainLayout = new QGridLayout(this);
    mainLayout->addLayout(line0,0,0);
    mainLayout->addLayout(line1,1,0);
    mainLayout->addLayout(line2,2,0);
    mainLayout->addLayout(line3,3,0);
    mainLayout->addLayout(line4,4,0);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}

void SettingDialog::getUrls(QString homeUrl, QString eduUrl, QString libUrl)
{
    edtHome->setText(homeUrl);
    edtEdu->setText(eduUrl);
    edtLib->setText(libUrl);

    QString dic[12] = {
        "sysu",
        "jnu",
        "gzhu",
        "scut",
        "scnu",
        "gdut",
        "gzhtcm",
        "gdufs",
        "gdpu",
        "gzarts",
        "gzhmc",
        "xhcom"
    };
    int currentIndex = 12;
    for(int i=0;i<12;i++)
    {
        if(homeUrl.indexOf(dic[i]) != -1 && eduUrl.indexOf(dic[i]) != -1 && libUrl.indexOf(dic[i]) != -1)
        {
            currentIndex = i;
            break;
        }
    }
    school->setCurrentIndex(currentIndex);
}

void SettingDialog::updateEdts(int schoolID)
{
    QString newHomeUrl,newEduUrl,newLibUrl;
    switch (schoolID) {
    case 0:
        newHomeUrl="http://www.sysu.edu.cn";
        newEduUrl="http://uems.sysu.edu.cn/jwxt";
        newLibUrl="http://library.sysu.edu.cn";
        break;
    case 1:
        newHomeUrl="http://www.jnu.edu.cn";
        newEduUrl="http://jwc.jnu.edu.cn";
        newLibUrl="http://libgp.jnu.edu.cn";
        break;
    case 2:
        newHomeUrl="http://www.gzhu.edu.cn";
        newEduUrl="http://jwc.gzhu.edu.cn";
        newLibUrl="http://lib.gzhu.edu.cn";
        break;
    case 3:
        newHomeUrl="http://www.scut.edu.cn";
        newEduUrl="http://www.scut.edu.cn/jw2005";
        newLibUrl="http://www.lib.scut.edu.cn";
        break;
    case 4:
        newHomeUrl="http://www.scnu.edu.cn";
        newEduUrl="http://jw.scnu.edu.cn";
        newLibUrl="http://lib.scnu.edu.cn";
        break;
    case 5:
        newHomeUrl="http://www.gdut.edu.cn";
        newEduUrl="http://jwgldx.gdut.edu.cn";
        newLibUrl="http://library.gdut.edu.cn";
        break;
    case 6:
        newHomeUrl="http://www.gzhtcm.edu.cn";
        newEduUrl="http://jw.gzucm.edu.cn";
        newLibUrl="http://library.gzhtcm.edu.cn";
        break;
    case 7:
        newHomeUrl="http://www.gdufs.edu.cn";
        newEduUrl="http://jwc.gdufs.edu.cn";
        newLibUrl="http://lib.gdufs.edu.cn";
        break;
    case 8:
        newHomeUrl="http://www.gdpu.edu.cn";
        newEduUrl="http://dep.gdpu.edu.cn/jwc";
        newLibUrl="http://www.lib.gdpu.edu.cn/rgzn/gzzd";
        break;
    case 9:
        newHomeUrl="http://www.gzarts.edu.cn";
        newEduUrl="http://jwxt.gzarts.edu.cn";
        newLibUrl="http://lib.gzarts.edu.cn";
        break;
    case 10:
        newHomeUrl="http://www.gzhmc.edu.cn";
        newEduUrl="http://jwc.gzhmc.edu.cn";
        newLibUrl="http://lib.gzhmc.edu.cn";
        break;
    case 11:
        newHomeUrl="http://www.xhcom.edu.cn";
        newEduUrl="http://jwc.xhcom.edu.cn";
        newLibUrl="http://www.xhcomlib.cn";
        break;
    case 12:
        newHomeUrl="http://";
        newEduUrl="http://";
        newLibUrl="http://";
    default:
        break;
    }

    edtEdu->setText(newEduUrl);
    edtHome->setText(newHomeUrl);
    edtLib->setText(newLibUrl);
}

void SettingDialog::newUrls()
{
    if( isUrl(edtHome->text()) && isUrl(edtEdu->text()) && isUrl(edtLib->text()) )
    {
        emit sendNewUrls(edtHome->text(),edtEdu->text(),edtLib->text());
        QMessageBox::information(this,tr("RIGHT URL"),tr("right"),QMessageBox::Yes);
        close();
    }
    else
        QMessageBox::information(this,tr("WRONG URL"),tr("the url should include 'http://' (or 'https://' ) and have complete url"));
}

bool SettingDialog::isUrl(QString url)
{
    if(url == NULL)
        return false;

    bool haveHttp = false,haveDomain = false;
    if( url.indexOf("https://") != -1 || url.indexOf("http://") != -1 )
        haveHttp = true;
    if( url.indexOf(".cn") != -1 || url.indexOf(".com") != -1)
        haveDomain = true;

    if(haveHttp && haveDomain)
        return true;
    return false;
}
