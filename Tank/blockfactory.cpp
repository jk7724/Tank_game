#include "blockfactory.h"
#include "game.h"

extern Game * game;
BlockFactory::BlockFactory(std::vector<BaseBlock*> BL):
    blockList(BL)
{

}

void BlockFactory::createBlock(int8_t ID, QPointF pos)
{
    //first block have ID=21 (another 22, 23...). This block is stored in blockList on 0.
    blockList[ID-21]->createBlock(pos);
}


