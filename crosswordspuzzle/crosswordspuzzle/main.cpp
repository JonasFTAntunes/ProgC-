#include<iostream>
#include "cwcreator.h"


using namespace std;

Cwcreator c("crossWords");



int main()
{
	c.OpenSynonyms();

	cout << "----------WELCOME TO CROSSWORDS MAKER----------" << endl;
	c.creatingGame();
		
	return 0;
}