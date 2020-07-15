#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H
#include "baseblock.h"

class SolidBlock: public BaseBlock
{
    Q_OBJECT
public:
    SolidBlock();

    virtual void createBlock(QPointF pos);//create new block, set position and add to scene
};

#endif // SOLIDBLOCK_H
