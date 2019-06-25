#include "myscene.h"
#include <QPainter>
#include <QTime>


//各种静态变量
int MyScene::beginx = -1;
int MyScene::beginy = -1;
int MyScene::endx = -1;
int MyScene::endy = -1;
bool MyScene::isBegin = false;
bool MyScene::isEnd = false;
bool MyScene::isObstacle = false;
int MyScene::book[11][11] = {{0}};
int MyScene::ObstacleCount = 0;
int MyScene::alln = 0;
MainWindow* MyScene::ptr = nullptr;

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent)
{
    ptr = static_cast<MainWindow*>(parent);  //用于操作主窗口的对象
    memset(book, 0, sizeof(book));
    for(int i=0;i<SettingDialog::height;i++)
    {
        for(int j=0;j<SettingDialog::width;j++)
        {
            this->item[i][j] = new MyItem;
            this->item[i][j]->setPos(j*SettingDialog::block, i*SettingDialog::block);
            this->addItem(this->item[i][j]);
        }
    }
}

void MyScene::setBegin()
{
    isBegin = true;
    isEnd = false;
    isObstacle = false;
}

void MyScene::setEnd()
{
    isEnd = true;
    isBegin = false;
    isObstacle = false;
}

void MyScene::addObstacle1()  //手动增加
{
    isObstacle = true;
    isBegin = false;
    isEnd = false;
}

void MyScene::addObstacle2()   //自动添加
{
    isObstacle = false;
    isBegin = false;
    isEnd = false;
    if(MyScene::ObstacleCount == SettingDialog::width*SettingDialog::height-2)
    {
        QMessageBox::critical(NULL, "警告","不能在设置更多的障碍!!",QMessageBox::Ok, QMessageBox::Ok);
        MyScene::ptr->setObs1Enable(false);
        MyScene::ptr->setObs2Enable(false);
        return;
    }
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime())); //取随机数的
    int tx = qrand()%SettingDialog::height;
    int ty = qrand()%SettingDialog::width;
    while((tx == beginx && ty == beginy) || (tx == endx && ty == endy) || (MyScene::book[tx][ty] == 1))
    {
        tx = qrand()%SettingDialog::height;
        ty = qrand()%SettingDialog::width;
    }
    item[tx][ty]->setBlockType(MyItem::BOBSTACLE);
    this->add(tx, ty);
    MyScene::ObstacleCount++;
    item[tx][ty]->update();
    this->ptr->setStartEnable(true);
}



void MyScene::add(int x, int y)
{
    if(book[x][y] != 1)
    {
        book[x][y] = 1;
    }
}





