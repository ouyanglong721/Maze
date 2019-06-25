
#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "settingdialog.h"


class MyItem : public QGraphicsRectItem
{
public:
    enum BLOCKTYPE{BSTART, BEND, BOBSTACLE, BNORMAL, BPATH};
    MyItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void setNum(const int num);
    void setBlockType(const BLOCKTYPE &type);

protected:
     void  mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
     int num;
     BLOCKTYPE blockType;
};

#endif // MYITEM_H
