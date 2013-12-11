#ifndef __SCSGNODE_H__
#define __SCSGNODE_H__

/*
 * Simple Continuous Scene Graph (SCSG) Node
 * Class which contains a simpler implementation of scene graphs designed 
 * for use with objects constructed to be continuous.
 * 
 * All nodes have the following things:
 * - shape - see SCSGShape enum
 * - shapeParams - a GLdouble[] specifying all parameters needed to pass to the drawing function
 * - next - a Matrix4 transformation which specifies where the next object should be placed
 * - offset - a Matrix4 transformation which should place the point where the current object
 *   should connect to other objects. It is assumed the origin of the coordinate system is 
 *   the connection point. That is, if a sphere is originally created with a radius of 1, centered
 *	 at the origin, to get something to connect to the sphere at its "bottom", the sphere should be
 *	 translated up 1 unit. Offset matrices are not propagated down the drawing graph. Only next 
 *
 * Drawing happens in the following order:
 * 1) Apply offset matrix.
 * 2) Draw object.
 * 3) Apply next matrix.
 * 4) Start at 1) for children.
 * 5) Remove offset, next.
 */

#include "SmartGLUT.h"
#include <vector>
#include "Matrix4.h"

enum SCSGShape
{
	/*
	 * Trunk Params:
	 * [0] - radius at base
	 * [1] - radius at top
	 * [2] - height
	 * [3] - number of segments used to construct base
	 * [4] - number of segments to render to construct height
	 */
	Trunk,
	/*
	 * Branch Params:
	 * [0] - cone radius at base
	 * [1] - height of cone
	 * [2] - base segments
	 * [3] - height segments
	 * [4] - leaf radius
	 */
	Branch
};

using namespace std;

class SCSGNode
{
	public:
		vector<SCSGNode*> children;

		GLUquadric* myQuadric; //For using GLU drawing functions

		SCSGShape shape;
		GLdouble shapeParams[5];
		Matrix4 offset;
		Matrix4 next;

		SCSGNode();
		SCSGNode(SCSGShape shape, GLdouble* shapeParams, Matrix4 offset, Matrix4 next);
		~SCSGNode(void);

		void draw();
	private:
		void drawShape(SCSGShape shapeType);
};
#endif