#pragma once

/* 
 * Abstract class which extends Node. A Group may contain any number of Nodes, and
 * should render all its children when render is called.
 */
#include "Node.h"

using namespace std;

class Group : public Node
{
	/* All applicable functions and any instance variables already implemented in Node. Top lel */
	virtual void	render() =0;				/* Renders this node and all child nodes */
	virtual void	addChild(Node* c) =0;		/* Adds a child to this node's list of children */
	virtual void	removeChild(Node* c) =0;	/* Removes a child from this node's list of children */
};
