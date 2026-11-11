// Tic-tac-toe for two players in the console.
// Players take turns and enter a cell number from 1 to 9.

#include <iostream>

const int SIZE = 3;

void printBoard(const char board[SIZE][SIZE]) {
    std::cout << "\n";
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            std::cout << " " << board[row][col] << " ";
            if (col < SIZE - 1) std::cout << "|";
        }
        std::cout << "\n";
        if (row < SIZE - 1) std::cout << "---+---+---\n";
    }
    std::cout << "\n";
}

// Checks all rows, columns and both diagonals for three equal marks.
bool hasWon(const char board[SIZE][SIZE], char player) {
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

int main() {
    // Cells are numbered 1-9 so the player can see which number to type.
    char board[SIZE][SIZE] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    char player = 'X';
    int movesMade = 0;

    while (movesMade < SIZE * SIZE) {
        printBoard(board);
        std::cout << "Player " << player << ", choose a cell (1-9): ";

        int cell;
        if (!(std::cin >> cell)) {
            std::cout << "Input ended.\n";
            return 0;
        }
        if (cell < 1 || cell > 9) {
            std::cout << "Please enter a number from 1 to 9.\n";
            continue;
        }

        int row = (cell - 1) / SIZE;
        int col = (cell - 1) % SIZE;
        if (board[row][col] == 'X' || board[row][col] == 'O') {
            std::cout << "That cell is already taken.\n";
            continue;
        }

        board[row][col] = player;
        movesMade++;

        if (hasWon(board, player)) {
            printBoard(board);
            std::cout << "Player " << player << " wins!\n";
            return 0;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    printBoard(board);
    std::cout << "Draw.\n";
    return 0;
}
