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
              << message << std::endl
              << std::endl;
}
