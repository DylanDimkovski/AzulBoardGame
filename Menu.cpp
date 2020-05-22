#include "Menu.h"

void Menu::printMenu()
{
    std::cout << "Menu" << std::endl
              << "----" << std::endl
              << "1. New Game" << std::endl
              << "2. Load Game" << std::endl
              << "3. Credits" << std::endl
              << "4. Quit" << std::endl
              << std::endl;
}
std::string Menu::getInput()
{
    std::string input;
    std::cout << "> ";
    std::getline(std::cin, input);
    std::cout << input << std::endl;
    return input;
}
void Menu::printCredits()
{
    std::cout << std::endl
              << "----------------------------------" << std::endl
              << "Name: Luca Cave" << std::endl
              << "Student ID: s3787946" << std::endl
              << "Email: s3787946@student.rmit.edu.au" << std::endl
              << std::endl
              << "Name: Michael Sartorel" << std::endl
              << "Student ID: s3786267" << std::endl
              << "Email: s3786267@student.rmit.edu.au" << std::endl
              << std::endl
              << "Name: Dylan Dimkovski" << std::endl
              << "Student ID: s3717379" << std::endl
              << "Email: s3717379@student.rmit.edu.au" << std::endl
              << "----------------------------------" << std::endl
              << std::endl;
}

void Menu::printMessage(std::string message)
{
    std::cout << std::endl
              << message
              << std::endl;
}

void Menu::handStart(string playername)
{
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
    std::cout << "0: ";
    for (TileType tile : *centerPile)
    {
        std::cout << (char)tile << " ";
    }
    std::cout << std::endl;
}

void Menu::printMosaic(Player *player)
{
    std::cout << "Mosaic for " << player->getName() << std::endl;
    for (int j = 0; j < NUMBER_OF_LINES; j++)
    {
        std::cout << j + 1 << ": ";
        std::string output;
        int lineSize = player->getMosaic()->getLine(j)->getMaxSize();
        int numTiles = player->getMosaic()->getLine(j)->getNumTiles();

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
            output += " ";
            output += player->getMosaic()->getLine(j)->getTileType();
        }

        output += " || ";

        for (int i = 0; i < NUMBER_OF_LINES; i++)
        {
            if (player->getMosaic()->getWallLine(j)[i] == true)
            {
                output += " ";
                output += master_wall[j][i];
            }
            else
            {
                output += " .";
            }
        }
        std::cout << output << std::endl;
    }
    std::cout << "broken: " << player->getMosaic()->getBrokenTiles()->toString() << std::endl;
}

void Menu::printScore(string name, int score)
{
    std::cout << name << " score: " << score << std::endl;
}

void Menu::gameOver(Player *player)
{
    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "Player " << player->getName() << " wins!" << std::endl;
    printScore(player->getName(), player->getScore());
}

void Menu::gameOver(string name1, string name2, int score)
{
    std::cout << "=== Game Over ===" << std::endl;
    std::cout << "Draw!" << std::endl;
    std::cout << "Player " << name1 << " score: " << score << std::endl;
    std::cout << "Player " << name2 << " score: " << score << std::endl;
}