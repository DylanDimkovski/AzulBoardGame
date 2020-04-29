#ifndef TILELIST_H
#define TILELSIT_H

#include "Types.h"
#include "Node.h"

class TileList
{
    public:
        TileList();
        ~TileList();
        int size();
        void clear();
        void addFront(TileType tile);
        void addBack(TileType tile);
        TileType removeFront();
        TileType removeBack();

    private:
        Node* head;
        Node* tail;
        int length;
};

#endif