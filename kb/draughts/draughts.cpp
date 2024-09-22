/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/draughts
TAGS: brute_force
EXPLANATION:
Basically just iterates through each white piece and tries to capture in each direction. It compares the number of possible captures each route it takes to find the greatest amount of captures possible.
END ANNOTATION
*/

#include <iostream>
using namespace std;
#define BOARD_SIZE 10

int findCaptures(char board[][10], int y, int x) {
    int solution = 0;
    //cout << x << ", " << y << endl;
    //cout << "up left" << endl; //check up-left
    if((x - 2 >= 0 && y - 2 >= 0)
       && board[y - 1][x - 1] == 'B'
       && board[y - 2][x - 2] == '#') {
        //can capture
        board[y - 1][x - 1] = '#';
        int captures = 1 + findCaptures(board, y - 2, x - 2);
        if(captures > solution)
            solution = captures;
        board[y - 1][x - 1] = 'B';
    }
    //cout << "up right" << endl; //check up-right
    if((x + 2 <= BOARD_SIZE && y - 2 >= 0)
       && board[y - 1][x + 1] == 'B'
       && board[y - 2][x + 2] == '#') {
        //can capture
        board[y - 1][x + 1] = '#';
        int captures = 1 + findCaptures(board, y - 2, x + 2);
        if(captures > solution)
            solution = captures;
        board[y - 1][x + 1] = 'B';
    }
    //cout << "down left" << endl; //check down-left
    if((x - 2 >= 0 && y + 2 <= BOARD_SIZE)
       && board[y + 1][x - 1] == 'B'
       && board[y + 2][x - 2] == '#') {
        //can capture
        board[y + 1][x - 1] = '#';
        int captures = 1 + findCaptures(board, y + 2, x - 2);
        if(captures > solution)
            solution = captures;
        board[y + 1][x - 1] = 'B';
    }
    //cout << "down right" << endl; //check down-right
    if((x + 2 <= BOARD_SIZE && y + 2 <= BOARD_SIZE)
       && board[y + 1][x + 1] == 'B'
       && board[y + 2][x + 2] == '#') {
        //can capture
        board[y + 1][x + 1] = '#';
        int captures = 1 + findCaptures(board, y + 2, x + 2);
        if(captures > solution)
            solution = captures;
        board[y + 1][x + 1] = 'B';
    }
    return solution;
}

int main() {
    int t;
    cin >> t;
    for(int tc = 0; tc < t; tc++) {
        char board[BOARD_SIZE][BOARD_SIZE];
        for(int i = 0; i < BOARD_SIZE; i++)
            cin >> board[i];
        int solution = 0;
        for(int y = 0; y < BOARD_SIZE; y++) {
            for(int x = 0; x < BOARD_SIZE; x++) {
                if(board[y][x] != 'W')
                    continue;
                //found white piece
                board[y][x] = '#';
                int captures = findCaptures(board, y, x);
                board[y][x] = 'W';
                if(captures > solution)
                    solution = captures;
            }
        }
        cout << solution << endl;
    }
    return 0;
}
