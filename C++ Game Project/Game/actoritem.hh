#ifndef ACTORITEM_HH
#define ACTORITEM_HH


#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

namespace StudentSide {

const int WIDTH = 15;
const int HEIGHT = 15;
const QString PLANE_PIC = ":/photos/plane.png";
const QString AIRPLANE_PIC = ":/photos/airplane.png";
const QString COPTER_PIC = ":/photos/copter.png";
const QString FIRE_PIC = ":/photos/fire.png";
const QString BUS_PIC = ":/photos/bus.png";
const QString SMOKE_PIC = ":/photos/smoke.png";

class ActorItem : public QGraphicsItem
{
public:
    ActorItem(int x, int y, int type = 0);
    virtual ~ActorItem();
    QRectF boundingRect() const;
    QRectF stopRect() const;
    QRectF passengerActor() const;
    QRectF playerActor() const;
    // params option and widget are unused in the method
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setCoord(int x, int y);

private:

    int x_;
    int y_;
    int type_;


};

}
#endif // ACTORITEM_HH
