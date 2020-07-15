#ifndef SBENEMYTANK_H
#define SBENEMYTANK_H

#include "enemytank.h"

class SBEnemyTank: public EnemyTank
{
public:
    SBEnemyTank(QGraphicsItem * parent =0);
public slots:
    virtual void setPmap();
};

#endif // SBENEMYTANK_H
