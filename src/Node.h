#pragma once
/* 
 * Abstract class represesnting a node in a scene graph 
 */
#include <list>

using namespace std;

class Node
{
	protected:
		list<Node*>*	children;				/* A std::list of this node's children */
		Node*			parent;					/* A pointer to this node's parents. NULL if node is the root */
	public:
		virtual void	render()				=0;		/* Renders this node and all child nodes */
		virtual void	setParent(Node* c)		=0;	
		virtual Node*	getParent()				=0;	
};
