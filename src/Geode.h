#pragma once
#include "Node.h"
#include "Matrix4.h"

/*
 * Primative abstract Geode class
 */
class Geode : public Node
{
	public:
		Matrix4				transMat;

		virtual void		render() = 0;				/* Renders this node and all child nodes */
		virtual Matrix4		getTransMat() = 0;
};