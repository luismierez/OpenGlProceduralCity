#ifndef _TREE_H
#define _TREE_H

#include <string>
#include <list>
#include "SCSGNode.h"

//Generation parameters: play with these values to change how the tree generates
//Trunk parameters:
#define TRUNK_HEIGHT			10.0	//The height of the initial trunk (affects all other trunks)
#define TRUNK_HEIGHT_DELTA		1.0		//The amount the trunk height changes each generation round

//IMPORTANT: For the tree to be continuous, the difference betwen TRUNK_RADIUS_BOT and TRUNK_RADIUS_TOP must be TRUNK_RADIUS_DELTA. BOT must be > TOP
#define TRUNK_RADIUS_BOT		10.0	//The radius of the bottom of the initial trunk (affects all other trunks)
#define TRUNK_RADIUS_TOP		9.0		//The radius of the top of the initial trunk (affects all other trunks)

#define TRUNK_SEGS				10.0	//The amount of segments used to draw each section of the trunk (decrease if having performance issues)

//Branch params
#define BRANCH_RADIUS			2.0				//The initial radius of the bottom of branch. (branch is a cone)
#define BRANCH_LENGTH			(15-rand()%5)	//The length of the branches
#define BRANCH_SEGS				10.0			//Number of segments used to draw the branch (decrease if having performance issues)
#define BRANCH_LEAF_RADIUS		(14-rand()%2)	//The radius for the leaf spheres

//Branch rotation params - set these to change the characteristics of how branches are rotated
//Branch rotation picks a random axis based on the generation rules and then rotates the branch a random amount around that axis.

#define AXIS_XY_LOW				40				//The lowest possible value for XY axis choosing (valid range: between 0 and AXIS_HIGHPASS_XY)
#define AXIS_XY_HIGH			100				//The highest possible value for XY axis choosing (valid range: between AXIS_LOWPASS_XY and 100)
#define AXIS_ANGLE_LOW			90				//The lowest possible angle that can be chosen for the rotation angle after an axis is chosen
#define AXIS_ANGLE_HIGH			180				//The highest possible angle that can be chosen for the rotation angle  after an axis is chosen

//DO NOT MODIFY THESE - they are generated as a result of the generation parameters you've set
#define AXIS_ANGLE_RAND_RANGE	(AXIS_ANGLE_HIGH - AXIS_ANGLE_LOW)
#define AXIS_XY_RAND_RANGE		(AXIS_XY_HIGH - AXIS_XY_LOW)
#define TRUNK_RADIUS_DELTA		(TRUNK_RADIUS_BOT - TRUNK_RADIUS_TOP)

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
	Matrix4 modelViewMatrix;
	SCSGNode* model;
	int modelCreated;

	public:
		Tree(void);
		~Tree(void);
	
		string generateTree(string nextString);
		void setModelViewMatrix(Matrix4 mvm);
		void draw();
		void regenerate();
	private:
		SCSGNode* buildTree();
};
#endif
