#include "MatrixTransform.h"

MatrixTransform::MatrixTransform()
{
	transMat	= new Matrix4();
	children	= new list<Node*>();
	parent		= NULL;
}

MatrixTransform::MatrixTransform(Matrix4* tm)
{
	transMat	= tm;
	children	= new list<Node*>();
	parent		= NULL;
}

MatrixTransform::MatrixTransform(Matrix4* tm, Node* p)
{
	transMat	= tm;
	children	= new list<Node*>();
	parent		= p;
}

void MatrixTransform::render()
{
	/* Depth-first traversal */
	glPushMatrix();
	glMultMatrixd(transMat->getPointer());
	list<Node*>::iterator iter;
	for(iter = children->begin(); iter != children->end(); iter++)
	{
		(*iter)->render();
	}
	glPopMatrix();
}

void MatrixTransform::addChild(Node* c)
{
	children->push_front(c);
	c->setParent(this);
}

void MatrixTransform::removeChild(Node* c)
{
	c->setParent(NULL);
	children->remove(c);
}

void MatrixTransform::setParent(Node* c)
{
	this->parent = c;
}

Node* MatrixTransform::getParent()
{
	return parent;
}

Matrix4* MatrixTransform::getTransMat()
{
	return transMat;
}
