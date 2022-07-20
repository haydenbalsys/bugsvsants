#include <iostream>
#include <cstdlib>  // for rand
#include "World.h"
#include "Ant.h"
#include "Bug.h"
#include "TBug.h"
#include <windows.h>
using namespace std;

///////////////////
// Public functions
///////////////////

// Default constructor: creates and initializes the world
// the seed is used for seeding the random behaviour.
World::World(unsigned int seed) {
    // seed the random generator
    srand(seed);
    // Create an empty world
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            grid[i][j] = NULL;
        }
    }
    // creates the ants = 3
    createOrganisms(ANT, INITIAL_ANTS);
    // creates the bugs = 8
    createOrganisms(BUG, INITIAL_BUGS);
}

// Deallocate memory allocated to organisms in this world.
World::~World() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            if (grid[i][j] != NULL) {
                delete grid[i][j];
            }
        }
    }
}

// Return the organism at the given coordinates
// If the coordinates are not valid, returns NULL
Organism* World::getAt(int x, int y) const {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        return grid[x][y];
    } else {
        return NULL;
    }
}

// Sets the entry at x,y to the value passed in.
void World::setAt(int x, int y, Organism* org) {
    if ((x >= 0) && (x < WORLDSIZE) && (y >= 0) && (y < WORLDSIZE)) {
        grid[x][y] = org;
    }
}

// Displays the world in ASCII.
void World::display() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int numAnts = 0;
    int numBugs = 0;
    int numTBugs = 0;

    SetConsoleTextAttribute(hConsole, 14);
    cout << endl;
    cout << "                           ____       _______ _______ _      ______   ____  _    _  _____  _____ " << endl;
    cout << "                          |  _ |   /||__   __|__   __| |    |  ____| |  _ || |  | |/ ____|/ ____|" << endl;
    cout << "                          | |_) | /  |  | |     | |  | |    | |__    | |_) | |  | | |  __| (___  " << endl;
    cout << "                          |  _ < / /| | | |     | |  | |    |  __|   |  _ <| |  | | | |_ ||___ | " << endl;
    cout << "                          | |_) / ____ || |     | |  | |____| |____  | |_) | |__| | |__| |____) |" << endl;
    cout << "                          |____/_/    |_|_|     |_|  |______|______| |____/ |____/ |_____|_____/ " << endl;
    cout << "                                                                                                 " << endl;
    cout << endl;

    SetConsoleTextAttribute(hConsole, 15);
    cout << "                    " <<
        "                                  Hayden Balsys";
    cout << endl << endl;


    //top border loop vvvv
    cout << "                                        ";

    for (int i = 0; i < 42; i++)
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << char(240);
    }

    cout << endl;

    for (int j = 0; j < WORLDSIZE; j++) {
        //left border
        SetConsoleTextAttribute(hConsole, 12);
        cout << "                                        " << char(216);
        for (int i = 0; i < WORLDSIZE; i++) {
            SetConsoleTextAttribute(hConsole, 15);
            if (grid[i][j] == NULL) {
                cout << " ";
            } else {
                if (grid[i][j]->getType() == ANT) {
                    numAnts++;
                }
                else if (grid[i][j]->getType() == BUG) {
                    numBugs++;
                }
                else if (grid[i][j]->getType() == TBUG) {
                    numTBugs++;
                }
                cout << grid[i][j]->representation();
            }
            SetConsoleTextAttribute(hConsole, 0);
            cout << char(197);
        }

        //right border
        SetConsoleTextAttribute(hConsole, 12);
        cout << char(216);
        cout << endl;
    }

    cout << "                                        ";
    
    for (int i = 0; i < 42; i++) //bottom border
    {
        SetConsoleTextAttribute(hConsole, 12);
        cout << char(240);
    }

    cout << endl;

    
    SetConsoleTextAttribute(hConsole, 3);
    cout << "                      " <<
        "                  Ants " << char(250) << ":" << numAnts << "    "; 
    cout << endl;
    SetConsoleTextAttribute(hConsole, 6);
    cout << "                       " <<
        "                 Bugs " << char(157) << ":" << numBugs << "    ";
    cout << endl;
    SetConsoleTextAttribute(hConsole, 13);
    cout << "                        " <<
        "                Twin Bugs " << char(232) << ":" << numTBugs << "    ";
    cout << endl;
}

void World::simulateOneStep() {
    // The main routine that simulates one turn in the world:
    // 1. move bugs
    // 2. move ants
    // 3. make bugs starve (which happends under a certain condition)
    // 4. make the organisms breed (again which happens under a certain
    // condition).

    // Reset all organisms to not moved
    resetOrganisms();

    // Move the tbugs
    moveOrganism(TBUG);
    resetOrganisms();
    moveOrganism(TBUG);

    // Move the bugs
    moveOrganism(BUG);

    // Move the ants
    moveOrganism(ANT);

    // Make the bugs starve
    cleanup();

    //Make them breed
    breedOrganisms();
}

Position World::randomPosition() const {    // returns a random number in the range 0 to MAX-1
    Position p;
    p.x = rand() % WORLDSIZE;
    p.y = rand() % WORLDSIZE;
    return p;
}


Move World::randomMove() const {
    return static_cast<Move>(rand() % 4);
}

////////////////////
// Private functions
////////////////////

void World::createOrganisms(OrganismType orgType, int count) {
    int orgCount = 0;
    while (orgCount < count) {
        Position p = randomPosition();

        // Only put ant in empty spot
        if (grid[p.x][p.y] == NULL) {
            orgCount++;
            if (orgType == ANT) {
                new Ant(this, p.x, p.y);   // Create an Ant and put it into the world
            }
            else if (orgType == BUG) {
                new Bug(this, p.x, p.y);   // Create a Bug and put it into the world
            }
            else if (orgType == TBUG) {
               new TBug(this, p.x, p.y);   // Create a TBug and put it into the world
            }
        }
    }
}

// Reset all organisms to not moved
void World::resetOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for (int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->setMoved(false);
            }
        }
    }
}

// Move all organisms of type aType
void World::moveOrganism(OrganismType aType) {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getType() == aType && !(grid[i][j]->hasMoved()))
                {
                    grid[i][j]->move();
                }
            }
        }
    }
}

// Remove all dead organisms from this world.
void World::cleanup() {
    for (int i = 0; i < WORLDSIZE; i++) {
        for (int j = 0; j < WORLDSIZE; j++) {
            // Kill off any organisms that haven't eaten recently
            if ((grid[i][j] != NULL) && grid[i][j]->isDead()) {
                delete grid[i][j];
                grid[i][j] = NULL;
            }
        }
    }
}

// Make the organisms breed
void World::breedOrganisms() {
    for(int i = 0; i < WORLDSIZE; i++)
    {
        for(int j = 0; j < WORLDSIZE; j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->breed();
            }
        }
    }
}
