#include "superbullet.h"
#include <QGraphicsScene>
#include <QTimer>
#include "game.h"
#include <QDebug>
#include <QGraphicsRectItem>
#include "boom.h"

extern Game * game;

SuperBullet::SuperBullet():
    BaseBullet(52, 10, 30, 50, 10)//int8_t id, int8_t DAMAGE, int8_t SPEED, int8_t RANGE, int8_t reloadTime
{
    setRect(0, 0, 3, 7);
    setBrush(Qt::red);
}

void SuperBullet::shot(QPointF coord, qreal angle)
{
    SuperBullet * bullet = new SuperBullet();
    bullet->setPos(coord);
    bullet->setRotation(angle);

    QTimer *tim = new QTimer();
    connect(tim, &QTimer::timeout, bullet, &NormalBullet::move);
    tim->start(100);

    game->scene->addItem(bullet);
}

void SuperBullet::kaboom(QPointF pos)
{

    Boom *boom = new Boom(pos, getDamage());
    game->scene->addItem(boom);

}
