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
    int roundsPlayed = 0;
    do
    {
        playRound();
        roundsPlayed++;
    } while (roundsPlayed < 2);
}

void GameEngine::playRound()
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
    for (int i = 0; i < (int)players.size(); i++)
    {
        menu->roundStart(playerTurnID->getName());
        menu->printFactory(&centerPile);
        for (int i = 0; i < NUM_FACTORIES; i++)
        {
            menu->printFactory(i + 1, factories[i]->toString());
        }
        menu->printMosaic(playerTurnID);

        bool inputDone = false;
        do
        {
            string input = menu->getInput();
            if (input.substr(0, 4) == "turn")
            {
                int factoryNum = (int)input[6];
                TileType colour = charToTileType(input[8]);
                int lineNum = (int)input[10];
                playerTurnID->getMosaic()->insertTilesIntoLine(lineNum, factories[factoryNum]->draw(colour), colour);
                setPlayerTurn();
                inputDone = true;
            }
            else
            {
                menu->printMessage("Invalid input, try again");
            }
        } while (!inputDone);
    }
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

void GameEngine::fillBag(TileList* bag)
{
    this->bag = bag;
}

void GameEngine::fillLid(TileList* lid)
{
    this->lid = lid;
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

    menu->printMessage("Enter the name for player 1: \n");
    string name1 = menu->getInput();
    menu->printMessage("Enter the name for player 2: \n");
    string name2 = menu->getInput();

    addPlayer(name1);
    addPlayer(name2);

    menu->printMessage("Let's Play!");
}

std::vector<TileType> GameEngine::getCenterPile()
{
return centerPile;
}

TileList* GameEngine::getBag()
{
return bag;
}

TileList* GameEngine::getLid()
{
return lid;
}

Player* GameEngine::getPlayerTurnID()
{
    return playerTurnID;
}

Player *GameEngine::getPlayer(int playerIndex)
{
    return players.at(playerIndex);
}
