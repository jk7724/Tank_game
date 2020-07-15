#include "sbenemytank.h"

SBEnemyTank::SBEnemyTank(QGraphicsItem *parent):
    EnemyTank(3, 50, 50, 15, QPointF(20,25), 20)//int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint, points
{
    //set SuperBullet
    reload(Qt::Key_2);

    setPixmap(QPixmap(":/images/images/SBtank.png"));

}

void SBEnemyTank::setPmap()
{
    setPixmap(QPixmap(":/images/images/SBtank.png"));
}
