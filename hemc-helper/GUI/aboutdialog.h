#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>

class AboutDialog : public QDialog
{
public:
    AboutDialog(QWidget * parent=0);
private:
    QLabel * labIcon,* labCont;
    QPushButton * btnThx,* btnAuthor;
    void thanks(); // visit github.com/ypingcn/gzhemc-helper
    void visitauthor();  // visit ypingcn.github.io
};

#endif // ABOUTDIALOG_H
