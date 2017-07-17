#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
int xy [4] [4] {0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0,
                0, 0, 0, 0
               };
//Function

int random ();
bool Unassigned (int xy [4] [4],int,int);
bool UsedInRow (int xy [4] [4], int , int);
bool UsedInCol (int xy [4] [4], int, int);
bool UsedInBox (int xy [4] [4], int, int);


int main()
{
    srand(time(NULL));
    xy [0] [1] = random ();
    xy [0] [2] = random ();
    xy [1] [3] = random ();
    xy [2] [0] = random ();
    xy [3] [1] = random ();
    xy [3] [2] = random ();
    bool valid=true;
    do
    {
        if (xy [3] [1] == xy[3] [2])
        {
            xy [3] [1] = random ();
        }
        if (xy [3] [1] == xy [0] [1])
        {
            xy [0] [1] = random ();
        }
        if (xy [0] [1]== xy [0] [2])
        {
            xy [0] [2]= random ();
        }
        if (xy[0] [2] == xy [1] [3])
        {
            xy [1] [3] = random ();
        }
        if (xy [2] [0] == xy [3] [1])
        {
            xy [2] [0] = random ();
        }
        if (xy [3] [2] == xy [0] [2])
        {
            xy [3] [2] = random ();
        }
        if (xy [3] [2] != xy [0] [2] and xy [3] [1] != xy[3] [2] and xy [3] [1] != xy [0] [1] and xy [2] [0] != xy [3] [1] and xy[0] [2] != xy [1] [3] and xy [0] [1]!= xy [0] [2])
        {
            valid= false;
        }
    }
    while (valid);
    cout << "Puzzle To Solve:" << endl;
    cout << xy [0] [0] << xy [0] [1] << "|" << xy [0] [2] << xy [0] [3] << endl;
    cout << xy [1] [0] << xy [1] [1] << "|" << xy [1] [2] << xy [1] [3] << endl;
    cout << "-----" << endl;
    cout << xy [2] [0] << xy [2] [1] << "|" << xy [2] [2] << xy [2] [3] << endl;
    cout << xy [3] [0] << xy [3] [1] << "|" << xy [3] [2] << xy [3] [3] << endl;

    for (int row=0; row < 4; row++)
    {
        for (int col=0; col < 4; col++)
        {
            if (Unassigned (xy, row, col)) //If it is blanked then,
            {
                for (int numplug=1; numplug <=4; numplug++) //Find a number
                {
                    if (!UsedInRow (xy, row, numplug) and !UsedInCol (xy,col,numplug) and UsedInBox (xy, row-row%2, col-col%2,numplug))
                    {
                        xy [row] [col] = numplug;
                    }
                }
            }
        }
    }

    cout << "Puzzle Solver:"<< endl;
    cout << xy [0] [0] << xy [0] [1] << "|" << xy [0] [2] << xy [0] [3] << endl;
    cout << xy [1] [0] << xy [1] [1] << "|" << xy [1] [2] << xy [1] [3] << endl;
    cout << "-----" << endl;
    cout << xy [2] [0] << xy [2] [1] << "|" << xy [2] [2] << xy [2] [3] << endl;
    cout << xy [3] [0] << xy [3] [1] << "|" << xy [3] [2] << xy [3] [3] << endl;
}

int random ()
{
    int num;
    num= rand () % 4 + 1;
    return num;
}

bool Unassigned (int xy [4] [4], int row, int col)
{
    if (xy [row] [col] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Still need to do:
bool UsedInRow(int xy [4][4], int row, int num)
{
    bool reply;
    for (int col = 0; col < 4; col++)
        if (xy [row][col] == num)
        {
            reply= true;
        }
        else
        {
            reply= false;
        }
        return reply;
}

bool UsedInCol(int xy [4][4], int col, int num)
{
    bool reply;
    for (int row = 0; row < 4; row++)
        if (xy [row][col] == num)
        {
            reply =true;
        }
        else
        {
            reply =false;
        }
        return reply;
}

bool UsedInBox (int xy [4] [4], int currow, int curcol, int num)
{

}
