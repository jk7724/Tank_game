#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "playertank.h"
#include <QObject>
#include <QKeyEvent>
#include "gameobject.h"
#include "blockfactory.h"
#include "progresbar.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QGraphicsView *parent = nullptr);
    void keyPressEvent(QKeyEvent *event) override;
    void menuDisplay(); //display main menu of the game
    void createMap(); //create game map base on *map
    void controlDisplay(); //display control window
    int16_t getMapHeight() const {return mapHeight;};
    int16_t getMapWidth() const {return mapWidth;};
    QGraphicsScene* getScene(){return scene;}; //delete
    void reloadBarTim();
    void setReloadBar(int8_t fill); //actualise reload bar(after player shot)
    void setHpBar(int8_t fill); //actualise player hp
    void setWeaponText(const QString text);
    void scoreMod(int p); //actualise score

    QGraphicsScene *scene;
    PlayerTank *player;
public slots:
    void start();
    void gameOver();
private:
    BlockFactory *blockFactory;
    ProgresBar *reload;
    ProgresBar *hpBar;
    QGraphicsTextItem* weaponText;
    int score;
    QGraphicsTextItem* scoreText;

    QVector<QVector<int8_t>> *map; //store ID of game stuff
    const int16_t mapHeight = 900;
    const int16_t mapWidth = 1200;

    void addEnemy(); //add enemy tank to game map
    void addGameObject(int8_t ID, int8_t column, int8_t row);
    void createBlockFactory();
};
#endif // GAME_H
