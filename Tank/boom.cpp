#include "boom.h"
#include <QGraphicsScene>
#include <QTimer>
#include "baseblock.h"
#include <QDebug>
#include <type_traits>
#include "dirtblock.h"
#include "solidblock.h"
#include "concreteblock.h"
#include "playertank.h"
#include "enemytank.h"

Boom::Boom(QPointF pos, int8_t DAMAGE):
    damage(DAMAGE)
{

    //draw the polygon
    QVector<QPointF> hexPoints;
    hexPoints <<QPointF(2,0)<<QPointF(3,0)<<QPointF(3,2)<<QPointF(5,2)
             <<QPointF(5,3)<<QPointF(3,3)<<QPointF(3,5)<<QPointF(2,5)
            <<QPointF(2,3)<<QPointF(0,3)<<QPointF(0,2)<<QPointF(2,2);

    //scaling
    int scale_by = 30;
    for(auto &i : hexPoints){
        i *=scale_by;
    }

    //QPolygonF(hexPoints);
    QPolygonF cross(hexPoints);
    //this
    setPolygon(cross);
    setBrush(QPixmap(":/images/images/boom.png"));
    setPen(Qt::NoPen);
    setPos(pos);

    QTimer *tim = new QTimer(this);
    connect(tim, &QTimer::timeout, this, &Boom::remove);
    tim->start(300);

}

void Boom::remove()
{

    this->collision();
    scene()->removeItem(this);

    delete this;
}

void Boom::collision()
{
    QList<QGraphicsItem*> colliding_item = this->collidingItems();

    std::for_each(colliding_item.begin(),colliding_item.end(), [this](auto i){ //get all coliding_item, compare Boom damage to target hp, delete bullet

        if(dynamic_cast<BaseBlock*>(i) != nullptr)
        {
           dynamic_cast<BaseBlock*>(i)->takeDamage(damage);
        }
        else if(dynamic_cast<EnemyTank*>(i) != nullptr)
        {
            dynamic_cast<EnemyTank*>(i)->takeDamage(damage);

        }
        else if(dynamic_cast<PlayerTank*>(i) != nullptr)
        {
            dynamic_cast<PlayerTank*>(i)->takeDamage(damage);

        }
    } );


}
