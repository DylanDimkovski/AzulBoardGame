#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Menu.h"

class Menu
{
public:
    void printMenu();
    std::string getInput();
    void printRound(bool playerTurn, Factory factories[]);
    void printPlayer(Player player);
    void printCredits();
    void printMessage(std::string message);
    void roundStart(std::string playerName);
    void printFactory(int id, string contents);
    void printFactory(std::vector<TileType> *centerPile);
    void printMosaic(Player *player);
};

#endif // !MENU_H