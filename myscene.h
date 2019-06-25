#ifndef MYSCENE_H
#define MYSCENE_H

class MainWindow;  //防止重复包含
#include <QObject>
#include <QGraphicsScene>
#include <cstring>
#include "settingdialog.h"
#include "myitem.h"
#include "mainwindow.h"


class MyScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyScene(QObject *parent = nullptr);

signals:

public slots:
    void setBegin();
    void setEnd();
    void addObstacle1();
    void addObstacle2();

public:
    static int beginx,beginy;
    static int endx, endy;
    static bool isBegin,isEnd,isObstacle;
    MyItem *item[11][11];
    static int book[11][11];
    static void add(int x,int y);
    static int ObstacleCount;
    static int alln; //一个alln条路径可达
    static MainWindow *ptr;


};

#endif // MYSCENE_H
