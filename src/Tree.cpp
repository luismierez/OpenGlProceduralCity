#define _USE_MATH_DEFINES
#include <math.h>

#include "Tree.h"
#include "RobUtil.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
int Tree::randomSeed = time(NULL);

Tree::Tree(void)
{
	modelCreated = 0;
	model = buildTree();
}

Tree::~Tree(void)
{
}

string Tree::generateTree(string nextString)
{
	srand(randomSeed++);
	string finalString = "";
	list<string> tokens = splitStr(nextString, " ");
	for(list<string>::iterator iter = tokens.begin(); iter != tokens.end(); iter++)
	{
		if( !(iter->compare("t")) )
		{
			finalString += "t ";
			continue;
		}

		if( !(iter->compare("s")) )
		{
			finalString += generateTree("t t t t0");
			continue;
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
			continue;
		}
		if( !(iter->compare("t1")) )
		{
			switch(rand()%2)
			{
				case 0:
					finalString += "t b b b b ";
					break;
				case 1:
					finalString += "t b b b ";
					break;
			}
			continue;
		}
		finalString +=  *iter + " ";
	}
	return finalString;
}

SCSGNode* Tree::buildTree()
{
	generationString = generateTree("s");
	int trunkIteration = 0;
	Matrix4 ident = Matrix4();
	ident.identity();

	Matrix4 rotateToUpright = Matrix4();
	rotateToUpright.rotateX(-90);

	GLdouble baseParams[5];
	/*
	 * Trunk Params:
	 * [0] - radius at base
	 * [1] - radius at top
	 * [2] - height
	 * [3] - number of segments used to construct base
	 * [4] - number of segments to render to construct height
	 */
	baseParams[0] = 10.0;
	baseParams[1] = 9.0;
	baseParams[2] = 10.0;
	baseParams[3] = 10.0;
	baseParams[3] = 10.0;

	SCSGNode* parent = new SCSGNode(Trunk, baseParams, rotateToUpright, ident);
	SCSGNode* current = parent;
	list<string> tokens = splitStr(generationString, " ");
	for(list<string>::iterator iter = tokens.begin(); iter != tokens.end(); iter++)
	{
		GLdouble trunkParams[5];
		GLdouble branchParams[5];
		if( !(iter->compare("t") ) )
		{
			trunkIteration++;
			trunkParams[0] = baseParams[0] - trunkIteration;
			trunkParams[1] = baseParams[1] - trunkIteration;
			trunkParams[2] = baseParams[2] - trunkIteration;
			trunkParams[3] = 10.0;
			trunkParams[4] = 10.0;

			Matrix4 n = Matrix4();
			n.translationMat(0,0,trunkParams[2]);

			SCSGNode* newTrunk = new SCSGNode(Trunk, trunkParams, ident, n);
			current->children.push_back(newTrunk);
			current = newTrunk;
		}
		if( !(iter->compare("b") ) )
		{
			srand(randomSeed++);
			/*
			 * Branch Params:
			 * [0] - cone radius at base
			 * [1] - height of cone
			 * [2] - base segments
			 * [3] - height segments
			 * [4] - leaf radius
			 */
			trunkParams[0] = baseParams[0] - trunkIteration;
			trunkParams[1] = baseParams[1] - trunkIteration;
			trunkParams[2] = baseParams[2] - trunkIteration;
			trunkParams[3] = 10.0;
			trunkParams[4] = 10.0;

			branchParams[0] = 2.0;
			branchParams[1] = (15-rand()%5);
			branchParams[2] = 10.0;
			branchParams[3] = 10.0;
			branchParams[4] = (14-rand()%2);

			//Rotation
			Matrix4 *rotX = new Matrix4();
			Vector3 axis = Vector3();
			axis.set(rand()%60+40, rand()%60+40, rand()%100);
			axis.normalize();
			double angle = rand()%180;//(180)/180.0 * M_1_PI;
			*rotX = rotX->rotate(axis, angle);
					
			Matrix4 trans = Matrix4();
			trans.translationMat(0,0, -(branchParams[2]* 5/6));

			/*
			Matrix4 offset = trans.multiply(rotX);
			*/
			SCSGNode* newBranch = new SCSGNode(Branch, branchParams, *rotX, ident);
			current->children.push_back(newBranch);
		}
	}
	return parent;
}

void Tree::regenerate()
{
	model = buildTree();
}

void Tree::draw()
{
	model->draw();
}