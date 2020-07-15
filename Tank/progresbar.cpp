#include "progresbar.h"
#include "game.h"

extern Game * game;
ProgresBar::ProgresBar(int8_t w, int8_t h, int8_t f, QPointF pos):
     height(h), width(w), fill(f), position(pos)
{
    green = new QGraphicsRectItem(pos.rx(), pos.ry(), w, h);
    red = new QGraphicsRectItem();

    green->setBrush(Qt::green);
    red->setBrush(Qt::red);

    game->scene->addItem(green);
    game->scene->addItem(red);

}

void ProgresBar::setFill(int8_t FILL)
{
    fill = FILL;
    float greenW;

    greenW = static_cast<float>(width) * (static_cast<float>(FILL)/static_cast<float>(100));

    delete green;
    delete red;
    game->scene->removeItem(green);
    game->scene->removeItem(red);

    green = new QGraphicsRectItem(position.rx(), position.ry(), greenW, height);
    red = new QGraphicsRectItem(position.rx() + greenW , position.ry(), width-greenW, height);
    green->setBrush(Qt::green);
    red->setBrush(Qt::red);

    game->scene->addItem(green);
    game->scene->addItem(red);

    //calculate new green width

}
