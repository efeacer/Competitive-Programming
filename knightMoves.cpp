//Necessary Imports
#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <queue>

using namespace std;

//Constant Declerations
const int CHESSBOARD_SIDE_LENGTH = 8;
const int EMPTY_SPOT = 0;
const int KNIGHT = 1;

//Function Declerations
int getShortestNumOfKnightMoves(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH], pair<int, int> & start, pair<int, int> & end);
pair<int, int> getKnightPos(string & knightSquare);
vector<pair<int, int>> getKnightMoves(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH], pair<int, int> & knightPos);
bool checkBounds(pair<int, int> pos);
void printChessboard(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH]);

//Main Method
int main() {
    cout << "This program computes the smallest number of knight moves between two given squares of a chessboard.\n"
    << "(The positions of the squares on the chessboard are denoted with a letter followed by a number such as e4, b6, d8, etc.)\n\n";
    string proceed;
    do {
        cout << "Do you want to proceed? (Press y to do so, press n to quit)";
        cin >> proceed;
        if (proceed == "N" || proceed == "n") {
            break;
        }
        int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH] = {EMPTY_SPOT};
        string knightSquare;
        cout<< "Enter the position of your knight on the chessboard: ";
        cin >> knightSquare;
        pair<int, int> knightPos = getKnightPos(knightSquare);
        string squareToReach;
        cout<< "Enter the position that you want to reach: ";
        cin >> squareToReach;
        pair<int, int> posToReach = getKnightPos(squareToReach);
        cout << "To get from " << knightSquare << " to " << squareToReach << " takes " << getShortestNumOfKnightMoves(chessboard, knightPos, posToReach) << " knight moves.\n\n";
     } while (proceed == "Y" || proceed == "y");
    return 0;
}

/**
 * @brief Computes and returns the smallest number of moves that a knight can take to move
 * from a square of a chessboard to another. Performs a variation of the BFS algorithm.
 * @return The smallest number of moves that a knight can take to move
 * from a square of a chessboard to another
 */
int getShortestNumOfKnightMoves(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH], pair<int, int> & start, pair<int, int> & end) {
    queue<pair<int, int>> moves;
    int counts[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH] = {0};
    moves.push(start);
    chessboard[start.first][start.second] = KNIGHT;
    counts[start.first][start.second] = 0;
    while (!moves.empty()) {
        pair<int, int> currentMove = moves.front();
        moves.pop();
        if (currentMove == end) {
            return counts[currentMove.first][currentMove.second];
        }
        for (auto move: getKnightMoves(chessboard, currentMove)) {
            if (chessboard[move.first][move.second] == EMPTY_SPOT) {
                moves.push(move);
                chessboard[move.first][move.second] = KNIGHT;
                counts[move.first][move.second] = counts[currentMove.first][currentMove.second] + 1;
            }
        }
    }
    return -1;
}

/**
 * @brief Transforms the string representation of a chessboard square to a pair structure
 * and returns it.
 * @return The pair representing the position of a given string representing a square in
 * a chessboard.
 */
pair<int, int> getKnightPos(string & knightSquare) {
    return make_pair(toupper(knightSquare[0]) - 'A', knightSquare[1] - '1');
}

/**
 * @brief Returns a list of the squares that a knight can move from  its current
 * position.
 * @return A list of the squares that a knight in a specific position can move.
 */
vector<pair<int, int>> getKnightMoves(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH], pair<int, int> & knightPos) {
    vector<pair<int, int>> knightMoves;
    if(checkBounds(make_pair(knightPos.first - 2, knightPos.second - 1))) {
        knightMoves.push_back(make_pair(knightPos.first - 2, knightPos.second - 1));
    }
    if(checkBounds(make_pair(knightPos.first - 2, knightPos.second + 1))) {
        knightMoves.push_back(make_pair(knightPos.first - 2, knightPos.second + 1));
    }
    if(checkBounds(make_pair(knightPos.first - 1, knightPos.second - 2))) {
        knightMoves.push_back(make_pair(knightPos.first - 1, knightPos.second - 2));
    }
    if(checkBounds(make_pair(knightPos.first - 1, knightPos.second + 2))) {
        knightMoves.push_back(make_pair(knightPos.first - 1, knightPos.second + 2));
    }
    if(checkBounds(make_pair(knightPos.first + 1, knightPos.second - 2))) {
        knightMoves.push_back(make_pair(knightPos.first + 1, knightPos.second - 2));
    }
    if(checkBounds(make_pair(knightPos.first + 1, knightPos.second + 2))) {
        knightMoves.push_back(make_pair(knightPos.first + 1, knightPos.second + 2));
    }
    if(checkBounds(make_pair(knightPos.first + 2, knightPos.second - 1))) {
        knightMoves.push_back(make_pair(knightPos.first + 2, knightPos.second - 1));
    }
    if(checkBounds(make_pair(knightPos.first + 2, knightPos.second + 1))) {
        knightMoves.push_back(make_pair(knightPos.first + 2, knightPos.second + 1));
    }
    return knightMoves;
}

/**
 * @brief This method check whether a given square is inside the chessboard or not.
 * It returns a boolean indicating it.
 * @return A boolean expression that is true if the given square is inside the
 * chessboard and false otherwise.
 */
bool checkBounds(pair<int, int> pos) {
    return  pos.first < CHESSBOARD_SIDE_LENGTH && pos.first >= 0 &&
    pos.second < CHESSBOARD_SIDE_LENGTH && pos.second >= 0;
}

/**
 * @brief This method prints a string representation of the chessboard for debugging
 * purposes.
 */
void printChessboard(int chessboard[CHESSBOARD_SIDE_LENGTH][CHESSBOARD_SIDE_LENGTH]) {
    for (int col = 0; col < CHESSBOARD_SIDE_LENGTH; col++) {
        cout << CHESSBOARD_SIDE_LENGTH - col << " ";
        for (int row = 0; row < CHESSBOARD_SIDE_LENGTH; row++) {
            cout << chessboard[row][CHESSBOARD_SIDE_LENGTH - 1 - col] << " ";
        }
        cout << endl;
    }
    cout << "  ";
    for (char ch = 'a'; ch <= 'h'; ch++) {
        cout << ch << " ";
    }
    cout << endl;
}
