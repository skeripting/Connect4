/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Title: Connect4.cpp
    Course: Computational Problem Solving I (CPET-121)
    Developer: Kushal Timsina
    Date: 10/30/2020-11/2/2020
    Description: A fun 2-Player Connect 4 game. 
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <ctime>
#include <stdlib.h>

using namespace std;

/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: DebugError
    Input: a string variable called errorString
    Output: None
    Purpose: Used internally to debug errors that rise in the code.
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void DebugError(string errorString) {
    cout << "ERROR: " << errorString << endl;
}

/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: SelectError
    Input: None
    Output: (1) int variable
    Purpose: Used to randomly select a player.
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/

int SelectPlayer() {
    int selectedPlayerN = rand() % 2 + 1;
    if (selectedPlayerN > 2 || selectedPlayerN < 1) {
        DebugError("Program selected a player number > 2 or < 1.");
    }
    cout << "Player #" << selectedPlayerN << " was selected to go first." << endl;
    return selectedPlayerN;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: DisplayWelcomeScreen
    Input: None
    Output: None
    Purpose: Used to display the welcome screen that the players see upon first opening the app.
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void DisplayWelcomeScreen() {
    string borderDecoration = string(100, '=');
    cout << borderDecoration << endl;
    cout << "Welcome to Connect 4!" << endl;
    cout << "The goal of this 2 player game of Connect 4 is to be the first player to place 4 checkers in a row." << endl;
    cout << "This can be done either horizontally, vertically, or diagonally." << endl;
    cout << borderDecoration << endl;
    cout << endl << endl;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: DisplayBoard
    Input: A multidimensional vector filled with another vector that consists of chars. (Column-Row system)
    Output: None
    Purpose: Used to display the game board. 
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void DisplayBoard(vector < vector < char >> gameData) {
    const unsigned int NUM_COLUMNS = gameData.size() - 1;
    const unsigned int WIDTH = gameData.at(1).size();
    const char GRID_COLUMN_SEPARATOR = '+';
    const char GRID_FILL = '-';
    const char COLUMN_SEPARATOR = '|';
    const int SETWIDTH = 2;
    string gridFiller = string(WIDTH - 1, GRID_FILL);
    cout << setw(SETWIDTH);
    for (int i = 1; i <= NUM_COLUMNS; ++i) { //Numbers up top
        cout << setw(WIDTH) << i;
    }
    for (int x = 0; x < WIDTH; ++x) {
        cout << endl;
        cout << setw(SETWIDTH);
        for (int i = 1; i <= NUM_COLUMNS; ++i) { //Checkers
            cout << COLUMN_SEPARATOR << setw(WIDTH - 1);
            if (i <= NUM_COLUMNS) {
                cout << gameData.at(i).at(x);
            }
        }
        cout << "" << COLUMN_SEPARATOR << setw(WIDTH - 1);
        cout << endl;
        cout << setw(0) << " ";
        for (int i = 1; i <= NUM_COLUMNS; ++i) {
            cout << GRID_COLUMN_SEPARATOR << gridFiller;
        }
        cout << GRID_COLUMN_SEPARATOR;
    }
    cout << endl;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: GetFreeSlot
    Input: (2) variable of type int representing the column to search, the multidimensional vector representing the columns and rows of the game.
    Output: None
    Purpose: Used to display the game board.
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
int GetFreeSlot(int desiredColumn, vector < vector < char >> gameData) {
    int rowToReturn = 0;
    const int TOP_ROW_ERROR = 404;
    for (int r = 0; r < gameData.at(desiredColumn).size(); ++r) {
        char currentRow = gameData.at(desiredColumn).at(r);
        int previousRowInt = r - 1;
        if (currentRow != ' ') {
            if (previousRowInt < 0) {
                rowToReturn = TOP_ROW_ERROR;
                break;
            }
            rowToReturn = previousRowInt;
            break;
        }
        if (r == gameData.at(desiredColumn).size() - 1) {
            rowToReturn = r;
            break;
        }
    }
    return rowToReturn;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: GetChecker
    Input: (1) int variable representing the player (either 1 or 2)
    Output: None
    Purpose: Used to convert the player to a checker. Not literally. It converts the integer that represents the player to a char representing their checker.
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
char GetChecker(int currentPlayer) {
    if (currentPlayer == 1) {
        return 'X';
    }
    else if (currentPlayer == 2) {
        return 'O';
    }
    return ' ';
}

/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: GetCheckerInt
    Input: (1) char variable representing the player's checker. 
    Output: int, returns the player (either 1 or 2)
    Purpose: Inverse of GetChecker. Returns the player given their checker.
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
char GetCheckerInt(char checkerChar) {
    if (checkerChar == 'X') {
        return 1;
    }
    else if (checkerChar == 'O') {
        return 2;
    }
    return 0;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: AddChecker
    Input: (3) int variable, int variable, the multidimensional vector representing the gameData
    Output: A string representing the response (whether it was successful)
    Purpose: Adds a checker to the board. 
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
string AddChecker(int currentPlayer, int desiredColumn, vector < vector < char >>& gameData) {
    char checkerChar;
    string functionResponse = "";
    checkerChar = GetChecker(currentPlayer);
    int freeSlot = GetFreeSlot(desiredColumn, gameData); //errors here
    if (freeSlot == 404) { //Error: The player tried to add a checker onto the top row, which was already filled
        functionResponse = "unavailable";
    }
    else {
        gameData.at(desiredColumn).at(freeSlot) = checkerChar;
    }
    return functionResponse;
}

/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: WinMethodToString
    Input: (1) int variable
    Output: A string representing how the winner won the game. 
    Purpose: Takes an integer and outputs the method that the winner used to win.
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
string WinMethodToString(int winMethod) {
    string winMethodString;
    if (winMethod == 0) {
        winMethodString = "No winner.";
    }
    else if (winMethod == 1)
    {
        winMethodString = "The game ended in a tie.";
    }
    else if (winMethod == 2) {
        winMethodString = "The winner won the game by placing 4 checkers consecutively vertically.";
    }
    else if (winMethod == 3) {
        winMethodString = "The winner won the game by placing 4 checkers consecutively horizontally.";
    }
    else if (winMethod == 4) {
        winMethodString = "The winner won the game by placing 4 checkers consecutively diagonally.";
    }
    return winMethodString;
}

/*
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: CheckWinner
    Input: (1) multidimensional vector representing the game data.
    Output: An integer vector representing who won and how they won.
    Purpose: Takes the gameData, checks to see if there's a won, and spits out the winner and how they won.
    +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
vector<int> CheckWinner(vector < vector < char >> gameData) {
    /*
        Returns:
        [0]
            0 - No winner
            1 - Player 1 won
            2 - Player 2 won
            3 - The game ended in a tie.
        [1]
            0 - No winner 
            1 - The game ended in a tie.
            2 - The game ended in such a way where a player won vertically
            3 - The game ended in such a way where a player won horizontally
            4 - The game ended in such a way where a player won diagonally 
    */
    int winnerFound = 0;
    const int WINNER_CONSIDERATION_VALUE = 4;
    int totalCheckerCount = 0; 
    //Vertical
    for (int c = 0; c < gameData.size(); ++c) {
        vector < char > currentColumn = gameData.at(c);
        char currentChecker = '?';
        int consecutiveCheckerCount = 0;
        for (int r = 0; r < currentColumn.size(); ++r) {
            char currentRow = currentColumn.at(r);
            if (currentRow != ' ') {
                totalCheckerCount++;
            }
            if ((currentRow == currentChecker) && (currentRow != ' ')) {
                consecutiveCheckerCount++;
            }
            else {
                consecutiveCheckerCount = 1;
            }
            currentChecker = currentRow;
            if (consecutiveCheckerCount == WINNER_CONSIDERATION_VALUE) {
                winnerFound = GetCheckerInt(currentChecker);
                return vector<int>{ winnerFound, 2 };
            }
        }
    }
    //Horizontal
    char currentChecker = '?';
    int consecutiveCheckerCount = 0;
    for (int i = 0; i < gameData.at(0).size(); ++i) {
        for (int c = 0; c < gameData.size(); ++c) {
            char currentColumn = gameData.at(c).at(i);
            if ((currentColumn == currentChecker) && (currentColumn != ' ')) {
                consecutiveCheckerCount++;
            }
            else {
                consecutiveCheckerCount = 1;
            }
            currentChecker = currentColumn;
            if (consecutiveCheckerCount == WINNER_CONSIDERATION_VALUE) {
                winnerFound = GetCheckerInt(currentChecker);
                return vector<int>{ winnerFound, 3 };
            }
        }
    }
    //Diagonal (TopLeft-BottomRight)
    for (int c = 0; c < gameData.size(); ++c) {
        vector < char > currentColumn = gameData.at(c);
        char currentChecker = '?';
        int consecutiveCheckerCount = 0;
        for (int r = 0; r < currentColumn.size(); ++r) {
            if (r + 1 < currentColumn.size() && c + r < gameData.size()) {
                char currentRow = gameData.at(c + r).at(r + 1);
                if ((currentRow == currentChecker) && (currentRow != ' ')) {
                    consecutiveCheckerCount++;
                }
                else {
                    consecutiveCheckerCount = 1;
                }
                currentChecker = currentRow;
                if (consecutiveCheckerCount == WINNER_CONSIDERATION_VALUE) {
                    winnerFound = GetCheckerInt(currentChecker);
                    return vector<int>{ winnerFound, 4 };
                }
            }
        }
    }
    //Diagonal (BottomLeft-TopRight)
    for (int c = 0; c < gameData.size(); ++c) {
        vector < char > currentColumn = gameData.at(c);
        char currentChecker = '?';
        int consecutiveCheckerCount = 0;
        for (int r = 0; r < currentColumn.size(); ++r) {
            if (r + 1 < currentColumn.size() && c - r < gameData.size()) {
                char currentRow = gameData.at(c - r).at(r + 1);
                if ((currentRow == currentChecker) && (currentRow != ' ')) {
                    consecutiveCheckerCount++;
                }
                else {
                    consecutiveCheckerCount = 1;
                }
                currentChecker = currentRow;
                if (consecutiveCheckerCount == WINNER_CONSIDERATION_VALUE) {
                    winnerFound = GetCheckerInt(currentChecker);
                    return vector<int>{ winnerFound, 4 };
                }
            }
        }
    }
    if (totalCheckerCount == ((gameData.size() - 1) * gameData.at(0).size())) {
        return vector<int>{3, 1};
    }
    return vector<int>{0, 0};
}

/*
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    Name: RunGame
    Input: (2) An int representing the current player and an int vector representing the wins of player 1, player 2, and the total number of ties, respectively.
    Output: None.
    Purpose: This function is hte main function that drives the whole program. Most of the function calling happens in here. 
    ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
void RunGame(int currentPlayer, vector < int > gameInfo = {0, 0, 0}) {
    bool gameEnded = false;
    int currentTurn = 0;
    vector < vector < char >> gameData;
    const unsigned int N_COLS = 7;
    const unsigned int N_ROWS = 6;
    const string ILLEGAL_POS_STRING = "Illegal position, please re-enter.";
    const string LOST_TURN = "Move not available.. you lost your turn!";
    const string ENDED_IN_TIE = "The game ended in a tie.";
    const string PLAY_AGAIN = "Would you like to play the game again? [Y/N]";
    const string NEW_GAME_STARTED = "A new game was started.";
    gameData.resize(N_COLS + 1);
    cout << endl;
    for (int c = 0; c < N_COLS + 1; ++c) {
        vector < char > rowData(N_ROWS);
        for (int x = 0; x < rowData.size(); ++x) {
            rowData.at(x) = ' ';
        }
        gameData.at(c) = rowData;
    }
    DisplayBoard(gameData);
    while (true) { 
        cout << "[" << currentTurn << "] " << "Player #" << currentPlayer << "'s Turn " << "(" << GetChecker(currentPlayer) << "): Enter your move: ";
        string myStringMove = "";
        getline(cin, myStringMove);
        int myMove = atoi(myStringMove.c_str());
        if (myMove > N_COLS || myMove < 1) {
            cout << ILLEGAL_POS_STRING << endl;
            continue;
        }
        string checkerResponse = AddChecker(currentPlayer, myMove, gameData);
        if (checkerResponse == "unavailable") {
            cout << LOST_TURN << endl;
        }
        DisplayBoard(gameData);
        vector<int> winnerData = CheckWinner(gameData);
        int winnerPlayer = winnerData.at(0);
        int winMethod = winnerData.at(1);
        if (winnerPlayer > 0 && winnerPlayer < 3) {
            cout << "Player #" << currentPlayer << " (" << GetChecker(currentPlayer) << "), you win!" << endl;
            string winMethodString = WinMethodToString(winMethod);
            cout << "(" << winMethodString << ")" << endl; 
            gameInfo.at(currentPlayer - 1)++;
            break;
        }
        else if (winnerPlayer == 3) {
            cout << ENDED_IN_TIE << endl;
            gameInfo.at(2)++;
            break; 
        }
        currentTurn += 1;
        currentPlayer = (currentPlayer % 2) + 1;
    }
    cout << endl << endl << PLAY_AGAIN << " ";
    string playAgainResponse;
    cin >> playAgainResponse;
    if (tolower(playAgainResponse[0]) == 'y') {
        cout << endl << endl << "--" << NEW_GAME_STARTED << "--" << endl << endl;
        cin.ignore();
        RunGame(SelectPlayer(), gameInfo);
    }
    else {
        cout << endl << endl;
        cout << "Wins for Player #1: " << gameInfo.at(0) << endl;
        cout << "Wins for Player #2: " << gameInfo.at(1) << endl;
        cout << "Ties: " << gameInfo.at(2) << endl;
        getchar();
    }
}

int main() {
    srand(time(0));
    DisplayWelcomeScreen();
    RunGame(SelectPlayer());
    getchar();
}