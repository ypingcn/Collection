#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent * e) override;
    void keyPressEvent(QKeyEvent * e) override;

    void init();
    bool isDead();
    void updateSnake();

private:
    static const int MAXN = 15;
    static const int MAXP = 20;
    QPainter * painter;

    enum gridType{APPLE,EMPTY,WALL};
    enum directionType{UP,DOWN,LEFT,RIGHT};


    directionType nextDirection = DOWN;
    bool hasApple = true;
    int score = 0;

    gridType grid[MAXN][MAXN];

    std::vector<std::pair<int,int>> snake;
};

#endif // MAINWINDOW_H
