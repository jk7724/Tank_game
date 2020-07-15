#include "game.h"
#include <QApplication>
#include "enemytank.h"

Game *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->menuDisplay();
    return a.exec();
}
