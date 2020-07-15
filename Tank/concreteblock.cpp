#include "concreteblock.h"
#include <QGraphicsScene>
#include "game.h"

extern Game *game;

ConcreteBlock::ConcreteBlock():
    BaseBlock(23, 20, 20, true)//int8_t id, int8_t HP_M, int8_t HP, bool DESTR
{
    setRect(0, 0, getSize(), getSize());
    setBrush(QPixmap(":/images/images/ConcreteBlock.png"));
}

void ConcreteBlock::createBlock(QPointF pos)
{
    ConcreteBlock *block = new ConcreteBlock();
    block->setPos(pos);
    game->scene->addItem(block);
}

void ConcreteBlock::takeDamage(int8_t damage)
{
    BaseBlock::takeDamage(damage);

    if(hp<=10){
        setBrush(QPixmap(":/images/images/brokenConcreteBlock.png"));
    }
}
