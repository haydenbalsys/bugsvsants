#include <iostream>
#include <ctime>    // for time
#include "World.h"
#include <Windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int column, int line) //gotoxy function which is used to move and animate objects in my game
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
    World myWorld(time(0));
    gotoxy(40, 5);
    myWorld.display();
    
    char ch;

    while (1) {   // q for quit
        
        if (_kbhit())
        {
            ch = _getch();

            if (ch == 'a' || ch == 'A')
            {
                myWorld.createOrganisms(ANT, 1);
            }
            else if (ch == 'b' || ch == 'B')
            {
                myWorld.createOrganisms(BUG, 1);
            }
            else if (ch == 't' || ch == 'T')
            {
                myWorld.createOrganisms(TBUG, 1);
            }
        }
        myWorld.simulateOneStep();
        gotoxy(40, 5);
        myWorld.display();
        Sleep(300);
    }

    return 0;
}
