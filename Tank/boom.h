#ifndef BOOM_H
#define BOOM_H
#include <QGraphicsPolygonItem>
#include <QObject>

/*Effect of reach target by superbullet*/

class Boom: public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    Boom(QPointF pos, int8_t DAMAGE); //w_v, h_v -> VerticalBoom (VBoom) width and height
public slots:
    void remove(); //remove from scene and delete
private:
    QGraphicsRectItem *HBoom;
    QGraphicsRectItem *VBoom;

    int8_t damage;

    void collision(); //deal with object colliding with Boom
};

#endif // BOOM_H
