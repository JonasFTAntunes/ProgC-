#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <string>
#include <vector>

//COLOR CODES: (alternative: use symbolic const’s)
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

using namespace std;

void initGrid(int grid[][10])
{
	for (int col = 0; col < 10; col++)	//Outter column loop
	{
		for (int row = 0; row < 10; row++)	//Inner row loop
		{
			grid[col][row] = 0;
		}
	}
}

void printBoard(int grid[][10])		//Print the board
{
	cout << "   a|b|c|d|e|f|g|h|i|j" << endl;
	for (int i = 0; i < 10; i++)		//column loop
	{
		for (int j = 0; j < 10; j++)		//row loop
		{
			if (j == 0)
			{
				cout << i << "  ";		//print row number and spaces before new row
			}
			cout << ".";
			if (j != 9)
			{
				cout << "|";
			}
		}
		cout << endl;		//new line at end of column
	}
	cout << endl;
}

// Set text color & background 
void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (background_color == BLACK)
		SetConsoleTextAttribute(hCon, color);
	else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN |
			BACKGROUND_RED);
}

int main() {

	int grid[10][10];
	initGrid(grid);
	setcolor(9, 4);
	printBoard(grid);

}