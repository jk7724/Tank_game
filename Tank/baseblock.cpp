#include "baseblock.h"
#include "game.h"
#include <QDebug>

extern Game * game;

BaseBlock::BaseBlock(int8_t id, int8_t HP_M, int8_t HP, bool DESTR):
    ID(id), hp_max(HP_M), hp(HP), destructable(DESTR)
{

}

void BaseBlock::remove()
{
    scene()->removeItem(this);
    delete this;
}

void BaseBlock::takeDamage(int8_t damage)
{
    if(destructable)
    {
        hp -=damage;
        if(hp<=0) remove();
    }
}

