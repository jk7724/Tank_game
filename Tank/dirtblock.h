#ifndef DIRTBLOCK_H
#define DIRTBLOCK_H
#include "baseblock.h"

class DirtBlock: public BaseBlock
{
    Q_OBJECT
public:
    DirtBlock();

    virtual void createBlock(QPointF pos);//create new block, set position and add to scene
};

#endif // DIRTBLOCK_H
