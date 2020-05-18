#include "GameEngine.h"
#include "Menu.h"

int main(int argc, char const *argv[])
{
    //GameEngine engine = new GameEngine();
    Menu menu;
    bool exit = false;
    std::string input;
    GameEngine *engine = nullptr;
    do
    {
        menu.printMenu();
        input = menu.getInput();
        if (input == "1")
        {
            engine = new GameEngine(&menu);
            engine->playGame(argv[0]);
        }
        else if (input == "3")
        {
            menu.printCredits();
        }
        else if (input == "4")
        {
            exit = true;
        }
        else
        {
            menu.printMessage("Invalid input, try again");
        }
    } while (!exit);

    delete engine;

    return 0;
}
