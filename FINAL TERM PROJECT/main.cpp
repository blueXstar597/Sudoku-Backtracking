//Copyrighted by Danny Ou (2016)
//THIS IS THE FINAL TERM PROJECT and the main purpose of this project is to generate a Sudoku puzzle (Medium Diffculty)
//and it is able to solve and recongize files from outside to solve it
//If more detail is wanted, then go the Design Document of the file. Anyway, good luck and have fun.
//LEGEND: '0' is just a placeholder for space. Please dont press ' ' or nothing on the keyboard when inputting the result

//Preamble - the stuff where the you access the lib
#include <iostream> //Main formatted lib
#include <string> //Enable the string funcation Ex: isdigit ()
#include <time.h> //Enable the random generator Ex: (srand(Null))
#include <stdio.h> //Enable the additional component of Random
#include <stdlib.h> //Funcation Exit to exit out of the funcation
#include <vector> //Vectors are very useful as I can use them to store data of the array into a 81 stored array
#include <fstream> //Enable me to open up the file using the file command
#include <algorithm> // This is a faster time;

//----------------------------------------------------------------------------------------------

//Format STD to the command
using namespace std;

//---------------------------------------------------------------------------------------------
//Creates a function to do the following:
//While solving the Sudoku, this funcation will check the valid compoenet
bool IsValid (int location [9] [9], int row, int col, vector <int> numGroup, int n);
//The main centre of the code that enable Backtracking and solving the puzzle
bool Solvable (int location [9] [9]);
//Create a function to check to see the number is used in the square or Martix as the assiging number
bool UsedInSquare (int location [9] [9], int row, int col, vector <int> numGroup, int n);
//Create a function to check to see if the number is ued in the same col as the assigning number
bool UsedInCol (int location [9] [9], int col,vector <int> numGroup, int n);
//Create a function to check to see if the number is ued in the same row as the assigning number
bool UsedInRow (int location [9] [9], int row,vector <int> numGroup, int n);
//This funcation create to see if certain puzzle have certain solution, different = 0; or same =  1;
bool Reproduce (int location [9] [9]);

//----------------------------------------------------------------------------------------------
//This funcation is used to store all of the 9x num in different order
vector <int> randomNum ();
//This funcation is used to deliver across the Sudoku Puzzle if it is being translated with the same solution in the same puzzle
vector <int> Challenge ();
//This funcation will read in file from a .docu or a .txt and gather the data by using vector and string manplution
vector <int> ReadInFile ();
//----------------------------------------------------------------------------------------------

//This funcation will create random number from 9-0.
int random ();

//----------------------------------------------------------------------------------------------

