#include <string>
#include "Factory.h"
#include "Player.h"
#include <vector>

using std::string;

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();
    void playGame();
    void playRound();
    Factory *getFactory(int);
    Player *getPlayer(int);
    bool isTurn(Player);

private:
    std::vector<Player> players;
    Factory *factories[NUM_FACTORIES];
    std::vector<TileType> centerPile;
    string playerTurnID;
};