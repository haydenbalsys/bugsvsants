#include <cstdlib>
#include <iostream>
#include "Ant.h"
#include "Organism.h"
#include "World.h"
#include <Windows.h>
#include <string>
using namespace std;

Ant::Ant(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    
}

void Ant::move()
{
    breedTicks++;
    Move mover = world->randomMove();
    switch (mover){
        case UP:
            if(world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
            {
                movesTo(x, y + 1);
            }
            break;
        case DOWN:
            if(world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
            {
                movesTo(x, y - 1);
            }
            break;
        case LEFT:
            if(world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
            {
                movesTo(x - 1, y);
            }
            break;
        case RIGHT:
            if(world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
            {
                movesTo(x + 1, y);
            }
            break;
        default:
            break;
    }
}

void Ant::breed()
{
    if(breedTicks >= BREED_ANTS)
    {
        breedAtAdjacentCell();
    }
}


void Ant::generateOffspring(int whereX, int whereY)
{
    new Ant(this->world, whereX, whereY);
    breedTicks = 0;
}


OrganismType Ant::getType() const
{
    return ANT;
}

char Ant::representation() const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 3);
    return char(250);
}

int Ant::size() const
{
    return 10;
}

bool Ant::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
