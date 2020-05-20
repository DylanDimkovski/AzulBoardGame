#include "GameEngine.h"

#include "Saver.h"
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
        roundsPlayed++;
    }
}

void GameEngine::playRound()
{
    if (roundOver())
    {
        centerPile.push_back(FIRSTPLAYER);
        for (int i = 0; i < NUM_FACTORIES; i++)
        {
            TileType temp[4] = {NOTILE, NOTILE, NOTILE, NOTILE};

            for (int j = 0; j < FACTORY_SIZE; j++)
            {
                if (bag->size() == 0)
                {
                    TileList *tmp = bag;
                    bag = lid;
                    lid = tmp;
                    tmp = nullptr;
                    delete tmp;
                }

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
                unsigned int factoryNum, lineNum;
                char colour;

                ss >> factoryNum >> colour >> lineNum;
                TileType tileType = charToTileType(colour);
                --lineNum;

                if (validLineNum(lineNum) && validFactoryNum(factoryNum))
                {
                    if (factoryNum == 0)
                    {
                        if (!centerPile.empty() && centerPileContains(tileType))
                        {
                            if (playerTurnID->getMosaic()->getLine(lineNum)->getTileType() == NOTILE ||
                                playerTurnID->getMosaic()->getLine(lineNum)->getTileType() == tileType)
                            {
                                if (containsFirstPlayer())
                                {
                                    playerTurnID->getMosaic()->getBrokenTiles()->addFront(FIRSTPLAYER);
                                }
                                playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, drawFromCenter(tileType), tileType);
                                inputDone = true;
                            }
                        }
                    }
                    else
                    {
                        --factoryNum;
                        if (!factories[factoryNum]->isEmpty() && factories[factoryNum]->contains(tileType))
                        {
                            if (playerTurnID->getMosaic()->getLine(lineNum)->canAddTiles(tileType))
                            {
                                playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, factories[factoryNum]->draw(tileType), tileType);

                                for (TileType tile : factories[factoryNum]->empty())
                                {
                                    centerPile.push_back(tile);
                                }

                                inputDone = true;
                            }
                        }
                    }

                    if (inputDone)
                    {
                        changePlayerTurn();
                        menu->printMessage("Turn successful.");
                    }
                }
            }
            else if (command == "save")
            {
                std::string fileName;
                if (ss.good())
                {
                    ss >> fileName;
                    // save file
                    Saver saver;
                    saver.save(this, fileName);
                    inputDone = true;
                }

                if (inputDone)
                    menu->printMessage("Game successfully saved to '" + fileName + "'");
            }
            if (!inputDone)
                menu->printMessage("Invalid input, try again");
        } while (!inputDone);
    }

    //Distribute tiles to walls
    menu->printMessage("=== END OF ROUND ===");

    for (auto player : players)
    {
        if (player->hasFirstPlayer())
        {
            playerTurnID = player;
        }

        for (TileType tile : player->calcScore())
        {
            lid->addBack(tile);
        }
        menu->printScore(player->getName(), player->getScore());
    }
}

bool GameEngine::validLineNum(int lineNum)
{
    return lineNum >= 0 && lineNum < NUMBER_OF_LINES;
}

bool GameEngine::validFactoryNum(int factoryNum)
{
    return factoryNum >= 0 && factoryNum <= NUM_FACTORIES;
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

void GameEngine::changePlayerTurn()
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

    std::vector<TileType>::reverse_iterator itr;
    {
        for (itr = centerPile.rbegin(); itr < centerPile.rend(); itr++)
        {
            int index = std::distance(begin(centerPile), itr.base()) - 1;
            if (centerPile[index] == colour)
            {
                count++;
                centerPile.erase(centerPile.begin() + index);
                itr++;
            }
        }
        return count;
    }
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
    for (int i = 0; i < NUM_FACTORIES; ++i)
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

bool GameEngine::centerPileContains(TileType tileType)
{
    bool centerPileContainsTile = false;
    unsigned int index = 0;
    while (!centerPileContainsTile && index < centerPile.size())
    {
        centerPileContainsTile = centerPile[index] == tileType;
        index++;
    }
    return centerPileContainsTile;
}
