// Programmers: Sean Turner, Mohammad Azimi, James Yapnayon, Matthew Allen
// Professor: Davis       Date: 4.25.2021       Project Name: Github Part 2
// This program is one-player game of battleship. Where the computer generates the board and places the ships
// and then the player must guess the ship positions. In the game a '~' character represents ocean,
// a '#' character represents a part of a ship, an 'H' character represents a place where a part of a
// ship has been hit, and a ‘.’ character represents a miss.
// This is a possible second version which added some more functions but creates a board
// completely in static memory instead of using a file.

#include <iostream>
#include <ctime>        // ctime and cstdlib are for the random functions
#include <cstdlib>
#include <limits>       // Mostly used for detecting invalid input

using namespace std;

// Data Structures Needed:
// struct TargetInfo: This lets us keep track of what coordinates we wish to target on the game board
// char boardArray: This lets us keep track of what the game board actually contains
// char playerArray: This lets us keep track of another game board the player sees (to avoid giving away ship locations)
// char arrayRead: This only appears in PrintArray as a way for us to print either of the previous two arrays

// Declare global constants used to represent numbers of rows and columns
const int ROWS = 10;
const int COLS = 10;

// Declare enum type for all the different ships
// CARRIER needs 5 spaces, BATTLESHIP needs 4,
// CRUISER and SUBMARINE need 3, DESTROYER needs 2
enum Ships {CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER};

// Used to pick coordinates when the user wishes to place a target on the board
struct TargetInfo
{
	int row;
	int column;
};

// Sets up both arrays so they only have ocean ('~') spaces
// Pre: boardArray and playerArray have been declared
// Post: boardArray and playerArray have each element filled with '~'
void InitArrays (/*OUT*/ char boardArray [ROWS] [COLS], /*OUT*/ char playerArray [ROWS] [COLS]);

// Sets a location for each of the ships from CARRIER to DESTROYER
// Pre: currShip has a ship declared, direction has 'V' or 'H', both arrays are filled with '~'s
// Post: Local variables randRow and randCol in function contain the first location of the ship,
// local variable shipSize has the proper size for each ship
void SetLocation (/*IN*/ Ships currShip, /*IN*/ char direction, /*IN-OUT*/ char boardArray [ROWS][COLS]);

// Sets the ship horizontally or vertically based on direction, randRow, and randCol values
// Called directly inside of SetLocation
// Pre: Same as SetLocation @entry but randRow and randCol have the first location of the ship,
// shipSize has the number of spaces a ship will take up
// Post: One of 5 ships will be stored in the array while ensuring the ships do not go out of bounds
void SetShip (/*IN*/ char direction, /*OUT*/ char boardArray [ROWS][COLS], /*IN*/ int randRow, /*IN*/ int randCol, /*IN*/ int shipSize);

// Sets up the coordinates needed for changing the two arrays
// Pre: currTarget was declared
// Post: currTarget is assigned coordinates that fall under the two arrays' ranges
void SelectArea (/*IN-OUT*/ TargetInfo& currTarget);

// Checks if coordinates set in the TargetInfo struct contain a '#', '~', 'H' or '.'
// '#' and '~' are replaced with 'H' and '.' respectively for Hit and Miss and numberOfTimes is incremented
// 'H' and '.' lead to a message printed to the screen that says the user already picked there and numberOfTimes is not incremented
// Whatever changes are done to boardArray should be reflected on playerArray so user accurately knows what happened.
// Pre: currTarget's members were set
// Post: Both arrays may or may not be changed, numberOfTries == (numberOfTries@entry || numberOfTries + 1),
// hasWon is based on whether boardArray has any more ship pieces left
void TargetArea (/*IN-OUT*/ char boardArray [ROWS] [COLS], /*IN-OUT*/ char playerArray [ROWS] [COLS], /*IN*/ TargetInfo currTarget, /*OUT*/ int& numberOfTries, /*OUT*/ bool& hasWon);

// Prints the entire board
// Pre: The array passed over has been defined
// Post: The array passed over has been printed
void PrintArray (/*IN-OUT*/ char arrayRead [ROWS] [COLS]);

int main()
{
	// The Declarations - Most of these variables are used in later sections:
		// Set a random seed
		// Declare array used for ship info (This should contain the answers to the game; in other words store '#' where ships are)
		// Declare array that the player sees during the game (This should NOT contain the answers to the game; do not store '#' where ships are)
		// Set up both arrays by assigning '~'s as the water spaces
		// Declare a char direction variable used for horizontal or vertical placements
		// Declare an int variable used to record the number of tries (Player has up to 55 guesses; lets game have a win/lose condition)
		// Declare a char variable used if the user wants to guess again or quit (Could be 'G' for Guess or 'Q' for Quit)
		// Declare a TargetInfo variable that has coordinates for a specific target's row and column
		// Declare a boolean variable that detects if the user won the game

	// Setting up the Array - Most of this was based on my answer back in the Week 11 Discussion Board:
	// Repeat these indented steps 5 times (One iteration per ship)
		// Declare a Ships variable that begins with CARRIER and works its way through the list.
		// Randomly generate a number (0 or 1) that makes the direction variable hold 'H' for Horizontal or 'V' for Vertical
		// Call SetLocation
			// Ideally in SetLocation, we should be grabbing a shipSize based on what I put near Ships' declaration
			// We should also be randomly generating column and row values that keep the ship within the array
				// Check if the ship would ever overlap another element with '#'
				// Keep generating new randRow and randCol values as long as no overlaps occur
		// "Add" the Ships variable using explicit type conversion
	// [Loop iteration would end here]

	// The Game:
	// Repeat these steps as long as the user did not enter G nor Q or the user still has less than 55 turns used
		// Print the player's array
		// Prompt user information about the game like how many turns they used out of 55 or how to (G)uess and (Q)uit
		// Let user enter their decision
		// If they want to (G)uess
			// Let them select the coordinates and assign them to currTarget
			// Compare the coordinates as noted in the function TargetArea
			// If the number of tries equals 55 or the player just found all the ships
				// Use a break statement to exit the loop early
			// Otherwise just print the updated player array
		// Otherwise if they want to (Q)uit
			// Also use a break statement here to exit the loop early
	// [Loop iteration would end here]

	// Perform 1 of 2 sets of output statements based on hasWon's value:
		// If hasWon is true (meaning the player won)
			// Print that the player won and the updated player array
		// If hasWon is false (meaning the player lost)
			// Print that the player lost and the board array (Remember: this is the array that has #s so the player knows where the ships are)

	return 0;
}
