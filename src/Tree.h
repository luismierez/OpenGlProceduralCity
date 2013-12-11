#ifndef _TREE_H
#define _TREE_H

#include <string>
#include <list>
#include "SCSGNode.h"
/*
 L System Grammar

 s		::= t t t t0
 t0		::= t b b t1 | t b t1 | t t1 b | t t1
 t1		::= t b b b b | t b b b

 Each t is a cylinder generated pointing straight up.

 Each b is a cylinder along a random axis initially parallel to the z-axis, then rotated up by a random number of degrees.
 Leaves are attached to each b.

 */ 
using namespace std;
class Tree
{
	static int randomSeed;
	string generationString;
	SCSGNode* model;
	int modelCreated;

	public:
		Tree(void);
		~Tree(void);
	
		string generateTree(string nextString);
		void draw();
		void regenerate();
	private:
		SCSGNode* buildTree();
};
#endif
