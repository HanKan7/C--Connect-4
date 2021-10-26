#include <iostream>
#include <stdlib.h>
//#include "main.h"
using namespace std;

int numberOfRows = 7;
int numberOfColumns = 6;
int winCondition = 4;

int numberOfTurns = 0;
bool playerTurnHasEnded = true;
bool gameHasEnded = false;


int restartValue = 0;
int enableWrapFunction = 0;
int enableRemoveFunction = 0;
int enableAi = 0;

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
        cout << "  |  " << i;
    }
    cout << "  |\n";
    for (int i = 0; i < numberOfColumns * 7; i++) {
        cout << "_";
    }
    cout << "\n";
    for (int i = 0; i < numberOfColumns * 7; i++) {
        cout << "_";
    }

    for (int i = 0; i < numberOfRows; i++)
    {
        cout << "\n  |  ";
        for (int j = 0; j < numberOfColumns; j++)
        {
            if (j < 10) {
                cout << array[j][i] << "  |  ";
            }
            else {
                cout << array[j][i] << "   |  ";
            }

        }

        cout << endl;
    }
}

int** InsertElement(int** array, int columnNumber, int whoseTurnItIs)
{
    cout << "Inserting Element in the array\n\n";

    for (int i = numberOfRows - 1; i >= 0; i--)
    {
        if (array[columnNumber][0] == 1 || array[columnNumber][0] == 2)
        {
            cout << "Column is filled with numbers. Please select other column number\n\n";
            playerTurnHasEnded = false;
            return array;
        }
        if (array[columnNumber][i] == 1 || array[columnNumber][i] == 2)  continue; //if the slot is already taken, continue  
        array[columnNumber][i] = whoseTurnItIs;
        playerTurnHasEnded = true;
        return array;
    }
    return array;
}

int** RemoveElement(int** array, int columnNumber, int whoseTurnItIs)
{
    cout << "Removing the element from the column\n";

    for (int j = numberOfRows - 1; j >= 0; j--)
    {
        if (j == 0)
        {
            array[columnNumber][j] = 0;
            break;
        }

        if (array[columnNumber][j - 1] == 0)
        {
            array[columnNumber][j] = 0;
            break;
        }

        array[columnNumber][j] = array[columnNumber][j - 1];
    }

    return array;
}

void ChangePlayerTurn(int& whoseTurnItIs)
{
    if (whoseTurnItIs == 1)  whoseTurnItIs = 2;
    else
    {
        whoseTurnItIs = 1;
    }
}

bool WinnerFoundShallWeRestartGame(bool winnerFound, int whoseTurnItIs)
{
    if (winnerFound)
    {
        cout << "\n\nPlayer " << whoseTurnItIs << " is the WINNER!";
        cout << "\nDo you want to restart the game? Enter 1 to restart and 0 to end the game \n";

        cin >> restartValue;
        if (restartValue == 1)
        {
            numberOfTurns = 0;
            gameHasEnded = false;
            return false;
        }
        else if (restartValue == 0)
        {
            gameHasEnded = true;
            return true;
        }
    }
}

