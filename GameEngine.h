#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <string>
#include "Factory.h"
#include "Player.h"
#include "TileList.h"
#include <vector>

using std::string;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    // Playing Game Methods
    void playGame();
    void playRound();

    // Adders / Setters
    void addPlayer(string name);
    void addPlayer(string name, int score, Mosaic* mosaic);
    void addPlayers();

    void fillBag(int argc, char** argv);
    void fillBag(TileList bag);
    void fillLid(TileList lid);
    void fillFactories(Factory* factories[]);

    // Getters
    Factory *getFactory(int);
    Player *getPlayer(int);
    bool isTurn(Player);
    void setTurn(string playerName);
    void shuffleBag();
    int getRandomSeed();
    bool isPlayer1Turn();
    std::vector<TileType> getCenterPile();
    TileList getBag();
    TileList getLid();

private:
    void addPlayer(Player player);

    int randomSeed;
    std::vector<Player> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    string playerTurnID;
    TileList bag;
    TileList lid;
};

#endif