#include <Factory.h>

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
        if (tiles[i] != 0)
        {
            array[i] = tiles[i];
            tiles[i] = 0;
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
            tiles[i] = 0;
        }
    }
    return count;
}

string Factory::toString()
{
    string tiles = "";
    for (int i = 0; i < FACTORY_SIZE; i++)
    {
        if (tiles[i != 0])
        {
            tiles += tiles[i] + " ";
        }
    }
    return tiles;
}