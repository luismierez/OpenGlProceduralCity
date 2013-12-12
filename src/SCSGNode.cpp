#include "SCSGNode.h"
#include "Renderer.h"

/*
		SCSGNode(double* shapeParams, Matrix4 offset, Matrix4 next);
		~SCSGNode(void);

		vector<SCSGNode> children;

		double* shapeParams;
		Matrix4 offset;
		Matrix4 next;

		void draw();
		*/

SCSGNode::SCSGNode()
{
}

SCSGNode::SCSGNode(SCSGShape s, GLdouble* sP, Matrix4 o, Matrix4 n)
{
	shape		= s;
	shapeParams[0] = sP[0];
	shapeParams[1] = sP[1];
	shapeParams[2] = sP[2];
	shapeParams[3] = sP[3];
	shapeParams[4] = sP[4];
	offset		= o;
	next		= n;

	myQuadric		= gluNewQuadric();
	gluQuadricDrawStyle( myQuadric, GLU_FILL);
	gluQuadricNormals( myQuadric, GLU_SMOOTH);
	gluQuadricOrientation( myQuadric, GLU_OUTSIDE);
	gluQuadricTexture( myQuadric, GL_TRUE);

	children = vector<SCSGNode*>();
}

void SCSGNode::draw()
{
	glPushMatrix();
	glMultMatrixd(offset.getPointer());
	glPushMatrix();
	drawShape(shape);
	glPopMatrix();
	glMultMatrixd(next.getPointer());
	for(vector<SCSGNode*>::iterator iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->draw();
	}
	glPopMatrix();
}

void SCSGNode::drawShape(SCSGShape shape)
{
	Matrix4 n = Matrix4();
	switch(shape)
	{
		case Trunk:
			/* Texturing goes here */
			glBindTexture(GL_TEXTURE_2D, Renderer::texture[2]);
			gluCylinder(myQuadric, shapeParams[0], shapeParams[1], shapeParams[2], shapeParams[3], shapeParams[4]);
			gluDisk(myQuadric, 0, shapeParams[0], shapeParams[3], shapeParams[4]);
			glPushMatrix();
			n.translationMat(0,0,shapeParams[2]);
			glMultMatrixd(n.getPointer());
			glPopMatrix();
			gluDisk(myQuadric, 0, shapeParams[1], shapeParams[3], shapeParams[4]);
			glBindTexture(GL_TEXTURE_2D, NULL);
			break;
		case Branch:
			/* Texture branch */
			glBindTexture(GL_TEXTURE_2D, Renderer::texture[2]);
			glutSolidCone(shapeParams[0], shapeParams[1], shapeParams[2], shapeParams[3]);

			Matrix4 heightTranslation = Matrix4();
			heightTranslation.translationMat(0, 0, shapeParams[1]);

			/* Texture leaves */
			glBindTexture(GL_TEXTURE_2D, Renderer::texture[3]);
			glPushMatrix();
			glMultMatrixd(heightTranslation.getPointer());
			gluSphere(myQuadric, shapeParams[4], shapeParams[2], shapeParams[3]);
			glPopMatrix();
			glBindTexture(GL_TEXTURE_2D, NULL);
			break;
	}
}

SCSGNode::~SCSGNode(void)
{
	if(!(this->children.empty()))
	{
		for(vector<SCSGNode*>::iterator iter = children.begin(); iter != children.end(); iter++)
		{
			delete (*iter);
		}
	}
}