//Main Function of the code- the starting of the program
int main()
{
    //The command for creating or generating random numbers
    //Adding it in the beignning adds more varies and randomness
    srand(time(NULL));
    //Declare variable as int
    int selection;

    //Display the rules
    cout << "RULES:" << endl;
    cout << "- 0,0 - 0,1 - 0,2 - etc -------------------------------------> Right first" << endl;
    cout << "| D" << endl;
    cout << "| o" << endl;
    cout << "| w" << endl;
    cout << "| n" << endl;
    cout << "V 1" << endl;

    cout <<endl;
    cout <<endl;
    cout <<endl;

//Display the input of the message - Gives the user an option
    cout << "How is your day? Do you want a challenge or a Sudoku Solver?" << endl;
    cout << "1.) Challenge          2.) Sudoku Solver" << endl;

//Receive input from the user
    cin >> selection;

    while (selection > 2 or selection <= 0 or cin.fail ())
    {
        //Display that the user need to re-input the number again
        cin.clear ();
        //Clear and Ignore the character's of the variables
        cin.ignore (1000, '\n');
        //Ask the user to input the number
        cout << "Enter in the range of 1-2:" << endl;
        //Input the number again
        cin >> selection;
        cout << endl;
    }

//If the user chooses option one, enter:
    if (selection == 1)
    {
        //Set a counter to unload the vector quanity
        int counter=0;
        //Declare variable as a vector - returning from Challenge
        vector <int> PuzzleData= Challenge ();

        //-------------------------------------------------------------------------------------------------
        //Declare the data piece
        int PuzzleLocation [9] [9];
        //--------------------------------------------------------------------------------------------------
        //Display for formatting
        cout << endl;
        //Display Output or the message
        cout << "PUZZLE OF THE DAY:" << endl;
        //Display for formatting
        cout << endl;
        //--------------------------------------------------------------------------------------------------

        //Display result in a formatted way
        cout << "+------+------+------+" << endl;
        for (int row=0; row < 9; row++)
        {
            cout << "|";
            for (int col=0; col < 9; col++)
            {
                //Initalize the location of each position
                PuzzleLocation [row] [col] = PuzzleData [counter];
                //Add to the counter each time
                counter++;
                //Display the location
                cout << PuzzleLocation [row] [col] << " ";
                //Display in style
                if ((col+1)%3==0)
                {
                    cout << "|";
                }
            }
            //Display for format
            cout << endl;
            if ((row+1)%3==0)
            {
                cout << "+------+------+------+" << endl;
            }
        }
        cout << endl;
        //--------------------------------------------------------------------------------------------------
        //Declare for an answer key grid
        int AnswerKey [9] [9];
        //--------------------------------------------------------------------------------------------------

//Display the input of where the user needs to guess- shows the empty space of the board
        for (int row=0; row <9; row++)
        {
            for (int col=0; col <9; col++)
            {
                AnswerKey [row] [col] = PuzzleLocation [row] [col];
                if (PuzzleLocation [row] [col]==0)
                {
                    cout << "Spot: " << "(" << row << "," << col << ")";
                    //Display the input of where the user needs to guess or answer in order to solve
                    cin >> PuzzleLocation [row] [col];
                    cout << endl;
                    while (PuzzleLocation [row] [col]<=0 or PuzzleLocation [row] [col] >=10 or cin.fail ())
                    {
                        //Display that the user need to re-input the number again
                        cin.clear ();
                        //Clear and Ignore the character's of the variables
                        cin.ignore (1000, '\n');
                        //Ask the user to input the number
                        cout << "Enter in the range of 1-9:" << endl;
                        //Input the number again
                        cout << "Spot: " << "(" << row << "," << col << ")";
                        cin >> PuzzleLocation [row] [col];
                        cout << endl;
                    }
                }
            }
        }

        //--------------------------------------------------------------------------------------------------
//Solving the Answerkey to see if the Puzzle Solved by the user is the same
        Solvable(AnswerKey);

        //--------------------------------------------------------------------------------------------------

//Display the output of the Answer key
        cout <<"AnswerKey:" << endl;
        cout << "+------+------+------+" << endl;
        for (int row=0; row <9; row++)
        {
            cout << "|";
            for (int col=0; col < 9; col++)
            {
                cout << AnswerKey [row] [col] << " ";
                if ((col+1)%3==0)
                {
                    cout << "|";
                }
                //--------------------------------------------------------------------------------------------------
//If the answerkey is not equal to the User's grid, the program will terminated with you losing
                if (AnswerKey [row] [col] != PuzzleLocation [row] [col])
                {
                    //Display output message
                    cout << "You Lose";
                    //Exit the program with false
                    return -1;
                }

                //--------------------------------------------------------------------------------------------------
            }
            //Format for style
            cout << endl;
            if ((row+1)%3==0)
            {
                cout << "+------+------+------+" << endl;
            }
        }

        //--------------------------------------------------------------------------------------------------
        //Otherwise, if there is no wrong:
        cout << "You win" << endl;
        //Display Output
        return 1;
    }
    else
    {
        cout << endl;

        int counter=0;
        //Declare variable- grid
        int location [9] [9]= {{0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0}
        };

        vector <int> Data = ReadInFile ();

        //Spot the location to input the numbers
        for (int row=0; row <9; row++) //Check rows
        {
            for (int col=0; col < 9; col++) //Checks col
            {
                /*
                if (location [row] [col]==0) //If it is equal to zero, or blank
                {
                    //Gives the position
                    cout << "Location:" << "(" << row << ", "<< col << ")";
                    //Let the user input the type of Sudoku that it wants to be solved
                    cin >> location [row] [col];
                    //Display for format
                    cout << endl;
                    while (location [row] [col] <0 or location [row] [col] >=10 or cin.fail ())
                    {
                        //Display that the user need to re-input the number again
                        cin.clear ();
                        //Clear and Ignore the character's of the variables
                        cin.ignore (1000, '\n');
                        //Ask the user to input the number
                        cout << "Enter in the range of 1-9:" << endl;
                        //Input the number again
                        cout << "location: " << "(" << row << "," << col << ")";
                        cin >> location [row] [col];
                        cout << endl;
                    }
                    */
                location [row] [col] = Data [counter];
                counter++;
            }
        }


        //Disply the File in a formatted way
        cout << "Your Submitted Data:" << endl;
        cout << "+------+------+------+" << endl;

        for (int row=0; row < 9; row ++)
        {
            cout << "|";
            for (int col=0; col < 9; col++)
            {
                //Display the file
                cout << location [row] [col] << " ";
                if ((col+1)%3==0)
                {
                    cout << "|";
                }
            }
            cout << endl;
            if ((row+1)%3==0)
            {
                cout << "+------+------+------+" << endl;
            }
        }

        //This will solved the Sudoku, if it is true
        if (Solvable (location)== true)
        {
            //Display the Output in a formatted way
            cout << "Answer Key:" << endl;
            cout << "+------+------+------+" << endl;
            for (int row=0; row < 9; row++)
            {
                cout << "|";
                for (int col=0; col < 9 ; col++)
                {
                    cout << location [row] [col] << " ";
                    if ((col+1)%3==0)
                    {
                        cout << "|";
                    }
                }
                cout << endl;
                if ((row+1)%3==0)
                {
                    cout << "+------+------+------+" << endl;
                }
            }
        }

        //Otherwise,
        else if (Solvable (location)==false)
        {
            //Display the Output- No results
            cout << "Processing.." << endl;
            cout << "No Solution" << endl;
        }
    }
}


