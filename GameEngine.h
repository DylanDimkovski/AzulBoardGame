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
    Player *addPlayer(std::string name, int score, Mosaic* mosaic);
    void addPlayers();

    void fillBag(int argc, char** argv);
    void fillBag(TileList bag);
    void fillLid(TileList lid);
    void fillFactories(Factory* factories[]);

    // Getters
    Factory *getFactory(int);
    Player *getPlayer(int);
    bool isTurn(Player);
    void fillBag(int seed);
    void shuffleBag();
    int getRandomSeed();
    bool isPlayer1Turn();
    std::vector<TileType> getCenterPile();
    TileList getBag();
    TileList getLid();

private:
    void setPlayerTurn();
    std::vector<Player *> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    Player *playerTurnID;
    TileList *bag;
    TileList *lid;
    Menu *menu;
};

#endif