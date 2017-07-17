#include <iostream>
#include <stdio.h>

bool IsValid (int location [9] [9], int row, int col, int n);
bool Solvable (int location [9] [9]);
bool UsedInSquare (int location [9] [9], int row, int col, int n);
bool UsedInCol (int location [9] [9], int col, int n);
bool UsedInRow (int location [9] [9], int row, int n);

using namespace std;

int main()
{
    int location [9] [9]=  {{0,0,0,0,7,0,9,4,0},
        {0,7,0,0,9,0,0,0,5},
        {3,0,0,0,0,5,0,7,0},
        {0,8,7,4,0,0,1,0,0},
        {4,6,3,0,0,0,0,0,0},
        {0,0,0,0,0,7,0,8,0},
        {8,0,0,7,0,0,0,0,0},
        {7,0,0,0,0,0,0,2,8},
        {0,5,0,2,6,8,0,0,0}};

    if (Solvable (location)== true)
    {
        for (int row=0; row < 9; row++)
        {
            for (int col=0; col <9 ; col++)
            {
                cout << location [row] [col] << " ";
            }
            cout << endl;
        }
    }
    else if (Solvable (location)==false)
    {
        cout << "Processing.." << endl;
        cout << "No Solution" << endl;
    }
    return 0;
}

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

        for (int num=1; num <= 9; num++)
        {
            if (IsValid (location,row,col,num)==true)
            {
                location [row] [col] = num;
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



bool IsValid (int location [9] [9],int row, int col,int num)
{
    return !UsedInRow(location, row, num) &&
           !UsedInCol(location, col, num) &&
           !UsedInSquare(location, row, col, num);

}

bool UsedInRow (int location [9] [9], int row, int num)
{
    for (int col=0; col< 9; col++)
    {
        if (location [row] [col]==num)
        {
            return true;
        }
    }
    return false;
}

bool UsedInCol (int location [9] [9], int col, int num)
{
    for (int row=0; row <9 ; row++)
    {
        if (location [row] [col] == num)
        {
            return true;
        }
    }
    return false;
}

bool UsedInSquare (int location [9] [9], int current_row, int current_col, int num)
{
    for (int row= (current_row/3)*3; row < (current_row/3)*3+3 ; row ++)
    {
        for (int col= (current_col/3)*3; col < (current_col/3)*3+3; col++)
        {
            if (location [row] [col] == num)
            {
                return true;
            }
        }
    }
    return false;
}

