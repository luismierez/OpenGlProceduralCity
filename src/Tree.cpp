#include "Tree.h"
#include "RobUtil.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

Tree::Tree(void)
{
}

Tree::~Tree(void)
{
}

string Tree::generateTree(string nextString)
{
	srand(time(NULL));
	string finalString = "";
	list<string> tokens = splitStr(nextString, " ");
	for(list<string>::iterator iter = tokens.begin(); iter != tokens.end(); iter++)
	{
		if( !(iter->compare("t")) )
		{
			finalString += "t ";
		}

		if( !(iter->compare("s")) )
		{
			finalString += generateTree("t t t t0");
		}

		if( !(iter->compare("t0")) )
		{
			switch(rand()%4)
			{
				case 0:
					finalString += generateTree("t b b t1");
					break;
				case 1:
					finalString += generateTree("t b t1");
					break;
				case 2:
					finalString += generateTree("t t1 b");
					break;
				case 3:
					finalString += generateTree("t t1");
					break;
			}
		}
		if( !(iter->compare("t1")) )
		{
			switch(rand()%2)
			{
				case 0:
					finalString += "t b b b b";
					break;
				case 1:
					finalString += "t b b b";
					break;
			}
		}
	}
	return finalString;
}