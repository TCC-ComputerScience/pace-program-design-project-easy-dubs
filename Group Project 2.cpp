// Programmers: Sean Turner, Mohammad Azimi, James Yapnayon, Matthew Allen
// Professor: Davis       Date: 5.2.2021       Project Name: Group Project 2
// Modified variant of another group's pseudocode that has InitBoard and Fire coded
// Other functions are currently stubs as requested and a debug function was made to show both arrays

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>      // If this group wants boards randomized, we need to include their proper header files
#include <ctime>        // If this group wants boards randomized, we need to include their proper header files

using namespace std;

const int MAX_SIZE =10;

struct BoardType
{
  char boardSize[MAX_SIZE][MAX_SIZE];        // The data type must be char since we need to hold symbols, not integers
  char guess[MAX_SIZE][MAX_SIZE];            // The data type must be char since we need to hold symbols, not integers
  char ocean = '~';
  char ship = '#';
  char shipHit = 'H';
  char miss = '.';
};

//Pre: board contains information from struct BoardType
//Post: randomnize a board mixed with ~ for ocean and "#" for ship
void InitBoard(BoardType &board);

//Pre: board contains a 10x10 grid
//Post: user will guess a hit and row and col
void Fire(BoardType &board, int &row, int &col);

//Pre: board contains a 10X10 grid
  //row and col contain information from user
//Post: will determine if row and col contain ship or ocean
bool isHit(BoardType &board, int row, int col);

//Pre: board contains grid
  //row and col contain ship or ocean and guess from user
//Post: if all ship is hit then sunk is true
bool isSunk(BoardType &board, int row, int col);

// Debug function used to show the array did print correctly
void PrintArray (/*IN-OUT*/ char arrayRead [MAX_SIZE] [MAX_SIZE]);

