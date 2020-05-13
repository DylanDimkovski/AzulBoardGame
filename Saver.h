#include <string>
#include <iostream>
#include "GameEngine.h"

using std::string;

class Saver
{
public:
    bool save();
    GameEngine *load();
};