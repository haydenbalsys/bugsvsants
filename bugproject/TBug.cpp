#include "TBug.h"
#include "Organism.h"
using namespace std;

TBug::TBug(World* aWorld, int xcoord, int ycoord) : Organism(aWorld, xcoord, ycoord)
{
    death_tik = 0;
}

void TBug::move()
{
    //breedTicks++;
    //death_tik++;
    if (world->getAt(x, y + 1) != NULL)
    {
        if (world->getAt(x, y + 1)->getType() == TBUG)
        {
            delete world->getAt(x, y + 1);
            world->setAt(x, y + 1, NULL);
            delete world->getAt(x, y - 1);
            world->setAt(x, y - 1, NULL);
            delete world->getAt(x + 1, y);
            world->setAt(x + 1, y, NULL);
            delete world->getAt(x - 1, y);
            world->setAt(x - 1, y, NULL);
            delete world->getAt(x + 1, y + 1);
            world->setAt(x + 1, y + 1, NULL);
            delete world->getAt(x - 1, y + 1);
            world->setAt(x - 1, y + 1, NULL);
            delete world->getAt(x + 1, y - 1);
            world->setAt(x + 1, y - 1, NULL);
            delete world->getAt(x - 1, y - 1);
            world->setAt(x - 1, y - 1, NULL);
            death_tik = 100;
            return;
        }
    }

    if (world->getAt(x, y - 1) != NULL)
    {
        if (world->getAt(x, y - 1)->getType() == TBUG)
        {
            delete world->getAt(x, y + 1);
            world->setAt(x, y + 1, NULL);
            delete world->getAt(x, y - 1);
            world->setAt(x, y - 1, NULL);
            delete world->getAt(x + 1, y);
            world->setAt(x + 1, y, NULL);
            delete world->getAt(x - 1, y);
            world->setAt(x - 1, y, NULL);
            delete world->getAt(x + 1, y + 1);
            world->setAt(x + 1, y + 1, NULL);
            delete world->getAt(x - 1, y + 1);
            world->setAt(x - 1, y + 1, NULL);
            delete world->getAt(x + 1, y - 1);
            world->setAt(x + 1, y - 1, NULL);
            delete world->getAt(x - 1, y - 1);
            world->setAt(x - 1, y - 1, NULL);
            death_tik = 100;
            return;
        }
    }

    if (world->getAt(x - 1, y) != NULL)
    {
        if (world->getAt(x - 1, y)->getType() == TBUG)
        { 
            delete world->getAt(x, y + 1);
            world->setAt(x, y + 1, NULL);
            delete world->getAt(x, y - 1);
            world->setAt(x, y - 1, NULL);
            delete world->getAt(x + 1, y);
            world->setAt(x + 1, y, NULL);
            delete world->getAt(x - 1, y);
            world->setAt(x - 1, y, NULL);
            delete world->getAt(x + 1, y + 1);
            world->setAt(x + 1, y + 1, NULL);
            delete world->getAt(x - 1, y + 1);
            world->setAt(x - 1, y + 1, NULL);
            delete world->getAt(x + 1, y - 1);
            world->setAt(x + 1, y - 1, NULL);
            delete world->getAt(x - 1, y - 1);
            world->setAt(x - 1, y - 1, NULL);
            death_tik = 100;
            return;
        }
    }
    if (world->getAt(x + 1, y) != NULL)
    {
        if (world->getAt(x + 1, y)->getType() == TBUG)
        {
            delete world->getAt(x, y + 1);
            world->setAt(x, y + 1, NULL);
            delete world->getAt(x, y - 1);
            world->setAt(x, y - 1, NULL);
            delete world->getAt(x + 1, y);
            world->setAt(x + 1, y, NULL);
            delete world->getAt(x - 1, y);
            world->setAt(x - 1, y, NULL);
            delete world->getAt(x + 1, y + 1);
            world->setAt(x + 1, y + 1, NULL);
            delete world->getAt(x - 1, y + 1);
            world->setAt(x - 1, y + 1, NULL);
            delete world->getAt(x + 1, y - 1);
            world->setAt(x + 1, y - 1, NULL);
            delete world->getAt(x - 1, y - 1);
            world->setAt(x - 1, y - 1, NULL);
            death_tik = 100;
            return;
        }
    }

    Move mover = world->randomMove();
    switch (mover) {
    case UP:
        if (world->getAt(x, y - 1) == NULL && in_range(x, y - 1))
        {
            movesTo(x, y - 1);
        }
        break;
    case DOWN:
        if (world->getAt(x, y + 1) == NULL && in_range(x, y + 1))
        {
            movesTo(x, y + 1);
        }
        break;
    case LEFT:
        if (world->getAt(x - 1, y) == NULL && in_range(x - 1, y))
        {
            movesTo(x - 1, y);
        }
        break;
    case RIGHT:
        if (world->getAt(x + 1, y) == NULL && in_range(x + 1, y))
        {
            movesTo(x + 1, y);
        }
        break;
    default:
        break;
    }
}

void TBug::generateOffspring(int whereX, int whereY)
{
    /*new TBug(this->world, whereX, whereY);
    breedTicks = 0;*/
}

void TBug::breed()
{
    /*if (breedTicks >= BREED_BUGS)
    {
        breedAtAdjacentCell();
    }*/

}

bool TBug::isDead() const
{
    if (death_tik >= STARVE_BUGS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

OrganismType TBug::getType() const
{
    return TBUG;
}


char TBug::representation()const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 13);
    return char(232);
}

int TBug::size() const
{
    return 30;
}

bool TBug::in_range(int xx, int yy)
{
    return (xx >= 0) && (xx < WORLDSIZE) && (yy >= 0) && (yy < WORLDSIZE);
}
