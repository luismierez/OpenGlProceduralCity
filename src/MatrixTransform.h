#pragma once

/* 
 * Class representing a Group of Nodes which should all have a  applied
 * to them.
 */
#include "Group.h"
#include "Matrix4.h"
#include "SmartGLUT.h"

using namespace std;

class MatrixTransform : public Group
{
	private:
		Matrix4* transMat;

	public:
					MatrixTransform();						/* Default cons. Matrix initialized to identity matrix. Parent is NULL */
					MatrixTransform(Matrix4* tm);
					MatrixTransform(Matrix4* tm, Node* p); 
		void		render();								/* Renders this node and all child nodes. Assumes glMatrixMode is GL_MODELVIEW */
		void		addChild(Node* c);						/* Adds a child to this node's list of children */
		void		removeChild(Node* c);					/* Removes a child from this node's list of children */
		void		setParent(Node* c);	
		Node*		getParent();	
		Matrix4*	getTransMat();							// Returns transformation matrix
};
