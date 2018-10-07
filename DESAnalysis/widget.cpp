#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->plotWidget->xAxis->setLabel(tr("Change Digit"));
    ui->plotWidget->yAxis->setLabel(tr("Number"));
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    for(int i = 1 ; i <= 8 ; i++)
        ui->boxSBoxId->addItem(QString::number(i));
    for(int i = 1 ; i<= 64 ; i++)
        ui->boxChangeDigit->addItem(QString::number(i));
    for(int i = 0 ; i < 64 ; i++)
    {
        QString num = QString::number(i,2);
        while(num.length() < 6)
            num = "0" + num;
        ui->boxInDiff->addItem(num);
    }
    ui->progressBar->setValue(0);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(10000);
    connect(ui->btnInDiffGo,SIGNAL(clicked(bool)),this,SLOT(sbox_difference()));
    connect(ui->btnChangeGo,SIGNAL(clicked(bool)),this,SLOT(digit_change()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sbox_difference()
{
    QLibrary lib("./libdes.dll");
    if(!lib.load())
    {
        qDebug()<<"lib load error";
        return;
    }
    getLibdes getSharedLibdes = (getLibdes)lib.resolve("getSharedLibdes");
    if(!getSharedLibdes)
    {
        qDebug()<<"getSharedLibdes error";
        return;
    }
    Libdes * des = getSharedLibdes();
    int sBoxId = ui->boxSBoxId->currentIndex();
    string inString = ui->boxInDiff->currentText().toStdString();
    int siz = ui->tableWidget->rowCount();
    for(int i = siz; i >= 0 ; i--)
        ui->tableWidget->removeRow(i);
    bitset<6> inDiff;
    for(int i = 0 ; i < (int)inString.length() ; i++)
    {
        if(inString[i] == '1')
            inDiff.set(6-i,1);
    }
    des->getSBoxDifference(sBoxId,inDiff);
    vector<std::pair<vector<bitset<6>>,bitset<4>>> res = des->getSBoxOutput();
    for(auto val : res)
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::fromStdString(val.second.to_string())));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(QString::number(val.first.size())));
        QString probable = "";
        for(bitset<6> b : val.first)
            probable = probable + " " + QString::fromStdString(b.to_string());
        ui->tableWidget->setItem(row,2,new QTableWidgetItem(probable));
    }
}

void Widget::digit_change()
{
    srand(time(nullptr));
    if(ui->edtPlain->text() == "" && ui->edtKey->text() == "")
    {
        QMessageBox::information(this,"ERROR","empty plain text or empty key.",QMessageBox::Yes);
        return;
    }
    if(ui->edtPlain->text().length() != 8)
    {
        QMessageBox::information(this,"ERROR","plain text's length should be 8.",QMessageBox::Yes);
        return;
    }
    if(ui->edtKey->text().length() != 8)
    {
        QMessageBox::information(this,"ERROR","key's length should be 8.",QMessageBox::Yes);
        return;
    }
    if(!ui->btnChangeCipherText->isChecked() && !ui->btnChangePlainText->isChecked())
    {
        QMessageBox::information(this,"ERROR","choose ChangeCipherText or ChangePlainText.",QMessageBox::Yes);
        return;
    }
    ui->btnChangeGo->setEnabled(false);
    QLibrary lib("./libdes.dll");
    if(!lib.load())
    {
        qDebug()<<"lib load error";
        return;
    }
    getLibdes getSharedLibdes = (getLibdes)lib.resolve("getSharedLibdes");
    if(!getSharedLibdes)
    {
        qDebug()<<"getSharedLibdes error";
        return;
    }
    Libdes * des = getSharedLibdes();
    bitset<64> key = des->charToBitset(ui->edtKey->text().toStdString().c_str());
    bitset<64> plain = des->charToBitset(ui->edtPlain->text().toStdString().c_str());
    bitset<64> changeRecord;
    QVector<double> values(64,0.0);
    int changeDigit = ui->boxChangeDigit->currentIndex() + 1;
    des->setKey(key);

    bitset<64> before,after,result;
    if(ui->btnChangePlainText->isChecked())
    {
        for(int i = 1 ; i <= 10000 ; i++)
        {
            before = des->encrypt(plain);
            changeRecord.reset();
            bitset<64> plainAfter = plain;
            while(changeRecord.count() < changeDigit)
            {
                int pos = rand() % 64;
                if(!changeRecord.test(pos))
                {
                    plainAfter.flip(pos);
                    changeRecord.set(pos);
                }
            }
            after = des->encrypt(plainAfter);
            result = before ^ after;
            values[result.count()]++;
            ui->progressBar->setValue(i);
        }
    }
    else if(ui->btnChangeCipherText->isChecked())
    {
        for(int i = 1 ; i <= 10000 ; i++)
        {
            des->setKey(key);
            before = des->encrypt(plain);
            changeRecord.reset();
            bitset<64> keyAfter = key;
            while(changeRecord.count() < changeDigit)
            {
                int pos = rand() % 64;
                if(!changeRecord.test(pos))
                {
                    keyAfter.flip(pos);
                    changeRecord.set(pos);
                }
            }
            des->setKey(keyAfter);
            after = des->encrypt(plain);
            result = before ^ after;
            values[result.count()]++;
            ui->progressBar->setValue(i);
        }
    }
    ui->btnChangeGo->setEnabled(true);

    ui->plotWidget->clearPlottables();
    double maxx = 0.0;
    for(int i = 0 ; i < values.size();i++)
        maxx = std::max(values[i],maxx);
    ui->plotWidget->yAxis->setRange(0,(int)maxx+20);
    ui->plotWidget->xAxis->setRange(0,64);

    QCPBars* bars=new QCPBars(ui->plotWidget->xAxis,ui->plotWidget->yAxis);
    QVector<double> index(64);
    for(int i=0;i<64;++i)
        index[i]=i;
    bars->setData(index,values);
    ui->plotWidget->replot();
}

