#include "GameEngine.h"
#include "Saver.h"
#include "Menu.h"
#include "Saver.h"

int main(int argc, char const *argv[])
{
    //GameEngine engine = new GameEngine();
    Menu menu;
    bool exit = false;
    std::string input;
    GameEngine *engine = nullptr;
    Saver saver;
    do
    {
        menu.printMenu();
        input = menu.getInput();
        if (input == "1")
        {
            menu.printMessage("Starting a New Game");
            engine = new GameEngine(&menu);
            exit = engine->playGame(argv[0]);
        }
        else if (input == "2")
        {
            menu.printMessage("Enter the filename from which load a game");
            std::string fileName = menu.getInput();
            if (!std::cin.eof())
            {
                engine = saver.load(fileName, &menu);
                if (engine != nullptr)
                {
                    menu.printMessage("Azul game successfully loaded");
                    exit = engine->playGame();
                }
                else menu.printMessage("Error reading file\n");
            }
            else exit = true;
        }
        else if (input == "3")
        {
            menu.printCredits();
        }
        else if (std::cin.eof() || input == "4")
        {
            exit = true;
        }
        else
        {
            menu.printMessage("Invalid input, try again");
        }
    } while (!exit);
    menu.printMessage("Goodbye");
    delete engine;

    return 0;
}
