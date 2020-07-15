#include "game.h"
#include <QDebug>
#include "dirtblock.h"
#include "solidblock.h"
#include "normalbullet.h"
#include <QTimer>
#include "gameobject.h"
#include "baseblock.h"
#include "blockfactory.h"
#include "concreteblock.h"
#include "enemytank.h"
#include "sbenemytank.h"
#include "button.h"
#include <QGraphicsRectItem>

int8_t BaseBlock::size = 60;

Game::Game(QGraphicsView *parent)
    : QGraphicsView(parent)
{
    score = 0;
    //set scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, getMapWidth(), getMapHeight()+30);
    setFixedSize(getMapWidth(), getMapHeight()+30);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


}
void Game::keyPressEvent(QKeyEvent *event)
{
    static int t = 100;
    switch (event->key() )
    {
    case Qt::Key_1: //set weapon to normal bullet
        player->reload(Qt::Key_1 );
        setWeaponText("Weapon: Normal Bullet");
    break;
    case Qt::Key_2: //set weapon to super bullet
        player->reload(Qt::Key_2);
        setWeaponText("Weapon: Super Bullet");
    break;
    case Qt::Key_W: //move up
        player->setRotation(0);
        player->move(Qt::Key_W);
    break;
    case Qt::Key_S: //move down
        player->setRotation(180);
        player->move(Qt::Key_S);
    break;
    case Qt::Key_A: //move left
        player->setRotation(-90);
        player->move(Qt::Key_A);
    break;
    case Qt::Key_D: //move right
        player->setRotation(90);
        player->move(Qt::Key_D);
    break;
    case Qt::Key_Space: //shot
        player->fire();
    break;
    }
}

void Game::menuDisplay()
{
    scene->clear();
    //add game title
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Tank Game"));
    QFont font("times new roman", 50);
    title->setFont(font);
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    int tyPos = 200;
    title->setPos(txPos, tyPos);
    scene->addItem(title);

    //add menu button
    Button* play = new Button(QString("Play"));
    int bxPos = this->width()/2 - play->boundingRect().width()/2;
    int byPos = 315;
    play->setPos(bxPos, byPos);
    connect(play, &Button::clicked, this, &Game::start); //start the game
    scene->addItem(play);

    Button* control = new Button(QString("Control"));
    int cxPos = this->width()/2 - control->boundingRect().width()/2;
    int cyPos = 400;
    control->setPos(cxPos, cyPos);
    connect(control, &Button::clicked, this, &Game::controlDisplay);
    scene->addItem(control);

    Button* quit = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 475;
    quit->setPos(qxPos, qyPos);
    connect(quit, &Button::clicked, this, &Game::close);
    scene->addItem(quit);

}

void Game::createMap()
{

   //example game map. 0 - free space, 22 - solid block, 21 - dirt block, 23 - concrete block
   QVector<QVector<int8_t>> map_template = {
      {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,},
      {22,0 ,0 ,0 ,21,21,21,0 ,0 ,22,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0,22,},
      {22,0 ,0 ,0 ,23,21,22,0 ,22,22 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0, 0,22,},
      {22,0 ,0 ,0 ,23,21,22,21,21,22,23,0 , 0, 0, 22, 0, 0, 0, 0,22,},
      {22,0 ,0 ,0 ,23,21,22, 0, 0,22,23,23,23,23,23,23,23,23,23,22,},
      {22, 0, 0, 0,23,21,22, 0, 0,22,23,23,23,23,23,23,23,23,23,22,},
      {22, 0, 0, 0,23,21,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22,},
      {22,23,23,23,23,21,22, 0,22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,22,},
      {22,23,21,21,21,21,23, 0, 0, 0,22,22,22,22,22,22,22,22,21,22,},
      {22,21,21,21,21,23,22, 0,22, 0,22,21, 0, 0, 0, 0, 0, 0, 0,22,},
      {22,21,21,21,21,22,22, 0,22, 0,22,21,21,22,22,22,22,22,21,22,},
      {22, 0,22,22,22, 0, 0, 0, 0, 0,22,21,22,22,22,22,22,22,21,22,},
      {22, 0,22, 0, 0, 0, 0,22, 0, 0,22,21, 0, 0, 0, 0,21,21,21,22,},
      {22, 0,22, 0, 0, 0, 0, 0, 0, 0,21,21, 0, 0, 0, 0,21,21,21,22,},
      {22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,22,},

   };

   map = new QVector<QVector<int8_t>>(map_template);

   int8_t column = 0;
   int8_t row = 0;
   //create and add to scene block objects according to 'map_template'
   std::for_each(map[0].begin(), map[0].end(), [this, &column, &row](auto i){
       std::for_each(i.begin(), i.end(), [this, &row, &column](auto x){
           if(x>=21 && x<=50){ //block ID range is range: 21-50
               blockFactory->createBlock(x, QPointF(row*60, column*60)); //60 is a block size. createBlock create block object associate to passing ID, add it to scene in right position
           }
           row++;
       });
       column++;
       row=0;
   });


}