//----------------------------------------------------------------------------------------
//This funcation will backtrack and solve the Sudoku and the missing pieces
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
                //Track one the open space
                a++;
                //Breaks from the loop
                break;
            }
        }
        //If greater than 0, break as it need to fill it in
        if (a>0)
        {
            break;
        }
    }
    //If a==0, the solution is solved
    if (a==0)
    {
        return true;
    }
    //--------------------------------------------------------------------------------------------------

//Have a random fill-in generator so it will not be that predictable

    vector <int> numGroup = randomNum ();

    //--------------------------------------------------------------------------------------------------

//Put an index for the vector to choose a random num
    for (int num=0; num < 9; num++)
    {
        //If it follows the rule, good (true)
        if (IsValid (location,row,col,numGroup,num)==true)
        {
            //Make the location equal to the random number
            location [row] [col] = numGroup [num];
            //Reference to this web:
            //This is the major part of where backtracking is started, if, this is detect false, it will re-set to zero
            if (Solvable (location))
            {
                return true;
            }
            //Set it to zero;
            location [row] [col] = 0;
        }
    }
    return false; //this triggers backtracking as it destory the top numbers if it follows the wrong path
}


//----------------------------------------------------------------------------------------
//This funcation is used to check on the rules of the Sudoku
bool IsValid (int location [9] [9],int row, int col, vector <int> numGroup, int num)
{
    //If these funcation are equal to !(true), then the program will return this back, let it know that it is ok to put the number there
    return !UsedInRow(location, row,numGroup, num) &&
           !UsedInCol(location, col,numGroup, num) &&
           !UsedInSquare(location, row, col,numGroup, num);

}
//----------------------------------------------------------------------------------------
//Funcation that is used to check on the rows;
bool UsedInRow (int location [9] [9], int row, vector <int> numGroup, int num)
{
    //Checks along the rows
    for (int col=0; col< 9; col++)
    {
        //If the number is equal to any other number in the cols
        if (location [row] [col]==numGroup [num])
        {
            //Return denied - Don't fill it in
            return true;
        }
    }
    //Return output - Success - Fill it in
    return false;
}
//----------------------------------------------------------------------------------------
//Funcation that is ued to check on cols;
bool UsedInCol (int location [9] [9], int col, vector <int> numGroup, int num)
{
    //Check along the cols
    for (int row=0; row <9 ; row++)
    {
        //If the number is equal to any other number in the rows
        if (location [row] [col] == numGroup [num])
        {
            //Return denied - Don't fill it in
            return true;
        }
    }
    //Return output - Success - Fill it in
    return false;
}
//----------------------------------------------------------------------------------------
//Funcation that is used to check on the Sqaures
bool UsedInSquare (int location [9] [9], int current_row, int current_col, vector <int> numGroup, int num)
{
    //Finds an area for a 3 by 3 square, no matter where the position is at
    for (int row= (current_row/3)*3; row < (current_row/3)*3+3 ; row ++)
    {
        //Same for the cols
        for (int col= (current_col/3)*3; col < (current_col/3)*3+3; col++)
        {
            //If the number is equal to any other number in the square
            if (location [row] [col] == numGroup [num])
            {
                //Return denided - Don't fill it in
                return true;
            }
        }
    }
    //Return output -Success - Fill it in
    return false;
}
//----------------------------------------------------------------------------------------
//Funcation for creating random numbers in different order
vector <int> randomNum ()
{

    //Declare vectors and num;
    vector <int> numGroup;
    int counter=0;
    int num;
    int End= random ();
    for (int x=1; x <= 9; x++)
    {
        //Create 9 randoms number
        num= x;
        //Push back and store
        numGroup.push_back (num);
    }
    /*
    //--------------------------------------------------------------------------------------------------
    //Checks the sizes of the store
    int y=0;
    /*for (int x=0 ; x < numGroup.size (); x++)
    {
        //Check all the way from the store
        for (int i=0; i < x; i++)
        {
            //If it is equal,
            if (numGroup [x]== numGroup [i])
            {
                //Randomize again
                numGroup [i]= rand () % 9 + 1;
                //Set the number to zero- so it has to check ALL
                x=0;
                break;
            }

        }
    }
    */

// ^
// |
// |
//Faster time - Quick random....
    random_shuffle (numGroup.begin(), numGroup.end());

    //--------------------------------------------------------------------------------------------------
    //Return output to the Solvable funcation
    return numGroup;
}

