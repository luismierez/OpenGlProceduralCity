#include "Cube.h"
#include "Renderer.h"
#include <iostream>

Cube::Cube(double s, Matrix4* tm)
{
	size		= s;
	transMat	= *tm;
}

void Cube::render()
{
	glPushMatrix();
	glMultMatrixd(transMat.getPointer());
	Matrix4 currTm = Matrix4();
	glGetDoublev(GL_MODELVIEW_MATRIX, currTm.getPointer());

	glutSolidCube(size);
	glPopMatrix();
}

void Cube::setParent(Node* p)
{
	this->parent = p;
}

Node* Cube::getParent()
{
	return parent;
}

Matrix4 Cube::getTransMat()
{
	return transMat;
}