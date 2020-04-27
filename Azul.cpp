#include "GameEngine.h"
#include "Menu.h"

int main(int argc, char const *argv[])
{
    //GameEngine engine = new GameEngine();
    Menu *menu = new Menu();
    menu->printMenu();
    std::string input = menu->getInput();
    std::cout << input << std::endl;

    return 0;
}