//Small Funcation for a one random number
int random ()
{
    //Declare variable to be random from 9-0
    int num= rand () % 9 + 0;
    //Return output
    return num;
}

//Funcation to solve the Sudoku for extra solution
bool Reproduce (int location [9] [9])
{
    //Declare three 2-D array variables to complete the Sudoku
    int Decoy [9] [9];
    int Decoy2 [9] [9];
    int Decoy3 [9] [9];

    //--------------------------------------------------------------------------------------------------

//Create the rows
    for (int row=0; row < 9 ; row++)
    {
        for (int col=0; col < 9; col++) //Create the Col
        {
            //Intilazilze all of the location of the current Sudoku and copy them to a decoy
            Decoy [row] [col] = location [row] [col];
            Decoy2 [row] [col] = location [row] [col];
            Decoy3 [row] [col] = location [row] [col];
        }
    }

    //-------------------------------------------------------------------------------------

//Decoy has to be solved then
    if (Solvable (Decoy)==true)
    {
        //Deocy 2 has to be solved
        if (Solvable (Decoy2)==true)
        {
            //--------------------------------------------------------------------------------------------------
            //Decoy 3 has to be solved
            if (Solvable (Decoy3)==true)
            {
                for (int row=0; row <= 8; row++) //Create rows
                {
                    for (int col=0; col <=8; col++) //Create col
                    {
                        //Compare, if one of the result is different then the program will re-do the funcation and start it from the beginning again
                        if ((Decoy [row] [col] != Decoy2 [row] [col]) or (Decoy [row] [col]!= Decoy3 [row] [col]) or (Decoy2 [row] [col] != Decoy3 [row] [col]))
                        {
                            //Return output
                            return false;
                        }
                    }
                }
                //If nothing happen, then return true as there is only one solution
                return true;
            }
            //--------------------------------------------------------------------------------------------------
        }
    }
}

//----------------------------------------------------------------------
//Funcation for creating a vector to return back the puzzle Sudoku
vector <int> Challenge()
{
    //Declare variable
    vector <int> PuzzleNum;

    //--------------------------------------------------------------------------------------------------

//Have this loop where when the puzzle has multiple solutions,remove the program board
    do
    {
        //Delcare the 9x9 Sudoku
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

//--------------------------------------------------------------------------------------------------

//If the grid is solvable, which it is...
        if (Solvable (location)== true)
        {
            //--------------------------------------------------------------------------------------------------
            //Start filling in random spaces
            int blankSpace=0;
            while (true)
            {
                //this keeps running until it hits 51 blankspace
                //Have a random locator to fill it in
                location [random()] [random()]=0;
                for (int row=0; row < 9; row++) //Create rows
                {
                    for (int col=0; col <9 ; col++) //Create col
                    {
                        //Checks for how many blank space
                        if (location [row] [col] == 0)
                        {
                            //Add those to a counter
                            blankSpace++;
                        }
                    }
                }
                //If the blankspace is 51;
                if (blankSpace==50)//50-52
                {
                    //Go ahead and be released
                    break;
                }
                //If not, reset the counter to have 51 space
                blankSpace=0;
            }
            //--------------------------------------------------------------------------------------------------

//If the Sudoku has one solution
            if (Reproduce (location) == true)
            {
                for (int row=0; row < 9; row++) //Create rows
                {
                    for (int col=0; col <9 ; col++) //Create cols
                    {
                        PuzzleNum. push_back(location [row] [col]); //Store the number of the position in a vector to move the data
                    }
                }
                //Return the vector to the int main();
                return PuzzleNum;
            }
            //--------------------------------------------------------------------------------------------------
        }
    }
    //If there is no solutions or more than one solution-retry this funcation again
    while (PuzzleNum.size ()==0);
}

