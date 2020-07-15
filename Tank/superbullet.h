#ifndef SUPERBULLET_H
#define SUPERBULLET_H
#include "basebullet.h"

class SuperBullet: public BaseBullet
{
    Q_OBJECT
public:
    SuperBullet();
    virtual void shot(QPointF coord, qreal angle) override;
    virtual void kaboom(QPointF pos) override; //make kaboom. pos is center of block colliding with bullet
private:

};

#endif // SUPERBULLET_H
