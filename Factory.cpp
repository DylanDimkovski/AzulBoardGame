#include "Factory.h"

Factory::Factory(int arr[FACTORY_SIZE])
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        tiles[i] = arr[i];
    }
}

void Factory::fill(int arr[FACTORY_SIZE])
{
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        tiles[i] = arr[i];
    }
}

int *Factory::empty()
{
    int array[4];
    int *arrPtr = array;
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i] != NOTILE)
        {
            array[i] = tiles[i];
            tiles[i] = NOTILE;
        }
    }
    return arrPtr;
}

int Factory::draw(int tileType)
{
    int count = 0;
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i] == tileType)
        {
            count++;
            tiles[i] = NOTILE;
        }
    }
    return count;
}

string Factory::toString()
{
    string output = "";

    std::string colours[7] = {"R", "Y", "B", "L", "U", "F", "."};

    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        output += colours[tiles[i]] + ' ';
    }
    
    return output;
}