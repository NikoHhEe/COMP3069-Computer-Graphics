#pragma once

#include "DisplayableObject.h"

class Tree :
	public DisplayableObject
	
{
public:
	Tree();
	~Tree() {};
	void Display();
	
private:

	void DrawTree();		// function to draw the tree
	void DrawTrunk();		// function to draw a trunk
	void DrawLeaves();		// function to draw all the leaves
	void DrawLeaf(float l);	// function to draw a leaf

	float trunkHeight;		// height of the trunk (also tree height)
	float trunkRadius;		// bottom radius of the trunk

	float leafStartHeight;	// height where leaves start to grow
	float leafLength;		// length of the leaf
	float leafRadius;		// bottom radius of the leaf
	float leafRotation;		// angle of leaf rotation

};

