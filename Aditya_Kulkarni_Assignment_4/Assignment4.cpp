/*
Name of the program = EECS 348 Assignment 4
Description = Cpp program where the developer sets a secret number between 1-10. User gets 3 attempts to guess the number.
Inputs= puzzle.txt files (1-5)
Outputs = Terminal output with puzzle solutions/ indicating if no solution found.
Collaborators = None 
Other sources = ChatGPT, Gemini, Claude
Author = Aditya Kulkarni
Creation date = 10/15/2026
Revision date = 10/15/2026
Revision = Added a starting-puzzle check (isStartingPuzzleValid), made findEmptyCell start from the last filled cell instead of the top, replaced endl with "\n", and moved the puzzle file names into a constant list.
*/
#include <iostream> // lets the program print to the screen (Authored by ChatGPT)
#include <fstream> // lets the program read files (Authored by ChatGPT)
#include <string> // gives us the string type (Authored by ChatGPT)
#include <vector> // gives us the vector type (Authored by ChatGPT)
#include <cctype> // gives us character helper functions (Authored by ChatGPT)

using namespace std; // lets us write cout instead of std::cout (Authored by ChatGPT)

//This is a class that will store the grid, read file, print, and change the rules
class SudokuBoard { // class that holds the 9x9 grid and its rules (Authored by ChatGPT)
public: // makes the next part usable from outside the class (Authored by Author with help of Claude for debugging, fixing and improving)
    static const int SIZE = 9; // board size, public so the solver can use it (Authored by Author with help of Claude for debugging, fixing and improving)

private: // hides the next part from outside the class (Authored by Author with help of Claude for debugging, fixing and improving)
    char grid[SIZE][SIZE]; // the 9x9 board, holds digits or '_' (Authored by ChatGPT)

public: // makes the methods below usable from outside (Authored by ChatGPT)
    SudokuBoard() { // constructor, runs when a board is created (Authored by ChatGPT)
        for (int row = 0; row < SIZE; row++) { // go through each row (Authored by ChatGPT)
            for (int col = 0; col < SIZE; col++) { // go through each column (Authored by ChatGPT)
                grid[row][col] = '_'; // start every cell as blank (Authored by ChatGPT)
            } // end of column loop (Authored by ChatGPT)
        } // end of row loop (Authored by ChatGPT)
    } // end of constructor (Authored by ChatGPT)