void Game::controlDisplay()
{
    scene->clear();

    QGraphicsTextItem* control = new QGraphicsTextItem(QString("Control:"));
    QFont font1("comic sans", 50);
    control->setFont(font1);
    int txPos = this->width()/2 - control->boundingRect().width()/2;
    int tyPos = 70;
    control->setPos(txPos, tyPos);
    scene->addItem(control);

    QFont font2("comic sans", 20);
    QGraphicsTextItem* moveText = new QGraphicsTextItem(QString("Move - W, S, A, D"));
    int mxPos = this->width()/2 - control->boundingRect().width()/2;
    int myPos = 250;
    moveText->setPos(mxPos, myPos);
    moveText->setFont(font2);
    scene->addItem(moveText);

    QGraphicsTextItem* shotText = new QGraphicsTextItem(QString("Shot - SPACEBAR"));
    int sxPos = this->width()/2 - control->boundingRect().width()/2;
    int syPos = 350;
    shotText->setPos(sxPos, syPos);
    shotText->setFont(font2);
    scene->addItem(shotText);

    QGraphicsTextItem* weapon1Text = new QGraphicsTextItem(QString("Normal Bullet - 1"));
    int wxPos = this->width()/2 - control->boundingRect().width()/2;
    int wyPos = 450;
    weapon1Text->setPos(wxPos, wyPos);
    weapon1Text->setFont(font2);
    scene->addItem(weapon1Text);

    QGraphicsTextItem* weapon2Text = new QGraphicsTextItem(QString("Super Bullet - 2"));
    int xxPos = this->width()/2 - control->boundingRect().width()/2;
    int xyPos = 550;
    weapon2Text->setPos(xxPos, xyPos);
    weapon2Text->setFont(font2);
    scene->addItem(weapon2Text);

    //add back button
    Button* backButton = new Button(QString("Back to menu"));
    int bxPos = this->width()/2 - control->boundingRect().width()/2;
    int byPos = 700;
    backButton->setPos(bxPos, byPos);
    connect(backButton, &Button::clicked, this, &Game::menuDisplay);
    scene->addItem(backButton);

}

void Game::reloadBarTim()
{
    setReloadBar(0);
}

void Game::setReloadBar(int8_t fill)
{
    reload->setFill(fill);
}

void Game::setHpBar(int8_t fill)
{
    hpBar->setFill(fill);
}

void Game::setWeaponText(const QString text)
{
    weaponText->setPlainText(text);
}

void Game::scoreMod(int p)
{
    score +=p;
    scoreText->setPlainText(QString("Score: " + QString::number(score)));
    if(score >= 140) //140 is total amount of point for defeat all enemy
    {
        gameOver();
    }
}

