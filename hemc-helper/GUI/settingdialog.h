#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    void getUrls(QString homeUrl = 0,QString eduUrl = 0,QString libUrl = 0);
    bool isUrl(QString url); // return true if argument is an url
    void newUrls(); // invoked when user click the yes button (btnYes)

private:
    QLabel * labOption,* labHome,* labEdu,* labLib;
    QComboBox * school;
    QLineEdit * edtHome,* edtEdu,* edtLib;
    QPushButton * btnYes,* btnNo;

    QStringList lstSchoolName = {
        tr("Sun Yat-Sen University"),
        tr("Ji'nan University"),
        tr("Guangzhou University"),
        tr("South China University of Technology"),
        tr("South China Normal University"),
        tr("Guangdong University of Technology"),
        tr("Guangzhou University of Chinese Medicine"),
        tr("Guangdong University of Foreign Studies"),
        tr("Guangdong Pharmaceutical University"),
        tr("Guangzhou Academy of Fine Arts"),
        tr("Guangzhou Medical University"),
        tr("Xinghai Conservatory of Music"),
        tr("---- Custom ----")
    }; // school name list , associating with updateEdts()

signals:
    void sendNewUrls(const QString newHomeUrl,const QString newEduUrls,const QString newLibUrl);
    //when all urls are legal,emitted to send new urls to MainWindow::setNewUrls()
private slots:
    void updateEdts(int schoolID);
    //update QLineEdit when QComboBox current index changed
};

#endif // SETTINGDIALOG_H
