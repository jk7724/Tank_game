#ifndef BASEBULLET_H
#define BASEBULLET_H

#include <QGraphicsRectItem>
#include <QObject>
#include "basetank.h"

/*Base class to normalbullet and superbullet class*/

class GameObject;

class BaseBullet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    virtual void shot(QPointF coord, qreal angle)=0; //create new bullet, make it move
    virtual void kaboom(QPointF pos){}; //make effect when bullet hit target
    int8_t getDamage() const {return damage;};
    int8_t getSpeed() const {return speed;};
    int8_t getReloadTime() const {return reloadTime;};

    bool collisionTest(); //testing if bullet reach any object and generate proper effect

public slots:
    void move(); //make bullet move and check collision (collisionTest())

protected:
    BaseBullet(int8_t id, int8_t DAMAGE, int8_t SPEED, int8_t RANGE, int8_t RTime);
    int8_t ID;
    int8_t damage;
    int8_t speed;
    int8_t range;
    int8_t reloadTime;

};

#endif // BASEBULLET_H