int main ()
{
    // Declares variables
    BoardType board;
    int row, col;

    // Set up the boards and random seed
    srand(time(NULL));
    InitBoard (board);
    PrintArray (board.boardSize);
    cout << endl << endl;
    PrintArray (board.guess);

    // Allow the user to fire. In a final build, this should be called repeatedly until isSunk returns true
    Fire (board, row, col);



return 0;
}
//**********************************************************************
void InitBoard(BoardType &board)
{
    // The original comments here leave plenty of freedom for us to set the array as we please as long as
    // it "goes through row", "goes through col", and then "produces either ship or ocean"

    // One major problem compared to the Easy Dubs version is that if we followed the rules of this program,
    // 3 of our functions would be merged together to create a giant function (InitArrays, SetLocation, SetShip)

    // To strive for staying as close to the original requests as we can,
    // everything is split into three parts with stars like shown below for readability
    // ********************************************************************

    // Initializing Array
// ********************************************************************
    // Declarations
    char direction;     // Used to indicate a ship direction
    int randRow;        // Two numbers meant to hold randomized ship locations
    int randCol;
    int shipSize;       // Used to hold the size of a ship
    bool isOverlapped;  // Used to check if a ship overlapped with another one
    struct shipType     // Struct type for all the different ships and make them hold their sizes
    {
        const int CARRIER = 5;
        const int BATTLESHIP = 4;
        const int CRUISER = 3;
        const int SUBMARINE = 3;
        const int DESTROYER = 2;
    };
    shipType currentShip;   // Contains a copy of each constant member to read off of

    // Set the arrays with just water
    for (int i = 0; i < MAX_SIZE; i++)
        for (int j = 0; j < MAX_SIZE; j++)
        {
            board.boardSize [i] [j] = board.ocean;
            board.guess [i] [j] = board.ocean;
        }

    // Setting Location
// ********************************************************************
    // Place random ship locations
    for (int shipCount = 0; shipCount < 5; shipCount++)
    {
        // Used to assign the ship size so a valid number of spaces are occupied
        switch (shipCount)
        {
            case 0:             shipSize = currentShip.CARRIER;
                                break;
            case 1:             shipSize = currentShip.BATTLESHIP;
                                break;
            case 2:             shipSize = currentShip.CRUISER;
                                break;
            case 3:             shipSize = currentShip.SUBMARINE;
                                break;
            case 4:             shipSize = currentShip.DESTROYER;
                                break;
        }

        // Used for placing a ship horizontally or vertically
        if (rand() % 2 == 0)
            direction = 'H';
        else
            direction = 'V';

        // Find a location that is not overlapping or out of bounds
        if (direction == 'H')   // Direction is horizontal
            {
                // Keep finding locations until one appears that does not overlap a ship
                do
                {
                    isOverlapped = false; // Set isOverlapped to false

                    // Make sure going horizontally does not go out of bounds
                    // Condition's last part is to ensure the entire ship appears on the board
                    do
                    {
                        randRow = rand() % MAX_SIZE;
                        randCol = rand() % MAX_SIZE - shipSize;     // Subtract by shipSize to make sure enough space is made horizontally
                    } while (randCol < 0 || randCol > 9 || (randRow + shipSize) > 9);

                    // Check if ship overlapped with another one
                    for (int i = randCol; i < (randCol + shipSize); i++)
                        if (board.boardSize [randRow] [i] == board.ship)
                            isOverlapped = true;

                } while (isOverlapped);
            }
        else if (direction == 'V')   // Direction is vertical
            {
                // Keep finding locations until one appears that does not overlap a ship
                do
                {
                    isOverlapped = false;     // Set isOverlapped to false

                    // Make sure going vertically does not go out of bounds
                    // Condition's last part is to ensure the entire ship appears on the board
                    do
                    {
                        randCol = rand() % MAX_SIZE;
                        randRow = rand() % MAX_SIZE - shipSize; // Subtract by shipSize to make sure enough space is made vertically
                    } while (randRow < 0 || randRow > 9 || (randCol + shipSize) > 9);

                    // Check if ship overlapped with another one
                    for (int i = randRow; i < (randRow + shipSize); i++)
                        if (board.boardSize [i] [randCol] == board.ship)
                            isOverlapped = true;

                }  while (isOverlapped);
            }

        // Setting Ships
// ********************************************************************
        // Place ships by storing elements with '#' or board.ship
        if (direction == 'H')
            for (int i = randCol; i < (randCol + shipSize); i++)
                board.boardSize [randRow] [i] = board.ship;
        else if (direction == 'V')
            for (int i = randRow; i < (randRow + shipSize); i++)
                board.boardSize [i] [randCol] = board.ship;

    }

  // Original Comments:
  //goes through row
    //goes through col
      //produces either ship or ocean
}
//********************************************************************
void Fire(BoardType &board, int &row, int &col)
{
    // Prompts user for coordinates
    cout << "Enter coordinates of ship, separated by a space ";
    cin >> row;
    cin >> col;

    // Make sure the numbers are in a valid range (Simple error check, but could also use Easy Dubs' version)
    // Numbers out of bounds are reassigned to 0
    if (row > 9 || row < 0)
        row = 0;
    if (col > 9 || col < 0)
        col = 0;

    // Update the guess array by assigning its current row and column a ship ('#')
    // Seems like they want us to compare the element with boardSize's then reassign to 'H' or '.' based on result in isHit
    board.guess [row] [col] = board.ship;
    PrintArray (board.guess);    // Stub call used to show that '#' was made; should be gone in a final build

    // Original Comments:
    //goes through row
        //goes through col
            //updates to guess array
}
//***************************************************************************
bool isHit(BoardType &board, int row, int col)
{
    // Stub call
    cout << "Calling isHit" << endl;

    //if guess[row][col] == boardSize[row][col]
        //return true;

//else
return false;
}

//***************************************************************************
bool isSunk(BoardType &board, int row, int col)
{
    cout << "Calling isSunk" << endl;
// if isHit is true and all ship is destroyed, then
  //return true;
//else
return false;
}

void PrintArray (/*IN-OUT*/ char arrayRead [MAX_SIZE] [MAX_SIZE])
{
    // Prints out the rows and columns for the game
    cout << "  ";
    for (int i = 0; i <= 9; i++)
    {
        cout << i << " ";
        if (i == 9)
            cout << endl;
    }

    // Prints either '~' or '#' for now
    for (int i = 0; i < MAX_SIZE; i++)
    {
        cout << i << " ";
        for (int j = 0; j < MAX_SIZE; j++)
            cout << arrayRead [i] [j] << " ";
        cout << endl;
    }

    cout << endl;

    return;
}

