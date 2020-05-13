#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Factory.h"
#include "Player.h"
#include "TileList.h"
#include "Menu.h"

#include <string>
#include <vector>

using std::string;

class GameEngine
{
public:
    GameEngine(Menu *menu);
    ~GameEngine();
    void playGame(char const *argv);
    void playRound();
    Player *addPlayer(string name);
    void addPlayers();
    Factory *getFactory(int);
    Player *getPlayer(int);
    bool isTurn(Player);
    void fillBag(int seed);
    void shuffleBag();

private:
    std::vector<Player *> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    Player *playerTurnID;
    TileList *bag;
    TileList *lid;
    Menu *menu;
};

#endif