#ifndef PROGRESBAR_H
#define PROGRESBAR_H

#include <QObject>
#include <QGraphicsRectItem>

//class provide red-green bar visualise ratio of some value np: hp/hp_max
class ProgresBar
{
public:
    ProgresBar(int8_t w, int8_t h, int8_t fill, QPointF pos);

    void setFill(int8_t FILL);
private:
    QGraphicsRectItem *green;
    QGraphicsRectItem *red;

    int8_t height;
    int8_t width;
    int8_t fill;
    QPointF position;

};

#endif // PROGRESBAR_H