//Funcation will read in a file, store it, and convert it to an int
vector <int> ReadInFile ()
{
//Declare variables
    ifstream fin ;
    vector <string> storage;
    vector <int> numbers;
    string line;
    string fname;
    cout << "What file do you want to input ";
    cin >> fname;
    fin.open (fname.c_str (), ios_base::in);


//Tries to open the file
    if (!fin.good())
    {
        //Display conditions and so the user have to re-correct the file
        cout << "Can't open the file " << fname;
        exit (1);
    }

//Display message or condition
    cout << "Opened file Successfully" << endl;

//If the file is finished
    do
    {
        //Store each line as a string
        getline (fin,line);
        //Store it in a vector
        storage.push_back (line);
    }
    while (fin.good());

//Close the file opening
    fin.close  ();

//This will check the storage size -ALL of the string gathered
    for (int i=0; i < storage.size (); i++)
    {
        //Checks the individual strings
        for (int x=0; x <= storage [i].length (); x++)
        {
            //If it is number
            if (isdigit (storage [i] [x]))
            {
                //Store that number
                int num = storage [i] [x] - '0';
                //to be a vector
                numbers.push_back(num);
            }
            //If there is letter;
            if (isalpha(storage [i] [x]))
            {
                //Display error
                cout << "NO CHARACTERS PLEASE" << endl;
                //Ask the user to edit the file
                cout << "RE-check your FILES PLEASE" << endl;
                exit (0);
            }
        }
    }

//If the number storage is not equal to 81 then
    if (numbers.size () != 81)
    {
        //Ask the user to re-edit the file
        cout << "Please Re-edit your file" << endl;
        //Make Sure they label "0" as blanks
        cout << "Use '0' as a placeholder for blanks" << endl;
        //Display the total sizes
        cout << "Current Size: " << numbers.size () << endl;
        //Quit the program for the user to edit
        exit (0);
    }

//Return the vector for the data
    return numbers;
}

/* Test Cases:
Generates a puzzle to play with: The user can input the answers and help it solved
//---------------------------------------------------------------------------------------------
How is your day? Do you want a challenge or a Sudoku Solver?
1.) Challenge          2.) Sudoku Solver
1

PUZZLE OF THE DAY:

+------+------+------+
|0 7 5 |0 0 0 |0 0 0 |
|0 4 0 |9 0 1 |5 0 0 |
|0 1 3 |0 8 5 |0 0 0 |
+------+------+------+
|2 0 0 |4 6 7 |0 0 0 |
|0 0 0 |0 0 9 |0 1 7 |
|7 0 0 |0 1 0 |9 0 0 |
+------+------+------+
|3 0 0 |0 0 4 |8 0 0 |
|0 8 0 |7 0 6 |2 0 4 |
|0 0 0 |0 2 0 |6 0 0 |
+------+------+------+
Spot: (0,0)
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
Solve it for you - for this one, I was lazy so I do all 0's and it solved it for me !! :D

Your Submitted Data:
+------+------+------+
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
+------+------+------+
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
+------+------+------+
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
|0 0 0 |0 0 0 |0 0 0 |
+------+------+------+
Answer Key:
+------+------+------+
|6 9 4 |7 2 5 |8 1 3 |
|1 8 7 |6 9 3 |2 4 5 |
|5 2 3 |4 1 8 |7 9 6 |
+------+------+------+
|9 1 2 |8 3 7 |5 6 4 |
|4 7 8 |9 5 6 |1 3 2 |
|3 5 6 |1 4 2 |9 8 7 |
+------+------+------+
|7 3 9 |2 8 4 |6 5 1 |
|8 6 5 |3 7 1 |4 2 9 |
|2 4 1 |5 6 9 |3 7 8 |
+------+------+------+

Process returned 0 (0x0)   execution time : 31.344 s
Press any key to continue.
*/
