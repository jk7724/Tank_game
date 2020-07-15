#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
///#include <QGraphicsItem>
//#include <QGraphisItemp>
class GameObject: public QObject
{
    Q_OBJECT
public:
    GameObject(int8_t id);
    int8_t getID() const{return ID;};

    //virtual void posAdd(qreal x, qreal y)=0; //set position and add to scene
    //virtual void setPos(qreal angle)=0;
protected:
    int8_t ID;
};

#endif // GAMEOBJECT_H
