#include "GameEngine.h"
#include "Saver.h"
#include "Menu.h"

int main(int argc, char const *argv[])
{
    //GameEngine engine = new GameEngine();
    Menu menu;
    bool exit = false;
    std::string input;

    do
    {
        menu.printMenu();
        input = menu.getInput();
        if (input == "1")
        {
            GameEngine *engine = new GameEngine(&menu);
            engine->playGame(argv[0]);
        }
        else if (input == "2")
        {
            Saver *saver = new Saver();
            menu.printMessage("Enter save file name");
            input = menu.getInput();
            GameEngine *newEngine = saver->load(input);
            newEngine->playGame(argv[0]);
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

    return 0;
}
