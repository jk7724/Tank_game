#ifndef CONCRETEBLOCK_H
#define CONCRETEBLOCK_H
#include "baseblock.h"

class ConcreteBlock: public BaseBlock
{
public:
    ConcreteBlock();

    virtual void createBlock(QPointF pos) override; //create new block, set position and add to scene
    virtual void takeDamage(int8_t damage) override; //switch QPixmap acording to hp
};

#endif // CONCRETEBLOCK_H