bool FindWinner(int** array, int whoseTurnItIs)
{
    int count = 0;

    //Check Win Condition For Horizontal Direction//////////////////
    for (int i = numberOfRows - 1; i >= 0; i--)
    {
        for (int j = 0; j < numberOfColumns; j++) {
            if (array[j][i] == whoseTurnItIs) {
                count++;
            }
            else
            {
                count = 0;
            }

            if (count == winCondition)
            {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        count = 0;
    }

    //Check Win Condition For Vertical Direction////////////////
    for (int i = 0; i < numberOfColumns; i++)
    {
        for (int j = 0; j < numberOfRows; j++) {
            if (array[i][j] == whoseTurnItIs) {
                count++;
            }
            else
            {
                count = 0;
            }

            if (count == winCondition)
            {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        count = 0;
    }

    //Left to Right Diagnol Upwards///////////////////////

    int i = 0;
    int j = winCondition - 1; // 3
    int loopCount = 0;

    while (j <= numberOfColumns) {
        for (; (i <= numberOfColumns - 1) && (j >= 0); i++, j--)
        {
            if (array[i][j] == whoseTurnItIs) {
                count++;
            }

            else
            {
                count = 0;
            }

            if (count == winCondition) {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        loopCount++;
        j = winCondition - 1 + loopCount;
        i = 0;
    }

    i = 1;
    j = numberOfRows - 1;
    loopCount = 0;
    while (i <= winCondition - 1) {
        for (; (i <= numberOfColumns - 1); i++, j--) {
            if (array[i][j] == whoseTurnItIs) {
                count++;
            }

            else
            {
                count = 0;
            }

            if (count == winCondition) {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        loopCount++;
        j = numberOfRows - 1;
        i = i - i + loopCount + 1;
    }

    /////Right To Left Upwards//////////////////////
    i = numberOfColumns - 1;
    j = winCondition - 1;
    loopCount = 0;
    while (j <= numberOfColumns) {
        for (; (i >= 0) && (j >= 0); i--, j--) {
            if (array[i][j] == whoseTurnItIs) {
                count++;
            }

            else
            {
                count = 0;
            }

            if (count == winCondition) {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        loopCount++;
        i = 5;
        j = winCondition - 1 + loopCount;
    }

    i = numberOfColumns - 2;
    j = numberOfRows - 1;
    loopCount = 0;
    while (i >= winCondition - 1) {
        for (; i >= 0; i--, j--) {
            if (array[i][j] == whoseTurnItIs) {
                count++;
            }

            else
            {
                count = 0;
            }

            if (count == winCondition) {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        j = numberOfRows - 1;
        loopCount++;
        i = i + numberOfColumns - 1 - loopCount;
    }

    int k = numberOfColumns - 1;
    bool firstLoop = false;
    bool firstorLastElementsAreZeroes = false;
    bool firstAndLastElementsAreSame = false;
    //Wrap Condition////////////
    if (enableWrapFunction == 1)
    {
        for (i = numberOfRows - 1; i >= 0; i--)
        {
            for (j = 0; j < numberOfColumns; j++)
            {
                //cout <<"\narray[j][i] = " <<array[j][i] << "\narray[k][i] = " << array[k][i];

                if (!firstLoop) {
                    if ((array[j][i] == 0 || array[k][i] == 0) && !firstorLastElementsAreZeroes)
                    {
                        firstorLastElementsAreZeroes = true;
                        break;
                    }
                    if ((array[j][i] != array[k][i]) && !firstAndLastElementsAreSame) {
                        firstAndLastElementsAreSame = true;
                        break;
                    }
                    if ((array[j][i] == whoseTurnItIs && array[k][i] != whoseTurnItIs) || (array[j][i] != whoseTurnItIs && array[k][i] == whoseTurnItIs)) {
                        count = 0;
                        break;
                    }
                    firstLoop = true;
                }

                //2 1 2 1 0 2

                if (array[j][i] != whoseTurnItIs && array[k][i] != whoseTurnItIs) {
                    count = 0;
                    break;
                }


                //1 1 2 2 0 1

                if (array[j][i] == whoseTurnItIs) {
                    count++;
                }
                if (array[k][i] == whoseTurnItIs) {
                    count++;
                }
                //Win Condition
                if (count == winCondition) {
                    return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
                }

                if ((array[j][i] != whoseTurnItIs && array[k][i] == whoseTurnItIs) || (array[j][i] == whoseTurnItIs && array[k][i] != whoseTurnItIs))
                {
                    count++;
                }

                //Win Condition
                if (count == winCondition) {
                    return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
                }



                k--;
            }
            firstLoop = false;
            firstorLastElementsAreZeroes = false;
            firstAndLastElementsAreSame = false;
            k = numberOfColumns - 1;
        }
    }


}

bool AI(int** array, int whoseTurnItIs) {
    int playerCount = 0;
    int aiCount = 0;

    //Check Win Condition For Horizontal Direction//////////////////
    for (int i = numberOfRows - 1; i >= 0; i--)
    {
        for (int j = 0; j < numberOfColumns; j++) {
            if (array[j][i] == 1) {
                playerCount++;
            }
            else
            {
                playerCount = 0;
            }

            if (playerCount == winCondition - 1)
            {
                if (array[j + 1][i] == 0)
                {
                    array[j + 1][i] = 2;
                    return array;
                }
                else if (array[j - 2][i] == 0)
                {
                    array[j - 2][i] = 2;
                }
            }

            if (array[j][i] == 2) {
                aiCount++;
            }
            else
            {
                aiCount = 0;
            }

            if (aiCount == winCondition - 1) {
                if (array[j + 1][i] == 0)
                {
                    array[j + 1][i] = 2;
                    return array;
                }
                else if (array[j - 2][i] == 0)
                {
                    array[j - 2][i] = 2;
                }
                else
                {
                    int value = rand() % numberOfColumns;
                    InsertElement(array, value, whoseTurnItIs);
                }
            }
        }
        playerCount = 0;
    }

    //Check Win Condition For Vertical Direction////////////////
    for (int i = 0; i < numberOfColumns; i++)
    {
        for (int j = 0; j < numberOfRows; j++) {
            if (array[i][j] == whoseTurnItIs) {
                playerCount++;
            }
            else
            {
                playerCount = 0;
            }

            if (playerCount == winCondition)
            {
                return WinnerFoundShallWeRestartGame(true, whoseTurnItIs);
            }
        }
        playerCount = 0;
    }
}



int main()
{
    int getColumnNumber = 0;
    int insertOrRemove = 0;
    int whoseTurnItIs = 1;
    bool playerEnteredAllTheInputs = false;

    while (!playerEnteredAllTheInputs)
    {
        /*cout << "Do you want to enable AI function? Press 1 to select YES, 0 to select NO\n";
        cin >> enableAi;
        if (enableAi != 0 && enableAi != 1) {
            cout << "Please enter a valid number\n";
            continue;
        }

        if (enableAi == 1) {
            numberOfColumns = 6;
            numberOfRows = 7;
            winCondition = 4;
            playerEnteredAllTheInputs = true;
            break;
        }*/

        cout << "Enter the number of columns. Make sure the value is between 4 and 20 \n";
        cin >> numberOfColumns;


        cout << "Enter the number of rows. Make sure the value is between 4 and 20 \n";
        cin >> numberOfRows;
        if (numberOfColumns < 4 || numberOfColumns > 20 || numberOfRows < 4 || numberOfRows > 20)
        {
            cout << "Please enter the number of rows and columns between the numbers 4 and 20 \n";
            continue;
        }

        cout << "Enter the win condition\n";
        cin >> winCondition;
        if ((winCondition < 3 || winCondition > 20)) {
            cout << "Please enter the valid win condition between 3 and 20\n";
            continue;
        }

        cout << "Do you want to enable wrap function? Press 1 to select YES, 0 to select NO\n";
        cin >> enableWrapFunction;
        if (enableWrapFunction != 0 && enableWrapFunction != 1) {
            cout << "Please enter a valid number\n";
            continue;
        }

        cout << "Do you want to enable remove function? Press 1 to select YES, 0 to select NO\n";
        cin >> enableRemoveFunction;
        if (enableRemoveFunction != 0 && enableRemoveFunction != 1) {
            cout << "Please enter a valid number\n";
            continue;
        }
        playerEnteredAllTheInputs = true;
    }


    int** connect4Board = InitialiseArrayWithZeroes();

    DisplayElementsInArray(connect4Board);

    while (!gameHasEnded)
    {



        if (enableRemoveFunction == 1) //Remove Enabled
        {
            cout << "\nPlayer " << whoseTurnItIs << " Please select if you want to INSERT or REMOVE element. Press 1 for INSERT, 2 for REMOVE\n";
            cin >> insertOrRemove;
            if (insertOrRemove != 1 && insertOrRemove != 2) {
                cout << "Please enter a valid number\n";
                continue;
            }
            if (insertOrRemove == 2) //Remove Function
            {
                cout << "\nPlayer " << whoseTurnItIs << " Please select the column where you want to remove your element. You can only remove your bottom row elements\n";
                cin >> getColumnNumber;
                //cout << "Bottom element = " << connect4Board[getColumnNumber][0] << "WT " << whoseTurnItIs<<endl;
                if (connect4Board[getColumnNumber][numberOfRows - 1] != whoseTurnItIs)
                {
                    cout << "Please enter a valid number\n";
                    continue;
                }
                connect4Board = RemoveElement(connect4Board, getColumnNumber, whoseTurnItIs);
            }
            else if (insertOrRemove == 1) {

                cout << "\nPlayer " << whoseTurnItIs << " Please select the column where you want to enter the element\n";
                cin >> getColumnNumber;
                if (getColumnNumber < 0 || getColumnNumber >= numberOfColumns)
                {
                    cout << "\nPlease Enter a valid number\n";
                    continue;
                }
                connect4Board = InsertElement(connect4Board, getColumnNumber, whoseTurnItIs);
            }
        }
        else if (enableRemoveFunction == 0) //Remove function disabled
        {
            cout << "\nPlayer " << whoseTurnItIs << " Please select the column where you want to insert the element\n";
            cin >> getColumnNumber;
            if (getColumnNumber < 0 || getColumnNumber >= numberOfColumns)
            {
                cout << "\nPlease Enter a valid number\n";
                continue;
            }
            connect4Board = InsertElement(connect4Board, getColumnNumber, whoseTurnItIs);
        }

        if (!playerTurnHasEnded) continue;  //Checking if player entered correct column number
        DisplayElementsInArray(connect4Board);


        numberOfTurns++;
        if (numberOfTurns >= winCondition * 2 - 1)
        {
            //Check Win
            bool isWinner = FindWinner(connect4Board, whoseTurnItIs);

            //Draw Condition
            if (numberOfTurns == numberOfColumns * numberOfRows)
            {
                cout << "Game has tied. Do you want to restart the game? Enter 1 to restart and 0 to end the game \n ";
                cin >> restartValue;
                if (restartValue > 0)
                {
                    restartValue = 0;
                    numberOfTurns = 0;
                    connect4Board = InitialiseArrayWithZeroes();
                    DisplayElementsInArray(connect4Board);
                    playerTurnHasEnded = true;
                    continue;
                }
                else
                {
                    break;
                }

            }

        }



        //If Match is to be restarted
        if (restartValue > 0)
        {
            restartValue = 0;
            connect4Board = InitialiseArrayWithZeroes();
            DisplayElementsInArray(connect4Board);
            playerTurnHasEnded = true;
            continue;
        }


        //Changing Turns
        ChangePlayerTurn(whoseTurnItIs);
        playerTurnHasEnded = true;
    }

}
