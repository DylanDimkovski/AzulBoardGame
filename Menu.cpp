#include "Menu.h"

void Menu::printMenu()
{
    std::cout << "Menu" << std::endl;
    std::cout << "----" << std::endl;
    std::cout << "1. New Game" << std::endl;
    std::cout << "2. Load Game" << std::endl;
    std::cout << "3. Credits" << std::endl;
    std::cout << "4. Quit" << std::endl;
}
std::string Menu::getInput()
{
    std::string input;
    std::cout << std::endl
              << "> ";
    std::cin >> input;
    return input;
}
void Menu::printRound(bool playerTurn, Factory factories[])
{
}
void Menu::printPlayer(Player player)
{
}
void Menu::printCredits()
{
    std::cout << "Name: Luca Cave" << std::endl;
    std::cout << "Student ID: s3787946" << std::endl;
    std::cout << "Email: s3787946@student.rmit.edu.au" << std::endl
              << std::endl;
    std::cout << "Name: Michael Sartorel" << std::endl;
    std::cout << "Student ID: s3786267" << std::endl;
    std::cout << "Email: s3786267@student.rmit.edu.au" << std::endl
              << std::endl;
    std::cout << "Name: Dylan Dimkovski" << std::endl;
    std::cout << "Student ID: s3717379" << std::endl;
    std::cout << "Email: s3717379@student.rmit.edu.au" << std::endl
              << std::endl;
}

void Menu::printMessage(std::string message)
{
    std::cout << std::endl
              << message
              << std::endl;
}

void Menu::roundStart(string playername)
{
    std::cout << "=== Start Round === \n";
    std::cout << "TURN FOR PLAYER: " << playername << std::endl;
    std::cout << "Factories: \n";
}

void Menu::printFactory(int id, string contents)
{
    std::cout << id << ": " << contents << std::endl;
    std::cout << (id == 5 ? "\n" : "");
}

void Menu::printFactory(std::vector<TileType> *centerPile)
{
    std::string colours[7] = {"R", "Y", "B", "L", "U", "F", "."};

    std::cout << "0: ";
    for (auto tile : *centerPile)
    {
        std::cout << colours[tile] << " ";
    }
    std::cout << std::endl;
}

void Menu::printMosaic(Player *player)
{
    std::string colours[7] = {"R", "Y", "B", "L", "U", "F", "."};

    std::cout << "Mosaic for " << player->getName() << std::endl;
    for (int i = 0; i < NUMBER_OF_LINES; i++)
    {
        std::cout << i + 1 << ": ";
        std::string output;
        int lineSize = player->getMosaic()->getLine(i)->getMaxSize();
        int numTiles = player->getMosaic()->getLine(i)->getNumTiles();

        for (int i = 0; i < 5 - lineSize; i++)
        {
            output += "  ";
        }

        for (int i = 0; i < lineSize - numTiles; i++)
        {
            output += ". ";
        }
        for (int i = 0; i < numTiles; i++)
        {
            output += " " + colours[player->getMosaic()->getLine(i)->getTileType()];
        }

        output += " || ";

        for (int i = 0; i < NUMBER_OF_LINES; i++)
        {
            if (player->getMosaic()->getWallLine(i)[i] == true)
            {
                output += " P";
            }
            else
            {
                output += " .";
            }
        }
        std::cout << output << std::endl;
    }
}
