#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <QGraphicsRectItem>
#include<QObject>

/*Base class to dirtblock, solidblock, concreteblock class. Block is a 60x60 square of which it is built game map */

class GameObject;

class BaseBlock: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    void remove(); //remove from scene, delete item
    virtual void takeDamage(int8_t damage); //subtract damage from hp. If hp is =>0, remove object
    virtual void createBlock(QPointF pos)=0; //create new block, set position and add to scene.
    static int8_t getSize(){return size;};
    bool ifDestructable() const {return destructable;};
protected:
    BaseBlock(int8_t id, int8_t HP_M, int8_t HP, bool DESTR);

    int8_t ID;
    static int8_t size;
    int8_t hp_max;
    int8_t hp;
    bool destructable;

};

#endif // BASEBLOCK_H
