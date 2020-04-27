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
    std::cin >> input;
    return input;
}
void Menu::printRound(bool playerTurn, Factory factories[])
{
}
void Menu::printPlayer(Player player)
{
}
// void Menu::printSuccess()
// {
// }
// void Menu::printMessage(String message)
// {
// }
