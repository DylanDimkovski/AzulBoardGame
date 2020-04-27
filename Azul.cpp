#include "GameEngine.h"
#include "Menu.h"

int main(int argc, char const *argv[])
{
    //GameEngine engine = new GameEngine();
    Menu *menu = new Menu();
    bool exit = false;
    std::string input;
    do
    {
        menu->printMenu();
        input = menu->getInput();
        if (input == "3")
        {
            menu->printCredits();
        }
        else if (input == "4")
        {
            return 0;
        }
        else
        {
            menu->printMessage("Invalid input, try again");
        }
    } while (!exit);

    return 0;
}
