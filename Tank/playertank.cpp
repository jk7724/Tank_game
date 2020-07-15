#include "playertank.h"
#include <QDebug>
#include "normalbullet.h"
#include <QGraphicsScene>
#include "game.h"
#include <QTimer>

extern Game *game;

PlayerTank::PlayerTank(QGraphicsItem *parent):
    BaseTank(1, 100, 100, 10, QPointF(20,25)) //int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint
{
   setPixmap(QPixmap(":/images/images/yourtank.png"));
   setTransformOriginPoint(getWidth()/2, getHeight()/2);
}

void PlayerTank::hpBarMod()
{
    auto p = (hp*100)/hpMax;
    game->setHpBar(p);

}

void PlayerTank::takeDamage(int8_t damage)
{
    hp-=damage;
    hpBarMod();
    if(hp<=0)
    {
        emit yourDead();
        scene()->removeItem(this);
        return;
    }
    setPixmap((QPixmap(":/images/images/enemytankhit.png")));
    BaseTank::takeDamage(damage);
}

void PlayerTank::loadGun()
{
    static int8_t i = 0;
    game->setReloadBar(i*10);
    if(i>=9)
    {
        game->setReloadBar(100);
        i=0;
        loaded = true;
        delete sender();
        return;
    }
    i++;
}

void PlayerTank::setPmap()
{
    setPixmap(QPixmap(":/images/images/yourtank.png"));
}
