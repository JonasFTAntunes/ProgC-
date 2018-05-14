#include <iostream>
#include "Board.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime> 
#include <cstdlib>
#include <windows.h>

using namespace std;

int Board::numboards = 0;



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

////get's

int Board::getID() const
{
	return id;
}

Board::Board(int numlinesx, int numcolumnsx)
{
	numlines = numlinesx;
	numcolumns = numcolumnsx;

	vector< vector<char>> vx(numlines);

	for (unsigned int i = 0; i<numlines; i++)
	{
		vx[i].resize(numcolumns);

		for (unsigned int j = 0; j< numcolumns; j++)
		{
			vx[i][j] = ('.');
		}

	}

	board = vx;
	id = numboards++;
	

}

void Board::setBoard(vector<vector<char>> newboardx)
{
	this->board = newboardx;
}

////////////////////////////////////////////

 void setcolor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hCon, FOREGROUND_INTENSITY | BACKGROUND_BLUE);

}

void Board::seeBoard()
{
	setcolor(2, 0);

	string str = "abcdefghijklmnopqrstuvwxyz";
	const char *cstr = str.c_str();
	cout <<"  ";
	printf("%.*s\n", numcolumns, cstr);
	
	
	char c = 'A';
	for (size_t i = 0; i < board.size(); i++)
	{
	
		cout << c << " ";
		for (size_t w = 0; w < board[i].size(); w++)
		{
			cout<<board[i][w];
		}
		c++;
		cout << endl;
	}

}

void Board::updateBoard(string inputword,char line,char column,char direction)  //update the board after each round 
{
	
	int directx = static_cast<int>(direction);                                      //convert char to int(ascii)
	int numline = static_cast<int>(line);
	int numcolumn = static_cast<int>(column);
	const char *str = inputword.c_str();

	
	int n=numline;
	int m = numcolumn;
	unsigned int x = 0;

	
	if (directx == 72)                           //ascii=72 'H'
	{
		
			while (x < strlen(str))
			{
				board[n - 65][m - 97] = putchar(toupper(str[x]));
				x++;
				m++;
			}
		
			
	}
	else if(directx == 86)					//ascii=86 'V'
	{
		
			while (x < strlen(str))
			{
				board[n - 65][m - 97] = putchar(toupper(str[x])); 
				n++;
				x++;
			}
		
		
	}
		
	seeBoard();
}
 

bool Board::placePosition(string word, char line, char column, char direction)  //return true or false, if a certain Word can be put on a certain position in the board
{
	int directx = static_cast<int>(direction);                                      //convert char to int(ascii)
	int postionline = static_cast<int>(line);
	int positioncolumn = static_cast<int>(column);
	unsigned int cumpstring = word.length();
	

	int n = postionline -65;
	int m = positioncolumn -97;
	
	bool valid = false;

	if (directx == 72)														//ascii=72 'H'
	{
		if ((numcolumns - m) < cumpstring)
		{
			cout << "word out of range" << endl;
			return false;
		}
		else
			return true;		
	}
	else if (directx == 86)													//ascii=86 'V'
	{
		if ((numlines - n) < cumpstring)
		{
			cout << "word out of range" << endl;
			return false;
		}
		else
			return true;
	}
	
	return valid;
}

void Board::removeWord(char line, char column, char direction) //remove word from board using previous orientacion (ex:AaH ,remove word starting cell Aa )
{
	int directx = static_cast<int>(direction);                                      //convert char to int(ascii)
	int postionline = static_cast<int>(line);
	int positioncolumn = static_cast<int>(column);

	int n = postionline - 65;
	int m = positioncolumn - 97;

	if (directx == 72)														//ascii=72 'H'
	{
		while ((board[n][m] != '.' || board[n][m] != '#') && m < (numcolumns - 1))
		{			
			board[n][m] = '.';
			m++;
			seeBoard();
		} 
		
		
	}
	else if (directx == 86)													//ascii=86 'V'
	{
		while ((board[n][m] != '.' || board[n][m] != '# ') && n < (numlines - 1))
		{
			board[n][m] = '.';
			n++;
			seeBoard();
		} 
		  		
	}
}


unsigned int Board::spacetoWord(char line, char column, char direction)  //return the size free to that a word can fit in the specified position
{
	int directx = static_cast<int>(direction);                                      //convert char to int(ascii)
	int postionline = static_cast<int>(line);
	int positioncolumn = static_cast<int>(column);

	int n = postionline - 65;
	int m = positioncolumn - 97;
	int sizefree=0;

	if (directx == 72)														//ascii=72 'H'
	{
		sizefree = numcolumns - m;
		return sizefree;
	}
	else if (directx == 86)													//ascii=86 'V'
	{
		sizefree = numlines - n;
		return sizefree;
	}

	return sizefree;
}


void Board::saveBoard(string decision)                     //save the current board
{
	int x = id+1;
	string str;
	ostringstream temp;
	if (x < 10)
		temp << "00" << x;
	else if (x >= 10 && x < 99)
		temp << "0" << x;
	else
		temp << x;

	str = temp.str();

	const string text = (("b" +  str ) + ".txt");                        // text=bXXX.txt
	
	if (decision == "s")
	{		
		ofstream boardx;
		boardx.open(text, fstream::app);

		//boardx << (id+1) << endl;
		for (size_t i = 0; i < board.size(); i++)
		{
			for (size_t w = 0; w < board[i].size(); w++)
			{
				boardx << board[i][w];
			}
			boardx << endl;

		}
		boardx.clear();
		boardx.close();
	}
	else if(decision == "f")
	{
		////check finished board and save
	}
	
}




