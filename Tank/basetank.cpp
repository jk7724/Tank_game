#include "basetank.h"
#include "dirtblock.h"
#include "solidblock.h"
#include "normalbullet.h"
#include "superbullet.h"
#include "concreteblock.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QTimer>
#include "game.h"

extern Game *game;
BaseTank::BaseTank(int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF GUNPOINT):
    ID(id), hpMax(HPMAX), hp(HP), speed(SPEED), gunPoint(GUNPOINT)
{
    bullet = nullptr;
    loaded = true;
}

void BaseTank::move(Qt::Key dir)
{
    QPointF temp = pos();
    switch(dir)
    {
    case Qt::Key_W:
    setPos(x(), y()-speed);
    break;
    case Qt::Key_S:
    setPos(x(), y()+speed);
    break;
    case Qt::Key_A:
    setPos(x()-speed, y());
    break;
    case Qt::Key_D:
    setPos(x()+speed, y());
    break;
    default:
    break;
    }


    if(collisionTest())
    {
        setPos(temp);
    }
}

void BaseTank::takeDamage(int8_t damage)
{

    if(hp>0)
    {
        QTimer *tim = new QTimer(this);
        connect(tim, &QTimer::timeout, this, &BaseTank::setPmap);
        tim->setSingleShot(true);
        tim->start(200);
    }

}

void BaseTank::fire()
{
    if(loaded)
    {
        loaded = false;
        auto angle = this->rotation();
        if(angle==0) //move bullet acording to angle. Add or subtrack 30 to place bullet outside tank.
        {
             bullet->shot(pos()+gunPoint+QPointF(0, -30), angle);
        }
        else if(angle==180)
        {
             bullet->shot(pos()+gunPoint+QPointF(0, 30), angle);
        }
        else if(angle==90)
        {
            bullet->shot(pos()+gunPoint+QPointF (30, 0), angle);
        }
        else if(angle==-90)
        {
            bullet->shot(pos()+gunPoint+QPointF (-30, 0), angle);
        }


        QTimer *tim = new QTimer(this);

        connect(tim, &QTimer::timeout, this, &BaseTank::loadGun);
        tim->start(bullet->getReloadTime() * 10); //tim timeout 10 times and delete
    }

}

void BaseTank::reload(Qt::Key key)
{
    if(bullet == nullptr)
    {
        delete bullet;
        bullet = nullptr;
    }
    switch (key)
    {
    case Qt::Key_1: //load normal bullet
        bullet = new NormalBullet;
    break;
    case Qt::Key_2: //load superbullet
        bullet = new SuperBullet;
    break;
    default:
    break;
    }

}

void BaseTank::loadGun()
{
    static int8_t i = 0;
        if(i>=9)
        {
            i=0;
            loaded = true;
            delete sender();
            return;
        }
        i++;

}

bool BaseTank::collisionTest()
{
    QList<QGraphicsItem*> colliding_items = this->collidingItems();
    bool flag = false;
    std::for_each(colliding_items.begin(),colliding_items.end(), [&flag](auto i){

        if(dynamic_cast<BaseBlock*>(i) != nullptr) flag = true;
        else if(dynamic_cast<PlayerTank*>(i) != nullptr) flag = true;
        else if(dynamic_cast<BaseTank*>(i) != nullptr) flag = true;
    });
    if(flag)
    {
        return true;
    }
    return false;

}
