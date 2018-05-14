#include <iostream>
#include"cwcreator.h"


using namespace std;

//Constructor,get's//////////

Cwcreator::Cwcreator(string n)
{
	name = n;
}

vector<Synonym> Cwcreator::getSynonyms()
{
	return synonyms;
}

void Cwcreator::addSynonym(Synonym synonym)
{
	synonyms.push_back(synonym);
}

							//////////main Program////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
//////treat the content of the txt synonyms and save them in the adequated structures///////

vector<string> Cwcreator::synonymsDecompose(string line)
{
	int x = 0,k;
	vector<string> v;											//each element is one synonym
	string element;


	while (x != -1)
	{
		x = line.find(",");
		element = line.substr(0, x);

		v.push_back(element);

		k = line.length();

		line = line.substr(x + 1, k);
	}
	
	return v;
}

void Cwcreator::OpenSynonyms()									//open the txt with Synonyms and read the content
{
	string file;
	string line;
	ifstream inficheiro("synonyms.txt");

	vector<string> linessynonyms;								 //vector for saving all the lines of the txt synonyms

	if (inficheiro.fail())
	{
		cerr << "Error opening " << file << "\n";
	}

	while (getline(inficheiro, line))
	{
		stringstream linestream(line);
		string value;


		int i = 0;
		int x = 0;
		while (getline(linestream, value, '\n'))
		{
			linessynonyms.push_back(value);
		}
	}
	inficheiro.clear();
	inficheiro.close();

	/*for (size_t t = 0; t < linessynonyms.size(); t++)
	{
		cout << linessynonyms[t] << endl;
	}*/

	vector<string> synonymx;
	
	int w = 0;

	while (w != (linessynonyms.size()-1))
	{
		string wordx,l;
		int x, k;
		vector<string> linesynonyms;      ////all the synonyms in the line 

		x = linessynonyms[w].find(":");
		wordx = linessynonyms[w].substr(0, x);
		k = linessynonyms[w].length();
		
		linesynonyms = synonymsDecompose(linessynonyms[w].substr(x + 1, k));
		Synonym c(wordx, linesynonyms);
		//c.setWord(wordx);
		//c.setSynonym(linesynonyms);
		addSynonym(c);
		w++;
	}
	
	/*for (size_t x = 0; x < synonyms.size(); x++)
	{
		cout << synonyms[x].getWord() << endl;
	}*/
	/*for (size_t x = 0; x < synonyms.size(); x++)                        //see each word 
	{
		vector<string> v= synonyms[x].getSynonyms();

		cout << synonyms[x].getWord() << endl;

		for (size_t y = 0; y < v.size(); y++)                             //for each word see their list of synonyms
		{
			cout << v[y];
		}
		cout << endl;
	}*/

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////         GAME          /////////////////////////////////////////


void Cwcreator::creatingGame()
{
	int lines, columns;

	cout << "Board size(lines columns)?" << endl;
	cin >> lines >> columns;

	Board game(lines, columns);
	playingGame(game);

}

bool Cwcreator::belongsWord(string word)                    //test if a Word belongs to the dictionary (ex:Aback)
{
	bool valid = false;

	for (size_t i = 0; i < synonyms.size(); i++)
	{
		if (synonyms[i].getWord() == word)
		{
			return true;
		}		
	}
	cout << "word doesnt belong to the dictionary" << endl;		

	return valid;
}

string Cwcreator::transformWord(string word)   //receveis a Word like Aback,aback,ABACK and returns the word Aback
{
	string inputWord = word;
	bool cap = true;

	for (unsigned int i = 0; i <= inputWord.length(); i++)
	{
		if (isalpha(inputWord[1]) && cap == true)
		{
			inputWord[i] = tolower(inputWord[i]);

		}
		else if (isalpha(inputWord[i]) && cap == true)
		{
			inputWord[i] = toupper(inputWord[i]);
			cap = false;
		}

	}
	inputWord[0] = toupper(inputWord[0]);

	return inputWord;
}

bool Cwcreator::notUsed(string word,vector<string> wordsused)    //test if the word has not yet been placed on the board
{

	if (wordsused.size() == 0)
		return false;
	else
	{
		for (size_t i = 0; i < wordsused.size(); i++)
		{
			
			if (wordsused[i] == word)
			{
				cout << "word already used " << endl;
				return true;
			}
		}
	}

	
	return false;
}

bool Cwcreator::cheackCtrl(Board game,bool anotherOperation, bool validOperands)  //check if its was used ctrl-z, and if it was, check if the user want to save or finish the board
{

	do
	{
		validOperands = true;
		if (cin.fail())
		{
			if (cin.eof())
			{
				string decision;
				cin.clear();

				cout << "s=save / f=finish:" << endl;
				cin >> decision;
			
				game.saveBoard(decision);
				

				anotherOperation = false;
			}
			else
			{
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		else
			cin.ignore(1000, '\n');

	} while (anotherOperation && !validOperands);

	return anotherOperation;
}


void Cwcreator::fitWord(unsigned int size) //apenas esta a dar as palavras que cabem, e nao os sinonimos,
{
	for (size_t x = 0; x < synonyms.size(); x++)
	{
		if ((synonyms[x].getWord()).length() <= size)
			cout << synonyms[x].getWord() << endl;
	}

}

void Cwcreator::playingGame(Board game)
{
	game.seeBoard();
	
	string inputdirections, inputWord;
	char line, column, direction;
	vector<string> vectorwords;                            //vector of the words used during a game	
	bool anotherOperation;
	
	do
	{
		cout << "Position( LCD / ctrl-z ) : ";
		cin >> inputdirections;

		bool validOperands=true;
		anotherOperation = true;

		anotherOperation=cheackCtrl(game,anotherOperation,validOperands);

			
		if (validOperands && anotherOperation)   //if validOperands==true e anotherOperation==true continues the game
		{
		
			const char *str = inputdirections.c_str();
			line = str[0];
			column = str[1];
			direction = str[2];


			cout << "Word( - = remove / ? = help):";
			cin >> inputWord;

			if (inputWord == "-")                                                 //remove word from board
			{
				game.removeWord(line, column, direction);
			}
			else if (inputWord == "?")                        // ask for a list of possible words that fit into the specified position, by typing "?" in answer to the "Word?" question.
			{				
				unsigned int size;
				size=game.spacetoWord(line, column, direction);
				fitWord(size);
			}
			else         
			{
				inputWord = transformWord(inputWord);

				if (belongsWord(inputWord) == true && game.placePosition(inputWord, line, column, direction) == true && notUsed(inputWord, vectorwords) == false)
				{
					vectorwords.push_back(inputWord);                            //correct this, (sempre a aumentar o vector com palavras repetidas)
					game.updateBoard(inputWord, line, column, direction);
					
				}
				
			}

		}

	}while(anotherOperation);

}


