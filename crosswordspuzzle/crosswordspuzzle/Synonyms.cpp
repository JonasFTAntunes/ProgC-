#include<iostream>
#include "Synonyms.h"

using namespace std;

int Synonym::numSynonyms = 0;

//---Get's----

int Synonym::getID() const
{
	return id;
}

string Synonym::getWord() const
{
	return word;
}

vector<string> Synonym::getSynonyms()
{
	return synonyms;
}

//---Set's----
void Synonym::setID(int newidentifier)
{
	this->id = newidentifier;
}

void Synonym::setWord(string newword)
{
	this->word = newword;
}

void Synonym::setSynonym(vector<string> synonymsx)
{
	this->synonyms = synonymsx;
}

//---Constructor-----

Synonym::Synonym(string wordx,vector<string> synonymsx)
{
	synonyms = synonymsx;
	id = numSynonyms++;
	word = wordx;
}