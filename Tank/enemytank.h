#ifndef ENEMYTANK_H
#define ENEMYTANK_H

#include "basetank.h"
#include <QKeyEvent>
#include <QTimer>
#include <random>
#include <QDebug>

class EnemyTank: public BaseTank
{
    Q_OBJECT
public:
    //int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint
    EnemyTank(int8_t id = 2, int8_t HPMAX = 30, int8_t HP = 30, int8_t SPEED = 10, QPointF gunPoint = QPointF(20,25), int Points = 10);
    void choseDest(); //chose random dir and destpoint,
    //getters
    QPointF getDest() const {return destination;}
    Qt::Key getDir() const{return dir;}
    int getPoints() const{return points;}
    //setters
    void setDest(QPointF d){destination = d;}
    void setDir(Qt::Key d);
    bool playerDetect(); //detect player and respond (fire!). return true if detect player
    void takeDamage(int8_t damage) override;
    void moveSlot(); //enemy tank move algoritm
    virtual void setPmap() override;
private:
    void lookAround(); //tank look around to detect player.

    QPointF destination;
    QPointF lastPos;
    Qt::Key dir;
    Qt::Key backDir;
    QTimer *moveTim;
    QPointF temp;
    QGraphicsLineItem *nLine;

    int points;
    bool stop; //stop movement if true;
    bool follow; //if true enemy follow player
    bool lookA; //if true, tank look around

    std::mt19937 rng; //pseudo random engine use to

};

#endif // ENEMYTANK_H
