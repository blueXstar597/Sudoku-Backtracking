#include <iostream>

using namespace std;

int x [2][2]= {{0,0},
    {0,0}
};

bool Unassigned (int x [2] [2],int,int);
bool UsedInRow (int x [2] [2], int , int);
bool UsedInCol (int x [2] [2], int, int);

int main()
{
    cin >> x [0] [0];
    for (int n=1; n <= 2; n++) //Number used to plug in
    {
        for (int row=0; row < 2; row++) //Search for rows
        {
            for (int col=0; col < 2; col++) //Search for col
            {
                if (Unassigned (x, row, col) and UsedInRow (x, row, n) and UsedInCol (x,col,n)) // If it is blanked, then fill with number
                {
                    x [row] [col] = n;
                }
            }
        }
    }

    cout << x [0] [0] << "|" << x [0] [1] << endl;
    cout << x [1] [0] << "|" << x [1] [1];

    return 0;
}

bool Unassigned (int x[2] [2], int row, int col)
{
    if (x [row] [col] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//Still need to do:
bool UsedInRow(int x [2][2], int row, int num)
{
    for (int col = 0; col < 2; col++)
        if (x [row][col] == num)
        {
            return false;
        }
        else
        {
            return true;
        }
}

bool UsedInCol(int x [2][2], int col, int num)
{
    for (int row = 0; row < 2; row++)
        if (x [row][col] == num)
        {
            return false;
        }
        else
        {
            return true;
        }
}

