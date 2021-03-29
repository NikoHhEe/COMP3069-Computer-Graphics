#include "Tree.h"
#include <cmath>

// initialise the parameters in tree class
Tree::Tree() : trunkHeight(30.0f), trunkRadius(1.0f), leafRotation(20.0) {
	leafStartHeight = trunkHeight / 3.0f;
	leafLength = leafStartHeight;
	leafRadius = 0.5f * trunkRadius;
}

// Display the tree
void Tree::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	DrawTree();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

// draw the tree
void Tree::DrawTree()
{
	glPushMatrix();		// save original state

	glPopMatrix();
	glPushMatrix();
	// draw trunk
	DrawTrunk();

	glPopMatrix();
	glPushMatrix();
	// draw leaves
	DrawLeaves();

	glPopMatrix();
}

// draw the trunk
void Tree::DrawTrunk()
{
	glPushMatrix();		// save original state
	
	glColor3ub(122, 78, 6);
	GLUquadricObj* objCylinder = gluNewQuadric();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(objCylinder, trunkRadius, 0.2f * trunkRadius, trunkHeight, 5, 5);
	
	glPopMatrix();
}

// draw the leaves
void Tree::DrawLeaves()
{
	glPushMatrix();		// save original state

	// RGB for leaf color
	int Red = 12;
	int Green = 54;
	int Blue = 0;
	
	float ll = leafLength; // set the length of the leaves
	// height of the leaves increases as the loop goes
	for (float lh = leafStartHeight; lh < trunkHeight; lh += (trunkHeight - leafStartHeight) / 15.0f)
	{	
		glPopMatrix();
		glPushMatrix();
		glColor3ub(Red, Green, Blue);
		glTranslatef(0.0f, lh, 0.0f);
		// for each level, draw a cycle of leaves
		for (float i = 0.0f; i < 360.0f; i += 5.0f)
		{
			glRotatef(i, 0.0f, 1.0f, 0.0f);
			DrawLeaf(ll);
		}
		ll -= (leafLength / 15.0f);	// decrease the leave length
		
									// change the RGB of the leave color
		Green += 10;
		Red += 5;
		Blue += 0;
	}
	
	glPopMatrix();
}

// draw the leaf
void Tree::DrawLeaf(float ll)
{
	glPushMatrix();		// save original state
	
	// set the rangle between the leaves and the ground
	glRotatef(leafRotation, 1.0f, 0.0f, 0.0f);
	GLUquadricObj* objCylinder = gluNewQuadric();
	gluCylinder(objCylinder, leafRadius, 0.5f * leafRadius, ll, 2, 2);

	glPopMatrix();
}