#ifndef PLAYERTANK_H
#define PLAYERTANK_H
#include "basetank.h"
#include <QKeyEvent>

/*tank belong to player*/

class PlayerTank: public BaseTank
{
    Q_OBJECT
public:
    PlayerTank(QGraphicsItem * parent =0);

    void hpBarMod();
    void takeDamage(int8_t damage) override;
signals:
    void yourDead(); //emited when hp=<0
public slots:
    virtual void loadGun() override;
    virtual void setPmap() override;
    //virtual void load
};

#endif // PLAYERTANK_H
