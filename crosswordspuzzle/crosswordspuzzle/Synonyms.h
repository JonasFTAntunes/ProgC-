#include <iostream>
#include<vector>

using namespace std;

class Synonym
{
public:

	Synonym(string word,vector<string> synonyms);

	int getID() const;
	string getWord() const;
	vector<string> getSynonyms();
	
	void setWord(string word);
	void setID(int newidentifier);
	void setSynonym(vector<string> newsynonyms);

	


private:

	static int numSynonyms;
	int id;
	string word;
	vector<string> synonyms;

};