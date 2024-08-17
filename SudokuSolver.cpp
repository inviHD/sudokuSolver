#include <iostream>
#include <fstream>

using namespace std;

const int N = 9;

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if the number already exists in the same row
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return false;
        }
    }

    // Check if the number already exists in the same column
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return false;
        }
    }

    // Check if the number already exists in the same 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find the next empty cell
    bool isEmpty = false;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    // If there are no empty cells, the Sudoku is solved
    if (!isEmpty) {
        return true;
    }

    // Try different numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the Sudoku
            if (solveSudoku(grid)) {
                return true;
            }

            // If the current number doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    cout << "Welcome to Sudoku Solver!" << endl;
    bool running = true;
    while (running) {

        int grid[N][N];

        // Ask User if they want to enter the Sudoku grid or read it from a file
        char choice1;
        cout << "Do you want to enter the Sudoku grid or read it from a file? (e/f): ";
        cin >> choice1;

        if (choice1 == 'f' || choice1 == 'F') {
            cout << "Enter the file name: ";
            string fileName;
            cin >> fileName;

            // Check if the file exists
            ifstream file(fileName);

            if (!file) {
                cout << "File not found." << endl;
                break;
            }

            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                    file >> grid[row][col];
                }
            }
            file.close();

            cout << "Loaded Sudoku grid:" << endl;
            printGrid(grid);
        }



        else {


            cout << "Enter the Sudoku grid (0 for empty cells):" << endl;
            cout << "Example:" << endl;
            cout << "5 3 0 0 7 0 0 0 0" << endl;
            cout << "6 0 0 1 9 5 0 0 0" << endl;
            cout << "0 9 8 0 0 0 0 6 0" << endl;
            cout << "8 0 0 0 6 0 0 0 3" << endl;
            cout << "4 0 0 8 0 3 0 0 1" << endl;
            cout << "7 0 0 0 2 0 0 0 6" << endl;
            cout << "0 6 0 0 0 0 2 8 0" << endl;
            cout << "0 0 0 4 1 9 0 0 5" << endl;
            cout << "0 0 0 0 8 0 0 7 9" << endl;
            cout << endl;

            for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {

                    cin >> grid[row][col];
                }
            }
        }



        if (solveSudoku(grid)) {
            cout << "Sudoku solved:" << endl;
            printGrid(grid);

            // Ask if the solution should be printed to a file without freopen
            char choice;
            cout << "Do you want to print the solution to a file? (y/n): ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                cout << "Enter the file name: ";
                string fileName;
                cin >> fileName;
                ofstream file(fileName);
                for (int row = 0; row < N; row++) {
                    for (int col = 0; col < N; col++) {
                        file << grid[row][col] << " ";
                    }
                    file << endl;
                }
                file.close();
                cout << "Solution printed to " << fileName << endl;
            }
        }
        else {
            cout << "No solution exists for the given Sudoku." << endl;
        }

        return 0;
    }
}