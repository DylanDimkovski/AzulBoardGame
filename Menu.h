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
    void handStart(std::string playerName);
    void printFactory(int id, string contents);
    void printFactory(std::vector<TileType> *centerPile);
    void printMosaic(Player *player);
    void printScore(string name, int score);
    void gameOver(Player *player);
    void gameOver(std::string name1, std::string name2, int score);

private:
    TileType master_wall[NUMBER_OF_LINES][NUMBER_OF_LINES] = {DARKBLUE, YELLOW, RED, BLACK, LIGTHBLUE,
                                                              LIGTHBLUE, DARKBLUE, YELLOW, RED, BLACK,
                                                              BLACK, LIGTHBLUE, DARKBLUE, YELLOW, RED,
                                                              RED, BLACK, LIGTHBLUE, DARKBLUE, YELLOW,
                                                              YELLOW, RED, BLACK, LIGTHBLUE, DARKBLUE};
};

#endif // !MENU_H