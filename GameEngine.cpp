#include <iostream>
#include <algorithm>
#include "GameEngine.h"

GameEngine::GameEngine()
{
    centerPile.push_back(FIRSTPLAYER);
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        delete factories[i];
    }
}

void GameEngine::playGame()
{
    addPlayers();
}

void GameEngine::playRound()
{
}

Factory *GameEngine::getFactory(int position)
{
    return factories[position];
}

void GameEngine::fillBag(int argc, char** argv)
{
    TileList* bag = new TileList();
    TileType temp[100];

    for (int i = 0; i < 100; i++)
    {
        if (i < 20)
        {
            temp[i] = BLACK;
        }

        if (i < 40 && i > 20)
        {
            temp[i] = LIGTHBLUE;
        }

        if (i < 60 && i > 40)
        {
            temp[i] = DARKBLUE;
        }
        
        if (i < 80 && i > 60)
        {
            temp[i] = YELLOW;
        }
        
        if (i < 100 && i > 80)
        {
            temp[i] = RED;
        }
    }

    // std::random_shuffle(std::begin(temp), std::end(temp), std::srand(argv) % 100);

    for (int i = 0; i < 100; i++)
    {
        bag->addFront(temp[i]);
    }   
}

void GameEngine::fillBag(TileList bag)
{
    this->bag = bag;
}

void GameEngine::fillLid(TileList lid)
{
    this->lid = lid;
}

void GameEngine::fillFactories(Factory* factories[NUM_FACTORIES])
{
    for (int i = 0; i < NUM_FACTORIES; ++i)
    {
        this->factories[i] = factories[i];
    }
}


void GameEngine::addPlayer(string name)
{
    Player p(name);
    addPlayer(p);
}

void GameEngine::addPlayer(string name, int score, Mosaic* mosaic)
{
    Player p(name, score, mosaic);
    addPlayer(p);
}

void GameEngine::addPlayers(){
    std::string name1;
    std::string name2;
    std::cout << "Enter the name for player 1: \n";
    std::cin >> name1;
    std::cout << "Enter the name for player 2: \n";
    std::cin >> name2;

    addPlayer(name1);
    addPlayer(name2);
}
    
void GameEngine::addPlayer(Player player)
{
    players.push_back(player);
}
