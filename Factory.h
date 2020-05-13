#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include "Types.h"

using std::string;

class Factory
{
public:
    Factory();
    Factory(int array[FACTORY_SIZE]);
    void fill(int array[FACTORY_SIZE]);
    int *empty();
    int draw(int);
    string toString();

private:
    int tiles[FACTORY_SIZE];
};

#endif // !FACTORY_H