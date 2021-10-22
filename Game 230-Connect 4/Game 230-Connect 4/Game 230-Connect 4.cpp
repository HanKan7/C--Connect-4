// Game 230-Connect 4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game 230-Connect 4.h"
using namespace std;

const int numberOfRows = 7;
const int numberOfColumns = 7;
int restartValue = 0;
bool playerTurnHasEnded = true;
bool gameHasEnded = false;


int** InitialiseArrayWithZeroes() {
    cout << "Initialising with Zeroes\n\n";
    int** array = new int* [numberOfColumns];
    for (int i = 0; i < numberOfColumns; i++) {
        array[i] = new int[numberOfRows];
        for (int j = 0; j < numberOfRows; j++) {
            array[i][j] = 0;
        }
    }
    return array;
}

void DisplayElementsInArray(int** array)
{
    cout << "Displaying elements in the array\n" << endl;

    for (int i = 0; i < numberOfColumns; i++) {
        cout << "  |  "<<i;
    }
    cout << "  |\n-----------------------------------------------";

    for (int i = 0; i < numberOfColumns; i++)
    {
        cout << "\n  |  ";
        for (int j = 0; j < numberOfRows; j++)
        {
            cout << array[i][j] << "  |  ";
        }

        cout << endl;
    }


}

int** InsertElement(int** array, int columnNumber, int whoseTurnItIs) 
{
    cout << "Inserting Element in the array\n\n";

    for (int i = numberOfRows - 1; i >= 0; i--) 
    {
        if (array[0][columnNumber] == 1 || array[0][columnNumber] == 2) 
        {
            cout << "Column is filled with numbers. Please select other column number\n\n";
            playerTurnHasEnded = false;
            return array;
        }
        if (array[i][columnNumber] == 1 || array[i][columnNumber] == 2)  continue; //if the slot is already taken, continue  
        array[i][columnNumber] = whoseTurnItIs;
        playerTurnHasEnded = true;
        return array;
    }
    return array;
}

bool FindWinner(int** array, int whoseTurnItIs) 
{
    //Calculate Horizontally

    for (int i = 0; i < numberOfColumns; i++) 
    {
        for (int j = 0; j < numberOfRows; j++) 
        {
            //cout << "For Loop inside i = " << i << " j =  " << j << endl;
            if ((i + 3) < numberOfColumns && array[i][j] == whoseTurnItIs && array[i + 1][j] == whoseTurnItIs && array[i + 2][j] == whoseTurnItIs && array[i + 3][j] == whoseTurnItIs) 
            {
                //cout << "First condition " + i << " " << j<<endl;
                return FoundWinnerRestartGame(whoseTurnItIs);
            }

            if ((j+3) < numberOfRows && array[i][j] == whoseTurnItIs && array[i][j + 1] == whoseTurnItIs && array[i][j + 2] == whoseTurnItIs && array[i][j + 3] == whoseTurnItIs) 
            {
                //cout << "Second condition " + i << " " << j << endl;
                return FoundWinnerRestartGame(whoseTurnItIs);
            }

            if ((i + 3) < numberOfColumns && (j+3) < numberOfRows && array[i][j] == whoseTurnItIs && array[i + 1][j + 1] == whoseTurnItIs && array[i + 2][j + 2] == whoseTurnItIs && array[i + 3][j + 3] == whoseTurnItIs) 
            {
                //cout << "Third " + i << " " << j << endl;
                return FoundWinnerRestartGame(whoseTurnItIs);
            }

            if((i + 3) < numberOfColumns && (j - 1) < numberOfRows && array[i][j] == whoseTurnItIs && array[i + 1][j - 1] == whoseTurnItIs && array[i + 2][j - 2] == whoseTurnItIs && array[i + 3][j - 3] == whoseTurnItIs)
            {
                //cout << "Fourth " + i << " " << j << endl;
                return FoundWinnerRestartGame(whoseTurnItIs);
            }
        }
    }
    return false;
}

bool FoundWinnerRestartGame(int whoseTurnItIs)
{
    cout << "\n\nPlayer " << whoseTurnItIs << " is the WINNER!";
    cout << "\nDo you want to restart the game? Enter 1 to restart and 0 to end the game \n";

    cin >> restartValue;
    if (restartValue > 0)
    {
        gameHasEnded = false;
        return false;
    }
    else
    {
        gameHasEnded = true;
    }
    return true;
}

/*bool IsWinner(int** array, int whoseTurnItIs) {
    int count = 0;

    //Horizontal
        for (int i = numberOfRows - 1; i >= 0; i--) {

            for (int j = 0; j < numberOfColumns; j++)
            {
                if (array[i][j] == whoseTurnItIs) {
                    count++;
                }

                if (count == 4) {
                    return true;
                }
            }

            count = 0;
            
        }

      //Vertical
        for (int i = 0; i < numberOfColumns; i++) {
            for (int j = numberOfRows - 1; j >= 0; j--) {
                if (array[i][j] == whoseTurnItIs) {
                    count++;
                }

                if (count == 4) {
                    return true;
                }
            }
            count = 0;
        }

    //Diagonol up 
        int i = numberOfColumns - 1, j = numberOfRows - 1;
        int diagonolCount = 1;
        int IDiag = 1, JDiag = numberOfRows - 1;
        while (!(i == 0 && j == 0)) 
        {
                        //6                       //6              //6 + 1 <= 7                 //6 - 6 == 0
            for (i = numberOfColumns - IDiag, j = numberOfRows - 1; (i + IDiag <= numberOfColumns && j - JDiag == 0); i++, j--) {
                if (array[i][j] == whoseTurnItIs) {
                    count++;
                }

                if (count == 4) {
                    return true;
                }
            }
            count = 0;
            IDiag++;
            JDiag--;
            i = numberOfColumns - IDiag;
            j = numberOfRows + JDiag;
            
            
        } 
        return true;
}*/

int main()
{
    int getColumnNumber = 0;
    int playerOneTurn = 1, playerTwoTurn = 2, whoseTurnItIs = 1;

    int** connect4Board = InitialiseArrayWithZeroes();

    DisplayElementsInArray(connect4Board);

    while (!gameHasEnded)
    {
        cout << "\nPlayer "<< whoseTurnItIs << " Please select the column where you want to enter the element\n";
        cin >> getColumnNumber;
        if (getColumnNumber < 0 || getColumnNumber >= numberOfColumns) 
        {
            cout << "\n Please Enter a valid number\n";
            continue;
        }
        connect4Board = InsertElement(connect4Board, getColumnNumber, whoseTurnItIs);
        if (!playerTurnHasEnded) continue;
        DisplayElementsInArray(connect4Board);
        FindWinner(connect4Board, whoseTurnItIs);
        if (restartValue > 0) 
        {
            restartValue = 0;
            connect4Board = InitialiseArrayWithZeroes();
            DisplayElementsInArray(connect4Board);
            playerTurnHasEnded = true;
            continue;
        }

        if(whoseTurnItIs == 1)  whoseTurnItIs = 2;
        else
        {
            whoseTurnItIs = 1;
        }
        playerTurnHasEnded = true;
    } 
}

