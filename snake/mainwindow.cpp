#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMaximumSize(MAXN*MAXP,MAXN*MAXP);
    this->setMinimumSize(MAXN*MAXP,MAXN*MAXP);
    this->setStyleSheet("QMainWindow{background-image: url(:/wallpaper.jpg);}");
    painter = new QPainter();
}

MainWindow::~MainWindow()
{

}

void MainWindow::init()
{
    memset(grid,EMPTY,sizeof(grid));
    for(int i = 0 ; i < MAXN; i ++)
        grid[i][0] = grid[0][i] = grid[i][MAXN-1] = grid[MAXN-1][i] = WALL;
    snake.clear();
    score = 0;
    nextDirection = DOWN;
    snake.push_back(std::make_pair(MAXN/2,MAXN/2 + 1));
    snake.push_back(std::make_pair(MAXN/2,MAXN/2));
    snake.push_back(std::make_pair(MAXN/2,MAXN/2 - 1));

    std::srand(time(0));
    int appleX = std::rand() % (MAXN - 2) + 1,appleY = std::rand() % (MAXN - 2) + 1;
    grid[appleX][appleY] = APPLE;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    this->setWindowTitle(tr("Score : ")+QString::number(score)+tr(",length : ")+QString::number(snake.size()));

    painter->begin(this);
    painter->setPen(QPen(QColor(0, 160, 230), 2));

    painter->setBrush(QColor(255, 255, 255));

    for(unsigned i = 0 ; i < snake.size();i++)
    {
        painter->drawRect(snake[i].first*MAXP,snake[i].second*MAXP,MAXP,MAXP);
    }
    painter->setBrush(QColor(255, 160, 90));
    for(int i = 0 ; i < MAXN ; i ++)
    {
        for(int j = 0 ; j < MAXN ; j ++)
        {
            if(grid[i][j] == WALL)
            {
                painter->drawRect(i*MAXP,j*MAXP,MAXP,MAXP);
            }
            if(grid[i][j] == APPLE)
            {
                painter->setBrush(QColor(255, 0, 0));
                painter->drawRect(i*MAXP,j*MAXP,MAXP,MAXP);
                painter->setBrush(QColor(255, 160, 90));
            }
        }
    }

    painter->end();
}

void MainWindow::keyPressEvent(QKeyEvent * e)
{
    if( e->key() == Qt::Key_Left && nextDirection != LEFT && nextDirection != RIGHT)
        nextDirection = LEFT;
    else if( e->key() == Qt::Key_Right && nextDirection != LEFT && nextDirection != RIGHT)
        nextDirection = RIGHT;
    else if(e->key() == Qt::Key_Up && nextDirection != UP && nextDirection != DOWN)
        nextDirection = UP;
    else if(e->key() == Qt::Key_Down && nextDirection != UP && nextDirection != DOWN)
        nextDirection = DOWN;
}

void MainWindow::updateSnake()
{
    int headX = snake[0].first,headY = snake[0].second;
    int tailX = snake[snake.size()-1].first,tailY = snake[snake.size()-1].second;

    for(int i = snake.size() - 1; i > 0;i--)
        snake[i] = std::make_pair(snake[i-1].first,snake[i-1].second);

    if(nextDirection == UP)
    {
        if(grid[headX][headY-1] == APPLE)
        {
            snake.push_back(std::make_pair(tailX,tailY));
            grid[headX][headY-1] = EMPTY;
            hasApple = false;
            score ++;
        }

        snake[0] = std::make_pair(headX,headY-1);
    }
    else if(nextDirection == DOWN)
    {
        if(grid[headX][headY+1] == APPLE)
        {
            snake.push_back(std::make_pair(tailX,tailY));
            grid[headX][headY+1] = EMPTY;
            hasApple = false;
            score ++;
        }
        snake[0] = std::make_pair(headX,headY+1);
    }
    else if(nextDirection == LEFT)
    {
        if(grid[headX-1][headY] == APPLE)
        {
            snake.push_back(std::make_pair(tailX,tailY));
            grid[headX-1][headY] = EMPTY;
            hasApple = false;
            score ++;
        }
        snake[0] = std::make_pair(headX-1,headY);
    }
    else if(nextDirection == RIGHT)
    {
        if(grid[headX+1][headY] == APPLE)
        {
            snake.push_back(std::make_pair(tailX,tailY));
            grid[headX+1][headY] = EMPTY;
            hasApple = false;
            score ++;
        }
        snake[0] = std::make_pair(headX+1,headY);
    }
    if(!hasApple)
    {
        grid[std::rand() % (MAXN - 2) + 1][std::rand() % (MAXN - 2) + 1] = APPLE;
        hasApple = true;
    }
}

bool MainWindow::isDead()
{
    for(unsigned i=0;i < snake.size();i++)
    {
        int x = snake[i].first,y = snake[i].second;
        if(x <= 0  || x >= MAXN - 1 || y <= 0 || y >= MAXN - 1)
            return true;
    }
    return false;
}
