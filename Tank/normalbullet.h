#ifndef NORMALBULLET_H
#define NORMALBULLET_H
#include "basebullet.h"

class NormalBullet: public BaseBullet
{
    Q_OBJECT
public:
    NormalBullet();
    virtual void shot(QPointF coord, qreal angle) override;

};

#endif // NORMALBULLET_H
