#include "enemytank.h"
#include "playertank.h"
#include "baseblock.h"
#include <QRandomGenerator>
#include "game.h"

extern Game*game;

EnemyTank::EnemyTank(int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint, int Points):
     BaseTank(id, HPMAX, HP, SPEED, gunPoint), //int8_t id, int8_t HPMAX, int8_t HP, int8_t SPEED, QPointF gunPoint
     rng(std::mt19937(QRandomGenerator::global()->generate())),
     stop(false), follow(false), lookA(false),
     points(Points)
{

    std::uniform_int_distribution<int> u(0,100);

    setPixmap(QPixmap(":/images/images/enemytank.png"));
    setTransformOriginPoint(getWidth()/2, getHeight()/2);

    temp = QPointF(getWidth()/2+300, getHeight()/2);

    //set move Timer
    moveTim = new QTimer();
    moveTim->setInterval(100);
    connect(moveTim, &QTimer::timeout, this, &EnemyTank::moveSlot);
    backDir = Qt::Key_N; //N like null

    //set detection line
    QLineF nL(this->transformOriginPoint(), QPointF(transformOriginPoint().rx(), transformOriginPoint().ry()-500));
    nLine = new QGraphicsLineItem(nL, this);
    nLine->setVisible(false);
    //set bullet
    reload(Qt::Key_1);

    //get tank move
    choseDest();


}

void EnemyTank::choseDest()
{

    std::uniform_int_distribution<int> u(0,3); //draw by lot move direction. 0 -> up, 1->down, 2->Left, 3->Right
    Qt::Key temp;
    bool flag = true;

    //draw by lot direction
    while(flag)
    {
        int d = u(rng);
        switch(d)
        {
        case 0:
            temp = Qt::Key_W;

        break;
        case 1:
            temp = Qt::Key_S;

        break;
        case 2:
            temp = Qt::Key_A;

        break;
        case 3:
            temp = Qt::Key_D;

        break;
        }

        if(backDir != temp) flag = false; //backtrack check
    }

    setDir(temp); //set direction

    //set bacDir to prevent backtrack in next move
    switch(dir)
    {
    case Qt::Key_W:
        backDir = Qt::Key_S;

    break;
    case Qt::Key_S:
         backDir = Qt::Key_W;

    break;
    case Qt::Key_A:
         backDir = Qt::Key_D;

    break;
    case Qt::Key_D:
         backDir = Qt::Key_A;

    break;
    default:
    break;
    }

   //draw by lot lenth from start to destination point
   std::uniform_int_distribution<int> p(100, 500);
   int mod = p(rng);

   //calculate dest point depend on dir
   if(dir == Qt::Key_W || dir == Qt::Key_S)
   {
       destination.setX(pos().rx());

       if(dir == Qt::Key_W)
       {
           destination.setY(pos().ry()-mod);
       }
       else if(dir == Qt::Key_S)
       {
           destination.setY(pos().ry()+mod);
       }

   }
   else if(dir == Qt::Key_A || dir == Qt::Key_D)
   {
       destination.setY(pos().ry());

       if(dir == Qt::Key_A)
       {
           destination.setX(pos().rx()-mod);
       }
       else if(dir == Qt::Key_D)
       {
           destination.setX(pos().rx()+mod);
       }
   }
   moveTim->start();
}

void EnemyTank::setDir(Qt::Key d)
{
    dir = d;

    switch(d)
    {
    case Qt::Key_W:
        this->setRotation(0);

    break;
    case Qt::Key_S:
        this->setRotation(180);

    break;
    case Qt::Key_D:
        this->setRotation(90);
    break;
    case Qt::Key_A:
        this->setRotation(-90);

    break;
    default:
    break;
    }

}

bool EnemyTank::playerDetect()
{
   stop = false; // if enemy tank not detect player again, enemytank start moving
   QList<QGraphicsItem*> colliding_item = nLine->collidingItems();

   int nearest_block_dist = 9998;
   int player_dist = 0;
   QPointF new_dest;

    //get player-enemy distans and nearest enemy-block dist (from gun direction)
    std::for_each(colliding_item.begin(), colliding_item.end(), [this, &nearest_block_dist, &player_dist, &new_dest](auto i){
        if(typeid(*i) == typeid(PlayerTank))
        {
            QLineF line(dynamic_cast<PlayerTank*>(i)->pos(), this->pos());
            player_dist = line.length();
            new_dest = i->pos();

        }
        else if(dynamic_cast<BaseBlock*>(i) != nullptr)
        {
            QLineF line(dynamic_cast<BaseBlock*>(i)->pos(), this->pos());
            if(line.length()<nearest_block_dist) nearest_block_dist = line.length();
        }

    });

        //if player is overlap by a block, enemy not detect player, return false
        if(player_dist !=0 && player_dist<nearest_block_dist)
        {
            this->fire();
            stop = true;
            follow = true;
            destination = new_dest;
            lookA = true;
            return true;

        }
        return false;
}

void EnemyTank::takeDamage(int8_t damage)
{
    hp-=damage;
    if(hp<=0)
    {
            scene()->removeItem(this);
            game->scoreMod(getPoints());
            delete this;
            return;
    }
    setPixmap((QPixmap(":/images/images/hittank.png")));
    BaseTank::takeDamage(damage);

}

void EnemyTank::moveSlot()
{

    if(!stop){
        lastPos = pos();
        move(dir);
    }
    playerDetect(); //sets destination to last player position

    QLineF ln(pos(), destination);
    if(follow)
    {
        follow = false;
        moveTim->start();
    }
    //if tank reach dest point or hit the wall, chose new dest
    else if(ln.length()<30 || (lastPos == pos() && !lookA)) //chose new dest and dir if tank raech dest or tank stack on obsticle
    {
        lookA = false;
        destination = pos();
        moveTim->stop();
        choseDest();//chose new dest point

    }
}

void EnemyTank::setPmap()
{
    setPixmap(QPixmap(":/images/images/enemytank.png"));
}

void EnemyTank::lookAround()
{

    if(this->rotation() == 180 || this->rotation()== 0)
    {

        this->setRotation(-90);
        dir = Qt::Key_A;
        if(playerDetect()) return;
        this->setRotation(90);
        dir = Qt::Key_D;
        if(playerDetect()) return;

    }
    else if(this->rotation() == 90 || this->rotation()== -90)
    {

        this->setRotation(0);
        dir = Qt::Key_W;
        if(playerDetect()) return;
        this->setRotation(180);
        dir = Qt::Key_S;
        if(playerDetect()) return;

    }
}
