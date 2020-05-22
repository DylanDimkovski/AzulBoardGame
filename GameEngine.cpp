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
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        factories[i] = new Factory();
    }
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        if (factories[i] != nullptr)
            delete factories[i];
    }
    if (bag != nullptr)
        delete bag;
    if (lid != nullptr)
        delete lid;
    for (Player *player : players)
        if (player != nullptr)
            delete player;
}

bool GameEngine::playGame(char const *argv)
{
    addPlayers();
    fillBag(argv[0]);
    playerTurnID = players[0];
    return playGame();
}

bool GameEngine::playGame()
{
    bool exit = false;
    while (!exit && !hasPlayerWon())
    {
        exit = playRound();
    }

    if (hasPlayerWon())
    {
        Player *winningPlayer = playerTurnID;
        for (auto player : players)
        {
            if (player->getScore() > winningPlayer->getScore())
            {
                winningPlayer = player;
            }
        }
        menu->gameOver(winningPlayer);
    }
    return exit;
}

bool GameEngine::playRound()
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
    bool exit = false;
    menu->printMessage("=== Start Round ===");
    while (!exit && !roundOver())
    {
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
            if (!std::cin.eof())
            {
                string errorMessage = "Command not recognised";
                string command;

                ss >> command;

                if (command == "turn")
                {
                    errorMessage = "Invalid syntax for turn command";
                    unsigned int factoryNum = NUM_FACTORIES + 1, lineNum = NUMBER_OF_LINES + 1;
                    char colour = '\0';

                    ss >> factoryNum >> colour >> lineNum;
                    TileType tileType = charToTileType(colour);
                    --lineNum;

                    if (validFactoryNum(factoryNum))
                    {
                        if (selectableTile(colour))
                        {
                            if (validLineNum(lineNum))
                            {
                                if (factoryNum == 0)
                                {
                                    if (!centerPile.empty() && centerPileContains(tileType))
                                    {
                                        if (lineNum == 5)
                                        {
                                            playerTurnID->getMosaic()->addToBrokenTiles(drawFromCenter(tileType), tileType);
                                            inputDone = true;
                                        }
                                        else if (!playerTurnID->getMosaic()->isFilled(lineNum, tileType) &&
                                                 playerTurnID->getMosaic()->getLine(lineNum)->canAddTiles(tileType))
                                        {
                                            if (containsFirstPlayer())
                                            {
                                                playerTurnID->getMosaic()->getBrokenTiles()->addFront(FIRSTPLAYER);
                                            }
                                            playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, drawFromCenter(tileType), tileType);
                                            inputDone = true;
                                        }
                                        else
                                            errorMessage = "Specified line cannot add tile";
                                    }
                                    else
                                        errorMessage = "Center pile does not contain specified tile";
                                }
                                else
                                {
                                    --factoryNum;
                                    if (!factories[factoryNum]->isEmpty())
                                    {
                                        if (factories[factoryNum]->contains(tileType))
                                        {
                                            if (lineNum == 5)
                                            {
                                                playerTurnID->getMosaic()->addToBrokenTiles(factories[factoryNum]->draw(tileType), tileType);
                                                for (TileType tile : factories[factoryNum]->empty())
                                                {
                                                    centerPile.push_back(tile);
                                                }
                                                inputDone = true;
                                            }
                                            else if (!playerTurnID->getMosaic()->isFilled(lineNum, tileType) &&
                                                     playerTurnID->getMosaic()->getLine(lineNum)->canAddTiles(tileType))
                                            {
                                                playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, factories[factoryNum]->draw(tileType), tileType);

                                                for (TileType tile : factories[factoryNum]->empty())
                                                {
                                                    centerPile.push_back(tile);
                                                }

                                                inputDone = true;
                                            }
                                            else
                                                errorMessage = "Specified line cannot add tile";
                                        }
                                        else
                                            errorMessage = "Selected factory does not contain specified tile";
                                    }
                                    else
                                        errorMessage = "Selected factory is empty";
                                }

                                if (inputDone)
                                {
                                    changePlayerTurn();
                                    menu->printMessage("Turn successful.");
                                }
                            }
                            else
                                errorMessage = "Invalid line number";
                        }
                        else
                            errorMessage = "Invalid colour";
                    }
                    else
                        errorMessage = "Invalid factory number";
                }
                else if (command == "save")
                {
                    errorMessage = "Invalid syntax for save command";
                    std::string fileName;
                    if (!ss.eof())
                    {
                        ss.get(); // removes initial whitespace between save and filename
                        std::getline(ss, fileName);
                        if (isNotWhiteSpace(fileName))
                        {
                            Saver saver;
                            saver.save(this, fileName);
                            inputDone = true;
                        }
                    }

                    if (inputDone)
                        menu->printMessage("Game successfully saved to '" + fileName + "'");
                }
                if (!inputDone)
                    menu->printMessage("Invalid input: " + errorMessage + ", try again");
            }
            else
            {
                exit = true;
            }
        } while (!exit && !inputDone);
    }

    if (!exit)
    {
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
    return exit;
}

bool GameEngine::validLineNum(int lineNum)
{
    return lineNum >= 0 && lineNum <= NUMBER_OF_LINES;
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
    std::vector<int> remove;
    int decrement = 0;

    for (int i = 0; i < (int)centerPile.size(); i++)
    {
        if (centerPile[i] == colour)
        {
            count++;
            remove.push_back(i);
        }
    }
    for (int i = 0; i < (int)remove.size(); i++)
    {
        centerPile.erase(centerPile.begin() + (remove[i] - decrement));
        decrement++;
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
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        if (this->factories[i] != nullptr)
            delete this->factories[i];
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
