#include "actoritem.hh"

namespace StudentSide {

ActorItem::ActorItem(int x, int y, int type):x_(x), y_(y), type_(type)
{
    setPos(mapToParent(x_, y_ ));
}

ActorItem::~ActorItem()
{

}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, WIDTH, HEIGHT);
}

QRectF ActorItem::stopRect() const
{
    return QRectF(0, 0, 10, 10);
}

QRectF ActorItem::passengerActor() const
{
    return QRectF(0, 0, 5, 5);
}

QRectF ActorItem::playerActor() const
{
    return QRectF(0, 0, 15, 15);
}


void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color(type_%256, type_%256, 255);
    QBrush brush(color);
    painter->setBrush(brush);
    if(type_ == 50) {
        painter->drawImage(boundingRect(), QImage(BUS_PIC));
    } else if(type_ == 249) {
        painter->drawEllipse(passengerActor());
    } else if (type_ == 1) {
        painter->drawImage(playerActor(), QImage(COPTER_PIC));
    } else if(type_ == 2) {
        painter->drawImage(playerActor(), QImage(PLANE_PIC));
    } else if (type_ == 3) {
        painter->drawImage(playerActor(), QImage(AIRPLANE_PIC));
    } else if (type_ == 10) {
        painter->drawImage(playerActor(), QImage(FIRE_PIC));
    } else if (type_ == 15) {
        painter->drawImage(playerActor(), QImage(SMOKE_PIC));
    } else {
        painter->drawEllipse(stopRect());
    }
}

void ActorItem::setCoord(int x, int y)
{
    setX( x );
    setY( y );
}

}
