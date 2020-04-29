#ifndef MENU_H
#define MENU_H

#include <string>
#include <iostream>
#include "Factory.h"
#include "Player.h"

class Menu
{
public:
    void printMenu();
    std::string getInput();
    void printRound(bool playerTurn, Factory factories[]);
    void printPlayer(Player player);
    void printCredits();
    void printMessage(std::string message);
};

#endif // !MENU_H