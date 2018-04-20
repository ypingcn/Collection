#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QCoreApplication>

class ImageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = nullptr);
    void last();
    void next();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    QPoint lastPoint;
    bool mousePress;

    QLabel * picture;
    QVBoxLayout * layout;

    QString currentPath = QCoreApplication::applicationDirPath();
    QStringList allFile;
    int imageIndex;

signals:

public slots:
};

#endif // IMAGEWINDOW_H
