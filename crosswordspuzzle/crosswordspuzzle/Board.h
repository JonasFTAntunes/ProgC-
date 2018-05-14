#include<iostream>
#include<vector>

using namespace std;

class Board
{
public:

	Board(int numlines, int numcolumns);

	int getID()const;

	void seeBoard();
	void setBoard(vector<vector<char>> newboard);

	void updateBoard(string inputword,char line,char column,char direction);
	bool placePosition(string word, char line, char column, char direction);
	void removeWord(char line, char column, char direction);

	unsigned int spacetoWord(char line, char column, char direction);


	void saveBoard(string decision);
	

private:
	vector<vector<char>> board;
	unsigned int numlines;
	unsigned int numcolumns;
	static int numboards;
	int id;


};