    bool loadFromFile(const string& filename) { // reads a puzzle file into the grid (Authored by ChatGPT)
        ifstream inputFile(filename); // opens the file (Authored by ChatGPT)

        if (!inputFile.is_open()) { // checks if the file failed to open (Authored by ChatGPT)
            return false; // report failure (Authored by ChatGPT)
        } // end of if (Authored by ChatGPT)

        int row = 0; // current row being filled (Authored by ChatGPT)
        int col = 0; // current column being filled (Authored by ChatGPT)
        char value; // holds one character read from the file (Authored by ChatGPT)

        while (inputFile >> value) { // read one non-space character at a time (Authored by ChatGPT)
            if (value == '\n' || value == '\r') { // check for line break characters (Authored by ChatGPT)
                continue; // skip them (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)

            if (value == '_' || (value >= '1' && value <= '9')) { // only accept blanks and digits 1-9 (Authored by ChatGPT)
                if (row >= SIZE) { // too many cells in the file (Authored by ChatGPT)
                    return false; // report failure (Authored by ChatGPT)
                } // end of if (Authored by ChatGPT)

                grid[row][col] = value; // store the character in the grid (Authored by ChatGPT)
                col++; // move to the next column (Authored by ChatGPT)

                if (col == SIZE) { // reached the end of the row (Authored by ChatGPT)
                    col = 0; // go back to the first column (Authored by ChatGPT)
                    row++; // move to the next row (Authored by ChatGPT)
                } // end of if (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)
        } // end of while loop (Authored by ChatGPT)

        inputFile.close(); // closes the file (Authored by ChatGPT)

        return row == SIZE && col == 0; // true only if exactly 81 cells were read (Authored by ChatGPT)
    } // end of loadFromFile (Authored by ChatGPT)

    void printBoard() const { // prints the grid with borders (Authored by ChatGPT)
        for (int row = 0; row < SIZE; row++) { // go through each row (Authored by ChatGPT)
            if (row % 3 == 0) { // every 3 rows, print a border line (Authored by ChatGPT)
                cout << "+-------+-------+-------+\n"; // prints the border, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
            } // end of if (Authored by ChatGPT)

            for (int col = 0; col < SIZE; col++) { // go through each column (Authored by ChatGPT)
                if (col % 3 == 0) { // every 3 columns, print a divider (Authored by ChatGPT)
                    cout << "| "; // prints the divider (Authored by ChatGPT)
                } // end of if (Authored by ChatGPT)

                cout << grid[row][col] << ' '; // prints the cell and a space (Authored by ChatGPT)
            } // end of column loop (Authored by ChatGPT)

            cout << "|\n"; // prints the right edge, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
        } // end of row loop (Authored by ChatGPT)

        cout << "+-------+-------+-------+\n"; // prints the bottom border, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
    } // end of printBoard (Authored by ChatGPT)

    //starts at cell number instead of top, because cells before that are full.
    bool findEmptyCell(int startIndex, int& emptyRow, int& emptyCol) const { // finds an empty cell, starting at startIndex (Authored by Author with help of Claude for debugging, fixing and improving)
        for (int index = startIndex; index < SIZE * SIZE; index++) { // loop from startIndex to the last cell (Authored by Author with help of Claude for debugging, fixing and improving)
            int row = index / SIZE; // turns the index into a row (Authored by Author with help of Claude for debugging, fixing and improving)
            int col = index % SIZE; // turns the index into a column (Authored by Author with help of Claude for debugging, fixing and improving)
            if (grid[row][col] == '_') { // checks if this cell is blank (Authored by Author with help of Claude for debugging, fixing and improving)
                emptyRow = row; // gives the row back to the caller (Authored by ChatGPT)
                emptyCol = col; // gives the column back to the caller (Authored by ChatGPT)
                return true; // an empty cell was found (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)
        } // end of loop (Authored by ChatGPT)

        return false; // no empty cells are left (Authored by ChatGPT)
    } // end of findEmptyCell (Authored by ChatGPT)
    //here it will check rows, columns and 3*3
    bool isValidPlacement(int row, int col, char digit) const { // checks if a digit can go in a cell (Authored by ChatGPT)
        for (int c = 0; c < SIZE; c++) { // go through the row (Authored by ChatGPT)
            if (grid[row][c] == digit) { // digit already in the row (Authored by ChatGPT)
                return false; // not allowed (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)
        } // end of row check (Authored by ChatGPT)

        for (int r = 0; r < SIZE; r++) { // go through the column (Authored by ChatGPT)
            if (grid[r][col] == digit) { // digit already in the column (Authored by ChatGPT)
                return false; // not allowed (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)
        } // end of column check (Authored by ChatGPT)

        int blockRow = (row / 3) * 3; // top row of this 3x3 block (Authored by ChatGPT)
        int blockCol = (col / 3) * 3; // left column of this 3x3 block (Authored by ChatGPT)

        for (int r = blockRow; r < blockRow + 3; r++) { // go through the block's rows (Authored by ChatGPT)
            for (int c = blockCol; c < blockCol + 3; c++) { // go through the block's columns (Authored by ChatGPT)
                if (grid[r][c] == digit) { // digit already in the block (Authored by ChatGPT)
                    return false; // not allowed (Authored by ChatGPT)
                } // end of if (Authored by ChatGPT)
            } // end of column loop (Authored by ChatGPT)
        } // end of row loop (Authored by ChatGPT)

        return true; // digit is safe to place (Authored by ChatGPT)
    } // end of isValidPlacement (Authored by ChatGPT)

    bool isStartingPuzzleValid() { // checks the starting digits for repeats (Authored by Author with help of Claude for debugging, fixing and improving)
        for (int row = 0; row < SIZE; row++) { // go through each row (Authored by Author with help of Claude for debugging, fixing and improving)
            for (int col = 0; col < SIZE; col++) { // go through each column (Authored by Author with help of Claude for debugging, fixing and improving)
                char digit = grid[row][col]; // saves the digit in this cell (Authored by Author with help of Claude for debugging, fixing and improving)
                if (digit != '_') { // only check filled cells (Authored by Author with help of Claude for debugging, fixing and improving)
                    grid[row][col] = '_'; // removes the digit so it does not clash with itself (Authored by Author with help of Claude for debugging, fixing and improving)
                    bool isOk = isValidPlacement(row, col, digit); // checks the digit against its row, column, and block (Authored by Author with help of Claude for debugging, fixing and improving)
                    grid[row][col] = digit; // puts the digit back (Authored by Author with help of Claude for debugging, fixing and improving)
                    if (!isOk) { // a repeated digit was found (Authored by Author with help of Claude for debugging, fixing and improving)
                        return false; // the puzzle breaks the rules (Authored by Author with help of Claude for debugging, fixing and improving)
                    } // end of if (Authored by Author with help of Claude for debugging, fixing and improving)
                } // end of if (Authored by Author with help of Claude for debugging, fixing and improving)
            } // end of column loop (Authored by Author with help of Claude for debugging, fixing and improving)
        } // end of row loop (Authored by Author with help of Claude for debugging, fixing and improving)
        return true; // no repeated digits were found (Authored by Author with help of Claude for debugging, fixing and improving)
    } // end of isStartingPuzzleValid (Authored by Author with help of Claude for debugging, fixing and improving)

    char getCell(int row, int col) const { // returns the value in a cell (Authored by ChatGPT)
        return grid[row][col]; // gives back that cell (Authored by ChatGPT)
    } // end of getCell (Authored by ChatGPT)

    void setCell(int row, int col, char value) { // sets the value in a cell (Authored by ChatGPT)
        grid[row][col] = value; // stores the value (Authored by ChatGPT)
    } // end of setCell (Authored by ChatGPT)
}; // end of SudokuBoard class (Authored by ChatGPT)

//this class runs the search and counts the solutions 
class SudokuSolver { // class that solves a board with backtracking (Authored by ChatGPT)
private: // hides the members below (Authored by ChatGPT)
    int solutionCount; // how many solutions were found (Authored by ChatGPT)

    void solveRecursive(SudokuBoard& board, int startIndex) { // recursive search, starts looking at startIndex (Authored by Author with help of Claude for debugging, fixing and improving)
        int row; // row of the empty cell (Authored by ChatGPT)
        int col; // column of the empty cell (Authored by ChatGPT)

        if (!board.findEmptyCell(startIndex, row, col)) { // looks for an empty cell from startIndex (Authored by Author with help of Claude for debugging, fixing and improving)
            solutionCount++; // no empty cells, so count a solution (Authored by ChatGPT)

            cout << "\nSolution " << solutionCount << ":\n"; // prints the solution number, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
            board.printBoard(); // prints the solved board (Authored by ChatGPT)

            return; // go back to try other possibilities (Authored by ChatGPT)
        } // end of if (Authored by ChatGPT)

        for (char digit = '1'; digit <= '9'; digit++) { // try each digit 1 to 9 (Authored by ChatGPT)
            if (board.isValidPlacement(row, col, digit)) { // only try digits that follow the rules (Authored by ChatGPT)
                board.setCell(row, col, digit); // place the digit (Authored by ChatGPT)

                solveRecursive(board, row * SudokuBoard::SIZE + col + 1); // solve the rest, starting right after this cell (Authored by Author with help of Claude for debugging, fixing and improving)

                board.setCell(row, col, '_'); // undo the digit (backtrack) (Authored by ChatGPT)
            } // end of if (Authored by ChatGPT)
        } // end of for loop (Authored by ChatGPT)
    } // end of solveRecursive (Authored by ChatGPT)

public: // makes the methods below usable from outside (Authored by ChatGPT)
    SudokuSolver() { // constructor (Authored by ChatGPT)
        solutionCount = 0; // start the count at zero (Authored by ChatGPT)
    } // end of constructor (Authored by ChatGPT)

    //solve will resent count, start the search and then it will say no solutions or tell total. 
    void solve(SudokuBoard& board) { // solves the board and prints the result (Authored by ChatGPT)
        solutionCount = 0; // reset the count (Authored by ChatGPT)

        solveRecursive(board, 0); // start the search at the first cell (Authored by Author with help of Claude for debugging, fixing and improving)

        if (solutionCount == 0) { // no solution was found (Authored by ChatGPT)
            cout << "\nNo solution found.\n"; // prints the message, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
        } else { // at least one solution was found (Authored by ChatGPT)
            cout << "\nTotal solutions found: " // starts the total message (Authored by ChatGPT)
                 << solutionCount << "\n"; // prints the total, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
        } // end of if/else (Authored by ChatGPT)
    } // end of solve (Authored by ChatGPT)
}; // end of SudokuSolver class (Authored by ChatGPT)

const int NUMBER_OF_PUZZLES = 5; // how many puzzle files there are, moved out of main (Authored by Author with help of Claude for debugging, fixing and improving)

const string PUZZLE_FILES[NUMBER_OF_PUZZLES] = { // constant list of puzzle file names (Authored by Author with help of Claude for debugging, fixing and improving)
    "puzzle1.txt", // first puzzle file (Authored by Author with help of Claude for debugging, fixing and improving)
    "puzzle2.txt", // second puzzle file (Authored by Author with help of Claude for debugging, fixing and improving)
    "puzzle3.txt", // third puzzle file (Authored by Author with help of Claude for debugging, fixing and improving)
    "puzzle4.txt", // fourth puzzle file (Authored by Author with help of Claude for debugging, fixing and improving)
    "puzzle5.txt" // fifth puzzle file (Authored by Author with help of Claude for debugging, fixing and improving)
}; // end of the list (Authored by Author with help of Claude for debugging, fixing and improving)

// main function, here it loads, prints, checks validity and solves the puzzle. Bad files are skipped.
int main() { // program starts here (Authored by ChatGPT)
    for (int i = 0; i < NUMBER_OF_PUZZLES; i++) { // go through each puzzle file (Authored by ChatGPT)
        cout << "\n========================================\n"; // prints a divider line, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
        cout << "Puzzle File: " << PUZZLE_FILES[i] << "\n"; // prints the file name, using the constant list (Authored by Author with help of Claude for debugging, fixing and improving)
        cout << "========================================\n"; // prints a divider line, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)

        SudokuBoard board; // makes a board for this puzzle (Authored by ChatGPT)

        if (!board.loadFromFile(PUZZLE_FILES[i])) { // tries to load the file, using the constant list (Authored by Author with help of Claude for debugging, fixing and improving)
            cout << "Error: Could not read a valid 9x9 puzzle " // starts the error message (Authored by ChatGPT)
                 << "from " << PUZZLE_FILES[i] << ".\n"; // finishes the error message, using the constant list and "\n" (Authored by Author with help of Claude for debugging, fixing and improving)
            continue; // skip to the next puzzle (Authored by ChatGPT)
        } // end of if (Authored by ChatGPT)

        cout << "\nOriginal Puzzle:\n"; // prints a label, with "\n" instead of endl (Authored by Author with help of Claude for debugging, fixing and improving)
        board.printBoard(); // prints the starting puzzle (Authored by ChatGPT)

        if (!board.isStartingPuzzleValid()) { // checks the starting digits for repeats (Authored by Author with help of Claude for debugging, fixing and improving)
            cout << "Error: " << PUZZLE_FILES[i] << " repeats a digit in a row, column, or block.\n"; // prints a clear error message (Authored by Author with help of Claude for debugging, fixing and improving)
            continue; // skip this puzzle (Authored by Author with help of Claude for debugging, fixing and improving)
        } // end of if (Authored by Author with help of Claude for debugging, fixing and improving)

        SudokuSolver solver; // makes a solver (Authored by ChatGPT)

        cout << "\nSolving " << PUZZLE_FILES[i] << "...\n"; // prints a progress message, using the constant list and "\n" (Authored by Author with help of Claude for debugging, fixing and improving)
        solver.solve(board); // solves the puzzle and prints all solutions (Authored by ChatGPT)
    } // end of for loop (Authored by ChatGPT)

    return 0; // program finished normally (Authored by ChatGPT)
} // end of main (Authored by ChatGPT)