#include "GameEngine.h"

#include <iostream>
#include <algorithm>
#include <random>

GameEngine::GameEngine(Menu *menu) : players(),
                                     factories(),
                                     centerPile(),
                                     bag(new TileList()),
                                     lid(new TileList()),
                                     menu(menu)
{

    centerPile.push_back(FIRSTPLAYER);

    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        TileType temp[4] = {NOTILE, NOTILE, NOTILE, NOTILE};
        factories[i] = new Factory(temp);
    }
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        delete factories[i];
    }
    delete bag;
    delete lid;
}

void GameEngine::playGame(char const *argv)
{
    addPlayers();
    fillBag(argv[0]);
    playerTurnID = players[0];
    playGame();
}

void GameEngine::playGame()
{
    int roundsPlayed = 0;
    while (!hasPlayerWon())
    {
        playRound();
        ++roundsPlayed;
    }
}

void GameEngine::playRound()
{
    if (factoriesAreEmpty())
    {
        for (int i = 0; i < NUM_FACTORIES; i++)
        {
            TileType temp[4] = {NOTILE, NOTILE, NOTILE, NOTILE};

            for (int j = 0; j < FACTORY_SIZE; j++)
            {
                temp[j] = bag->removeFront();
            }

            factories[i]->fill(temp);
        }
    }

    while (!roundOver())
    {
        menu->printMessage("=== Start Round ===");
        menu->handStart(playerTurnID->getName());
        menu->printFactory(&centerPile);
        for (int i = 0; i < NUM_FACTORIES; i++)
        {
            menu->printFactory(i + 1, factories[i]->toString());
        }
        menu->printMosaic(playerTurnID);

        bool inputDone = false;
        do
        {
            std::stringstream ss(menu->getInput());

            string command;

            ss >> command;

            if (command == "turn")
            {
                int factoryNum;
                char colour;
                int lineNum;

                ss >> factoryNum >> colour >> lineNum;
                TileType tileType = charToTileType(colour);
                --lineNum;

                if (factoryNum == 0)
                {
                    if (containsFirstPlayer())
                    {
                        playerTurnID->getMosaic()->getBrokenTiles()->addFront(FIRSTPLAYER);
                    }
                    playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, drawFromCenter(tileType), tileType);
                }
                else
                {
                    --factoryNum;

                    playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, factories[factoryNum]->draw(tileType), tileType);
                    for (int i = 0; i < FACTORY_SIZE; i++)
                    {
                        for (TileType tile : factories[factoryNum]->empty())
                        {
                            centerPile.push_back(tile);
                        }
                    }
                }
                setPlayerTurn();
                inputDone = true;
                menu->printMessage("Turn successful.");
            }
            else
            {
                menu->printMessage("Invalid input, try again");
            }
        } while (!inputDone);
    }

    //Distribute tiles to walls
    menu->printMessage("=== END OF ROUND ===");
    for (auto player : players)
    {
        for (TileType tile : player->calcScore())
        {
            lid->addBack(tile);
        }
        menu->printMosaic(player);
        menu->printScore(player->getName(), player->getScore());
    }
}

bool GameEngine::roundOver()
{
    // centerPile.empty() && factoriesAreEmpty(); equivalent but less efficient
    return !(!centerPile.empty() || !factoriesAreEmpty());
}

// returns true if factories are empty
bool GameEngine::factoriesAreEmpty()
{
    bool factoriesEmpty = true;
    int factoryIndex = 0;
    while (factoriesEmpty && factoryIndex < NUM_FACTORIES)
    {
        factoriesEmpty &= factories[factoryIndex++]->isEmpty();
    }
    return factoriesEmpty;
}

void GameEngine::setPlayerTurn(int playerIndex)
{
    playerTurnID = players[playerIndex];
}

void GameEngine::setPlayerTurn()
{
    if (players[0] == playerTurnID)
    {
        playerTurnID = players[1];
    }
    else
    {
        playerTurnID = players[0];
    }
}

Factory *GameEngine::getFactory(int position)
{
    return factories[position];
}

void GameEngine::fillBag(int seed)
{
    //Create both a bag and shuffle vector
    TileType tileTypes[5] = {BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED};
    TileType temp[100];

    //Store all tiles in temp bag SORTED
    for (int i = 0; i < 100; i++)
    {
        temp[i] = tileTypes[i / 20];
    }

    //Shuffle temp bag
    std::shuffle(std::begin(temp), std::end(temp), std::default_random_engine(seed));

    //Store shuffled tiles into the game bag
    for (int i = 0; i < 100; i++)
    {
        bag->addBack(temp[i]);
    }
}

int GameEngine::drawFromCenter(TileType colour)
{
    int count = 0;
    int pos = 0;
    for (TileType tile : centerPile)
    {
        if (tile == colour)
        {
            count++;
            centerPile.erase(centerPile.begin() + pos);
        }
        else
        {
            pos++;
        }
    }
    return count;
}

bool GameEngine::containsFirstPlayer()
{
    bool contains = false;
    if (centerPile[0] == FIRSTPLAYER)
    {
        centerPile.erase(centerPile.begin());
        contains = true;
    }
    return contains;
}

void GameEngine::fillBag(TileList *bag)
{
    this->bag = bag;
}

void GameEngine::fillLid(TileList *lid)
{
    this->lid = lid;
}

void GameEngine::fillCenterPile(std::vector<TileType> centerPile)
{
    this->centerPile = centerPile;
}

void GameEngine::fillFactories(Factory *factories[])
{
    for (int i = 0; i < FACTORY_SIZE; ++i)
    {
        this->factories[i] = factories[i];
    }
}

Player *GameEngine::addPlayer(string name)
{
    //creates a new player
    return addPlayer(name, 0, new Mosaic());
}

Player *GameEngine::addPlayer(std::string name, int score, Mosaic *mosaic)
{
    players.push_back(new Player(name, score, mosaic));
    return players.back();
}

void GameEngine::addPlayers()
{
    //Checks for player names and adds them to player vector

    menu->printMessage("Enter the name for player 1:");
    string name1 = menu->getInput();
    menu->printMessage("Enter the name for player 2:");
    string name2 = menu->getInput();

    addPlayer(name1);
    addPlayer(name2);

    menu->printMessage("Let's Play!");
}

std::vector<TileType> GameEngine::getCenterPile()
{
    return centerPile;
}

TileList *GameEngine::getBag()
{
    return bag;
}

TileList *GameEngine::getLid()
{
    return lid;
}

Player *GameEngine::getPlayerTurnID()
{
    return playerTurnID;
}

Player *GameEngine::getPlayer(int playerIndex)
{
    return players.at(playerIndex);
}

bool GameEngine::hasPlayerWon()
{
    bool playerWon = false;
    unsigned int playerIndex = 0;
    while (!playerWon && playerIndex < players.size())
        playerWon = players.at(playerIndex++)->hasWon();
    return playerWon;
}
