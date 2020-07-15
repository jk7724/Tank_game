#include "normalbullet.h"
#include "game.h"
#include <QTimer>
#include "dirtblock.h"
#include <QGraphicsScene>

extern Game * game;

NormalBullet::NormalBullet():
    BaseBullet(51, 10, 30, 50, 5)//int8_t id, int8_t DAMAGE, int8_t SPEED, int8_t RANGE, int8_t reloadTime
{
    setRect(0, 0, 3, 7);
    setBrush(Qt::black);
}

void NormalBullet::shot(QPointF coord, qreal angle)
{
    //create new bullet, setPos, add to scene and connect to timer
    NormalBullet * bullet = new NormalBullet();
    bullet->setPos(coord);
    bullet->setRotation(angle);

    QTimer *tim = new QTimer();
    connect(tim, &QTimer::timeout, bullet, &NormalBullet::move);
    tim->start(100);
    game->scene->addItem(bullet);
}


