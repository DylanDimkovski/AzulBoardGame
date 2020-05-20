#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Factory.h"
#include "Player.h"
#include "TileList.h"
#include "Menu.h"
#include "Utils.h"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;

class GameEngine
{
public:
    GameEngine(Menu *menu);
    ~GameEngine();
    void playGame(char const *argv);
    void playGame();
    void playRound();
    Player *addPlayer(string name);
    Player *addPlayer(std::string name, int score, Mosaic *mosaic);
    void addPlayers();

    void fillBag(int argc, char **argv);
    void fillBag(TileList *bag);
    void fillLid(TileList *lid);
    void fillCenterPile(std::vector<TileType> centerPile);
    void fillFactories(Factory *factories[]);
    void setPlayerTurn(int playerIndex);

    // Getters
    Factory *getFactory(int);
    Player *getPlayer(int playerIndex);
    bool isTurn(Player);
    void fillBag(int seed);
    void shuffleBag();
    bool isPlayer1Turn();
    std::vector<TileType> getCenterPile();
    TileList *getBag();
    TileList *getLid();
    Player *getPlayerTurnID();

private:
    void changePlayerTurn();
    bool hasPlayerWon();
    int drawFromCenter(TileType colour);
    bool containsFirstPlayer();
    bool roundOver();
    bool factoriesAreEmpty();
    bool centerPileContains(TileType tileType);
    bool validLineNum(int lineNum);
    bool validFactoryNum(int factoryNum);

    std::vector<Player *> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    Player *playerTurnID;
    TileList *bag;
    TileList *lid;
    Menu *menu;
};

#endif