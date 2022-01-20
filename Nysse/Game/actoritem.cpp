#include "actoritem.hh"



namespace StudentSide {

ActorItem::ActorItem(int x, int y, int type): x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_ ));
}

ActorItem::~ActorItem()
{

}

QRectF ActorItem::boundingRect() const
{
    if (type_ == STOP or type_ == PASSENGER) {
        return QRectF(0, 0, 5, 5);
    }
    else {
        return QRectF(0, 0, 15, 15);
    }
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    if (type_ == STOP)
    {
        QBrush brush(Qt::white);
        painter->setBrush(brush);
        painter->drawRect(bounds);
    }
    else if (type_ == NYSSE)
    {
        QBrush brush(Qt::blue);
        painter->setBrush(brush);
        painter->drawEllipse(bounds);
    }
    else if (type_ == PASSENGER)
    {
        QBrush brush(Qt::red);
        painter->setBrush(brush);
        painter->drawEllipse(bounds);
    }

    else if (type_ == PLAYER)
    {
        painter->drawImage(bounds, QImage(":/pictures/Photos/drone2.png"));
    }

}

void ActorItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

}//namespace
