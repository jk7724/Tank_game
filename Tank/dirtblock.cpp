#include "dirtblock.h"
#include <QGraphicsScene>
#include "game.h"

extern Game *game;

DirtBlock::DirtBlock():
    BaseBlock(21, 10, 10, true)//int8_t id, int8_t HP_M, int8_t HP, bool DESTR
{
    setRect(0, 0, getSize(), getSize());
    setBrush(QPixmap(":/images/images/dirtblock.png"));
}

void DirtBlock::createBlock(QPointF pos)
{
    DirtBlock *block = new DirtBlock();
    block->setPos(pos);
    game->scene->addItem(block);


}
