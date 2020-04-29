#include "GameEngine.h"

GameEngine::GameEngine()
{
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        factories[i] = new Factory();
    }
    centerPile.push_back(FIRSTPLAYER);
}

GameEngine::~GameEngine()
{
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        delete factories[i];
    }
}

void GameEngine::playGame()
{
}

void GameEngine::playRound()
{
}

Factory *GameEngine::getFactory(int position)
{
    return factories[position];
}