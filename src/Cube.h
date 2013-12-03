#pragma once
#include "Geode.h"
#include "Matrix4.h"
#include "SmartGLUT.h"
class Cube :
	public Geode
{
	private:
		double size;
	public:
		Cube(double s, Matrix4* transMat);
		void		render();
		Matrix4		getTransMat();
		void		setParent(Node* p);
		Node*		getParent();
};

