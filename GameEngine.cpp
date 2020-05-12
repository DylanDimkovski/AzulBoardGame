#include "GameEngine.h"

#include <iostream>
#include <algorithm>
#include <random>

GameEngine::GameEngine() :
    players(),
    factories(),
    centerPile(),
    playerTurnID("-1"),
    bag(new TileList()),
    lid(new TileList())
{
    centerPile.push_back(FIRSTPLAYER);

    for (int i = 0; i < NUM_FACTORIES; i++) {
        int temp[4] = {NOTILE};
        factories[i] = new Factory(temp);
    }
}

GameEngine::~GameEngine()
{
}

void GameEngine::playGame(char const *argv)
{
    addPlayers();
    fillBag(argv[0]);
    playerTurnID = players[0]->getName();
    playRound();
}

void GameEngine::playRound()
{

    std::cout << "=== Start Round === \n";
    std::cout << "TURN FOR PLAYER: " << playerTurnID << std::endl;
    std::cout << "Factories: \n";
    std::cout << 0 << ": " << std::endl;
    
    for (int i = 0; i < NUM_FACTORIES; i++)
    {
        int temp[4] = {NOTILE};

        for (int j = 0; j < FACTORY_SIZE; j++) {
            temp[j] = bag->getHead()->getValue(); 
            bag->removeFront();
        }

        factories[i]->fill(temp);
        std::cout << i + 1 << ": " << factories[i]->toString() << std::endl;
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

Player* GameEngine::addPlayer(string name)
{
    //creates a new player
    return new Player(name, 0);
}

void GameEngine::addPlayers(){
    //Checks for player names and adds them to player vector
    std::string name1;
    std::string name2;
    std::cout << "Enter the name for player 1: \n";
    std::cin >> name1;
    std::cout << "Enter the name for player 2: \n";
    std::cin >> name2;

    players.push_back(addPlayer(name1));
    players.push_back(addPlayer(name2));

    std::cout << "Let's Play! \n";
}
    
