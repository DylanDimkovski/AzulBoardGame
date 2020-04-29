#include "GameEngine.h"

GameEngine::GameEngine()
{
    centerPile.push_back(FIRSTPLAYER);
}

GameEngine::~GameEngine()
{
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

void GameEngine::fillBag()
{
}

void GameEngine::addPlayer(string name)
{
    Player player;
}
