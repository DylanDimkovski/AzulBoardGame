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
    void playGame();
    void playRound();
    void addPlayer(string name);
    Factory *getFactory(int);
    Player *getPlayer(int);
    bool isTurn(Player);
    void fillBag();

private:
    std::vector<Player> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    string playerTurnID;
    TileList bag;
    TileList lid;
};