void Game::start()
{
    scene->clear();
    score = 0;
    //set Player //QPointF(220,190)
    player = new PlayerTank();
    connect(player, &PlayerTank::yourDead, this, &Game::gameOver);
    player->setPos(70, 770);
    scene->addItem(player);
    player->reload(Qt::Key_1); //gear up normal bullet

    //set reload bar
    reload = new ProgresBar(100, 15, 100, QPointF(90, 910));
    QGraphicsTextItem* reloadText = new QGraphicsTextItem(QString("Reload: "));
    QFont font("Tokyo", 15);
    reloadText->setFont(font);
    reloadText->setPos(10, 900);
    scene->addItem(reloadText);

    //set hp bar
    hpBar = new ProgresBar(100, 15, 100, QPointF(350 ,910));
    QGraphicsTextItem* hpText = new QGraphicsTextItem(QString("HP: "));
    QFont font1("Tokyo", 15);
    hpText->setFont(font1);
    hpText->setPos(300, 900);
    scene->addItem(hpText);

    //set weapon text
    weaponText = new QGraphicsTextItem(QString("Weapon: Normal Bullet"));
    QFont font2("Tokyo", 15);
    weaponText->setFont(font2);
    weaponText->setPos(600, 900);
    scene->addItem(weaponText);

    //set score text
    scoreText = new QGraphicsTextItem(QString("Score: 0"));
    QFont font3("Tokyo", 15);
    scoreText->setFont(font3);
    scoreText->setPos(900, 900);
    scene->addItem(scoreText);

    //create map of block
    createBlockFactory();
    createMap();
    //add Enemy
    addEnemy();
}

void Game::gameOver()
{
    //drawPanel(0,0,1024,768, Qt::black, 0.65);
    QGraphicsRectItem *panel = new QGraphicsRectItem;
    panel->setRect(100,100,1024, 768);
    panel->setOpacity(0.5);
    QBrush brush;
    brush.setColor(Qt::black);
    brush.setStyle(Qt::SolidPattern);
    panel->setBrush(brush);
    scene->addItem(panel);

    //add game title
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Game Over!"));
    QFont titleFont("comic sans", 50);
    title->setFont(titleFont);
    int txPos = this->width()/2 - title->boundingRect().width()/2;
    int tyPos = 350;
    title->setPos(txPos, tyPos);
    scene->addItem(title);

    //add replay button
    Button* replay = new Button(QString("Play again?"));
    int bxPos = this->width()/2 - replay->boundingRect().width()/2;
    int byPos = 465;
    replay->setPos(bxPos, byPos);
    connect(replay, &Button::clicked, this, &Game::start);
    scene->addItem(replay);

    //add quit button
    Button* quit = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quit->boundingRect().width()/2;
    int qyPos = 545;
    quit->setPos(qxPos, qyPos);
    connect(quit, &Button::clicked, this, &Game::close);
    scene->addItem(quit);


}

void Game::addEnemy()
{

    EnemyTank* enemy = new EnemyTank();
    enemy->setPos(QPointF(150, 140));
    scene->addItem(enemy);

    EnemyTank* enemy2 = new EnemyTank();
    enemy2->setPos(QPointF(80, 330));
    scene->addItem(enemy2);

    EnemyTank* enemy3 = new EnemyTank();
    enemy3->setPos(QPointF(420,70));
    scene->addItem(enemy3);

    EnemyTank* enemy5 = new EnemyTank();
    enemy5->setPos(QPointF(690,400));
    scene->addItem(enemy5);

    EnemyTank* enemy6 = new EnemyTank();
    enemy6->setPos(QPointF(1030,400));
    scene->addItem(enemy6);

    SBEnemyTank* SBenemy = new SBEnemyTank();
    SBenemy->setPos(QPointF(430,310));
    scene->addItem(SBenemy);

    EnemyTank* enemy7 = new EnemyTank();
    enemy7->setPos(QPointF(700,110));
    scene->addItem(enemy7);

    EnemyTank* enemy8 = new EnemyTank();
    enemy8->setPos(QPointF(660,110) );
    scene->addItem(enemy8);

    EnemyTank* enemy9 = new EnemyTank();
    enemy9->setPos(QPointF(1040,110));
    scene->addItem(enemy9);

    SBEnemyTank* SBenemy2 = new SBEnemyTank();
    SBenemy2->setPos(QPointF(810,740));
    scene->addItem(SBenemy2);

    SBEnemyTank* SBenemy3 = new SBEnemyTank();
    SBenemy3->setPos(QPointF(870,550));
    scene->addItem(SBenemy3);
}


void Game::createBlockFactory()
{
    std::vector<BaseBlock*> temp; //temp is vector of pointer to all kind of block in game. Base on that vector, BlockFactory create proper block

    DirtBlock *dr = new DirtBlock();
    SolidBlock *sd = new SolidBlock();
    ConcreteBlock *cr = new ConcreteBlock();

    temp.push_back(dr);
    temp.push_back(sd);
    temp.push_back(cr);

    blockFactory = new BlockFactory(temp);
}
