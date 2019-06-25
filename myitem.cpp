#include "myitem.h"

#include <QCursor>
#include <QPainter>
#include "myscene.h"
#include <QMessageBox>

MyItem::MyItem()
{
    this->setRect(0,0, SettingDialog::block, SettingDialog::block);  //矩形的大小
    num = -1;
    blockType = BNORMAL;

}
 void MyItem::setNum(const int num)
 {
     this->num = num;
 }

 void MyItem::setBlockType(const BLOCKTYPE &type)
 {
     blockType = type;
 }


 void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
 {

     switch(blockType)
     {
     case BPATH:
         painter->setBrush(Qt::red);
         break;
     case BSTART:
         painter->setBrush(Qt::green);
         break;
     case BEND:
         painter->setBrush(Qt::yellow);
         break;
     case BOBSTACLE:
         painter->setBrush(Qt::gray);
         break;
     default:
         painter->setBrush(Qt::white);
         break;
     }
     painter->drawRect(this->rect());

     if(num != -1)
     {
        painter->drawText(10, 13,40, 40, Qt::AlignCenter, QString("%1").arg(num));
     }
 }




void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     int x = this->pos().y()/SettingDialog::block;
     int y = this->pos().x()/SettingDialog::block;
     if(MyScene::isBegin)
     {
        MyScene::isBegin = false;  //只能单次点击
        MyScene::beginx = x;
        MyScene::beginy = y;
        this->setBlockType(BSTART);
        MyScene::ptr->setBeginEnable(false);
        MyScene::ptr->setEndEnable(true);
        MyScene::ptr->setStartEnable(false);
        MyScene::ptr->setObs1Enable(false);
        MyScene::ptr->setObs2Enable(false);
     }

     else if(MyScene::isEnd)
     {
         MyScene::isEnd = false; //只能单次点击
         MyScene::endx = x;
         MyScene::endy = y;
         this->setBlockType(BEND);
         MyScene::ptr->setBeginEnable(false);
         MyScene::ptr->setEndEnable(false);
         MyScene::ptr->setStartEnable(false);
         MyScene::ptr->setObs1Enable(true);
         MyScene::ptr->setObs2Enable(true);
     }
    else if(MyScene::isObstacle)
     {
         MyScene::ptr->setBeginEnable(false);
         MyScene::ptr->setEndEnable(false);
         MyScene::ptr->setStartEnable(true);
/*
         if(MyScene::ObstacleCount == SettingDialog::width*SettingDialog::height-2)
         {
             QMessageBox::critical(NULL, "警告","不能在设置更多的障碍!!",QMessageBox::Ok, QMessageBox::Ok);
             MyScene::ptr->setObs1Enable(false);
             MyScene::ptr->setObs2Enable(false);
             return;
         }
*/

         //将障碍选为起点或终点，不可行

         if(x == MyScene::beginx && y ==MyScene::beginy)
         {
            MyScene::ptr->setSatausBar("不能将起点设为障碍！！");
            return;
         }
         if(x == MyScene::endx && y ==MyScene::endy)
         {
            MyScene::ptr->setSatausBar("不能将终点设为障碍！！");
            return;
         }
         this->setBlockType(BOBSTACLE);
         MyScene::add(x, y);
          MyScene::ObstacleCount++;
     }
        this->update();
}

