#include<iostream>
#include"Synonyms.h"
#include"Board.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
#include <ctype.h>
#include <map>
#include <ctime>
#include <cstdio>

using namespace std;

class Cwcreator
{
public:

	Cwcreator(string name);
	
	////synonyms
	vector<Synonym> getSynonyms();
	void addSynonym(Synonym synonym);

	vector<string> synonymsDecompose(string line);
	void OpenSynonyms();

	//Game
	void creatingGame();
	void playingGame(Board game);
	bool belongsWord(string word);
	string transformWord(string word);
	bool notUsed(string word, vector<string> words);
	bool cheackCtrl(Board game,bool anotherOperation, bool validOperands);
	void fitWord(unsigned int size);

private:
	string name;
	vector<Synonym> synonyms;
};