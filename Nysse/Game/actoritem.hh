#ifndef ACTORITEM_HH
#define ACTORITEM_HH

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

namespace StudentSide {

//different type values
const int STOP = 0;
const int NYSSE = 1;
const int PASSENGER = 2;
const int PLAYER = 3;
const int PLAYER_2 = 4;

class ActorItem : public QGraphicsItem

{
public:
    ActorItem(int x, int y, int type);
    ~ActorItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCoord(int x, int y);


private:
    int x_;
    int y_;
    int type_;
};

}//namespace
#endif // ACTORITEM_HH
