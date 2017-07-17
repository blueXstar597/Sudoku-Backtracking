#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;
vector <int> randomNum ();

bool IsValid (int location [9] [9], int row, int col, vector <int> numGroup, int n);
bool Solvable (int location [9] [9]);
bool UsedInSquare (int location [9] [9], int row, int col, vector <int> numGroup, int n);
bool UsedInCol (int location [9] [9], int col,vector <int> numGroup, int n);
bool UsedInRow (int location [9] [9], int row,vector <int> numGroup, int n);
bool Reproduce (int location [9] [9]);
int random ();

int main()
{
    srand(time(NULL));
    int location [9] [9]=  {{0, 0, 0, 0, 0,0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    if (Solvable (location)== true)
    {
        for (int x=1; x <= 64; x++ )
        {
            location [random ()] [random()] = 0;
        }
        for (int row=0; row < 9; row++)
        {
            for (int col=0; col <9 ; col++)
            {
                cout << location [row] [col] << " ";
            }
            cout << endl;
        }
        cout << "----------------------------" << endl;
        if (Reproduce (location) == true)
        {
            cout << "Real Puzzle" << endl;
            for (int row=0; row < 9; row++)
            {
                for (int col=0; col <9 ; col++)
                {
                    cout << location [row] [col] << " ";
                }
                cout << endl;
            }
            cout << "-------------------------" << endl;
        }
        else
        {
            main ();
        }
    }
    else
    {
        cout << "No solution" << endl;
    }
    return 0;
}

//----------------------------------------------------------------------------------------
bool Solvable (int location [9] [9])
{
    //Assigned a counter
    int a=0;
    //Declare rows and col with unassigned value
    int row,col;
    //Search for the rows (0-8)
    for (int rowVal=0; rowVal < 9; rowVal++)
    {
        //Search for the cols (0-8)
        for (int colVal=0; colVal < 9; colVal++)
        {
            //If the location is equal to blank
            if (location [rowVal] [colVal]== 0)
            {
                //Track this by:
                //Adding one
                row=rowVal;
                col=colVal;
                a++;
                break;
            }
        }
        if (a>0)
        {
            break;
        }
    }
    if (a==0)
    {
        return true;
    }

    vector <int> numGroup = randomNum ();

    for (int num=0; num <= 8; num++)
    {
        if (IsValid (location,row,col,numGroup,num)==true)
        {
            location [row] [col] = numGroup [num];
            //Reference to this web:
            if (Solvable (location))
            {
                return true;
            }
            location [row] [col] = 0;
        }
    }
    return false;
}


//----------------------------------------------------------------------------------------
bool IsValid (int location [9] [9],int row, int col, vector <int> numGroup, int num)
{
    return !UsedInRow(location, row,numGroup, num) &&
           !UsedInCol(location, col,numGroup, num) &&
           !UsedInSquare(location, row, col,numGroup, num);

}
//----------------------------------------------------------------------------------------
bool UsedInRow (int location [9] [9], int row, vector <int> numGroup, int num)
{
    for (int col=0; col< 9; col++)
    {
        if (location [row] [col]==numGroup [num])
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------
bool UsedInCol (int location [9] [9], int col, vector <int> numGroup, int num)
{
    for (int row=0; row <9 ; row++)
    {
        if (location [row] [col] == numGroup [num])
        {
            return true;
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------
bool UsedInSquare (int location [9] [9], int current_row, int current_col,vector <int> numGroup, int num)
{
    for (int row= (current_row/3)*3; row < (current_row/3)*3+3 ; row ++)
    {
        for (int col= (current_col/3)*3; col < (current_col/3)*3+3; col++)
        {
            if (location [row] [col] == numGroup [num])
            {
                return true;
            }
        }
    }
    return false;
}
//----------------------------------------------------------------------------------------
vector <int> randomNum ()
{
    vector <int> numGroup;
    int num;
    for (int x=0; x <= 8; x++)
    {
        num= rand () % 9 + 1;
        numGroup.push_back (num);
    }
    for (int x=0 ; x <= numGroup.size (); x++)
    {
        for (int i=0; i < x; i++)
        {
            if (numGroup [x]== numGroup [i])
            {
                numGroup [i]= rand () % 9 + 1;
                x=0;
            }
        }
    }
    return numGroup;
}

int random ()
{
    int num;
    num= rand () % 9 + 0;
    return num;
}

bool Reproduce (int location [9] [9])
{
    int Decoy [9] [9];
    int Decoy2 [9] [9];

    for (int row=0; row < 9 ; row++)
    {
        for (int col=0; col < 9; col++)
        {
            Decoy [row] [col] = location [row] [col];
            Decoy2 [row] [col] = location [row] [col];
        }
    }
    if (Solvable (Decoy)==true)
    {
        cout << "Solved?!(Decoy 1):" << endl;
        for (int row=0; row < 9 ; row++)
        {
            for (int col=0; col < 9; col++)
            {
                cout << Decoy [row] [col] << " ";
            }
            cout << endl;
        }
        if (Solvable (Decoy2)==true)
        {
            cout << "Decoy 2:"  << endl;
            for (int row=0; row < 9 ; row++)
            {
                for (int col=0; col < 9; col++)
                {
                    cout << Decoy2 [row] [col] << " ";
                }
                cout << endl;
            }
            for (int row=0; row <= 8; row++)
            {
                for (int col=0; col <=8; col++)
                {
                    if (Decoy [row] [col] != Decoy2 [row] [col])
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}
