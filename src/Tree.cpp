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
	modelViewMatrix = Matrix4();
	modelViewMatrix.identity();
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
					finalString += generateTree("t b t1 b");
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
	baseParams[0] = TRUNK_RADIUS_BOT;
	baseParams[1] = TRUNK_RADIUS_TOP;
	baseParams[2] = TRUNK_HEIGHT;
	baseParams[3] = TRUNK_SEGS;
	baseParams[3] = TRUNK_SEGS;

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
			trunkParams[0] = baseParams[0] - trunkIteration*TRUNK_RADIUS_DELTA;
			trunkParams[1] = baseParams[1] - trunkIteration*TRUNK_RADIUS_DELTA;
			trunkParams[2] = baseParams[2] - trunkIteration*TRUNK_HEIGHT_DELTA;
			trunkParams[3] = TRUNK_SEGS;
			trunkParams[4] = TRUNK_SEGS;

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
			/*
			trunkParams[0] = baseParams[0] - trunkIteration*TRUNK_HEIGHT_DELTA;
			trunkParams[1] = baseParams[1] - trunkIteration*TRUNK_RADIUS_DELTA;
			trunkParams[2] = baseParams[2] - trunkIteration*TRUNK_RADIUS_DELTA;
			trunkParams[3] = TRUNK_SEGS;
			trunkParams[4] = TRUNK_SEGS;
			*/

			branchParams[0] = BRANCH_RADIUS;
			branchParams[1] = BRANCH_LENGTH;
			branchParams[2] = BRANCH_SEGS;
			branchParams[3] = BRANCH_SEGS;
			branchParams[4] = BRANCH_LEAF_RADIUS;

			//Rotation
			Matrix4 *rotX = new Matrix4();
			Vector3 axis = Vector3();
			axis.set(rand()%AXIS_XY_RAND_RANGE+AXIS_XY_LOW, rand()%AXIS_XY_RAND_RANGE+AXIS_XY_LOW, rand()%100);
			axis.normalize();
			double angle = rand()%AXIS_ANGLE_RAND_RANGE + AXIS_ANGLE_LOW;
			*rotX = rotX->rotate(axis, angle);

			/*
			Matrix4 offset = trans.multiply(rotX);
			*/
			SCSGNode* newBranch = new SCSGNode(Branch, branchParams, *rotX, ident);
			current->children.push_back(newBranch);
		}
	}
	return parent;
}

void Tree::setModelViewMatrix(Matrix4 mvm)
{
	this->modelViewMatrix = mvm;
}

void Tree::regenerate()
{

	model = buildTree();
}

void Tree::draw()
{
	glPushMatrix();
	glMultMatrixd(modelViewMatrix.getPointer());
	model->draw();
	glPopMatrix();
}