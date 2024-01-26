#include <iostream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()
#include <cmath>
#include <iomanip>

using namespace std;
int lindex = 2;

char getQuad(int** grid, int &n, int &x, int &y) {
    int i = 0;
    int j = 0;
    bool flag = false;
    for (i = y; i < n + y; i++)
    {
        for (j = x; j < n + x; j++) {
            if (grid[i][j] != 0) 
            {
                flag = true;  
                break;
            }
        }
        if (flag)
        {
            break;
        }
    }

    if(j - x >= (n)/2 && i - y < (n)/2)
        return 'a';
    if(j - x < (n)/2 && i - y < (n)/2)
        return 'b';
    if(j - x < (n)/2 && i - y >= (n)/2)
        return 'c';
    return 'd';
}

void tileGrid(int** grid, int n, int x, int y) {
    if (n == 1 || n == 0) return;
    char quad = getQuad(grid, n, x, y);
    if (quad == 'a')
    {
        grid[n/2 + y][n/2 + x] = lindex;
        grid[n/2 - 1 + y][n/2 - 1 + x] = lindex;
        grid[n/2 + y][n/2 - 1 + x] = lindex;
    }
    if (quad == 'b')
    {
        grid[n/2 + y][n/2 + x] = lindex;
        grid[n/2 -1 + y][n/2 + x] = lindex;
        grid[n/2 + y][n/2 - 1 + x] = lindex;
    }
    if (quad == 'c')
    {
        grid[n/2 + y][n/2 + x] = lindex;
        grid[n/2 -1 + y][n/2 + x] = lindex;
        grid[n/2 -1 + y][n/2 - 1 + x] = lindex;            
    }
    if (quad == 'd')
    {
        grid[n/2 + y][n/2 - 1 + x] = lindex;
        grid[n/2 -1 + y][n/2 + x] = lindex;
        grid[n/2 -1 + y][n/2 - 1 + x] = lindex;     
    }
    lindex++;

    tileGrid(grid, n/2, x + n/2, y);
    tileGrid(grid, n/2, x, y);
    tileGrid(grid, n/2, x, y + n/2);
    tileGrid(grid, n/2, x + n/2, y + n/2);
}

int main() {
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr)));

    // Ask for the value of n
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    int size = pow(2, n);

    // Initialize a dynamic 2D array with all zeros
    int** grid = new int*[size];
    for (int i = 0; i < size; ++i) {
        grid[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            grid[i][j] = 0;
        }
    }

    // Generate a random row and column
    int randomRow = rand() % size;
    int randomCol = rand() % size;

    // Set the random element to 1
    grid[randomRow][randomCol] = 1;


    int x = 0;
    int y = 0;
    // Tile the grid with L shapes
    tileGrid(grid, size, x, y);

    // Print the grid to the terminal with proper formatting
    cout << "Generated Grid:\n";
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << setw(4) << grid[i][j] << " ";  // setw(4) sets the width of each number
        }
        cout << endl;
    }

    // Deallocate memory
    for (int i = 0; i < size; ++i) {
        delete[] grid[i];
    }
    delete[] grid;

    return 0;
}
