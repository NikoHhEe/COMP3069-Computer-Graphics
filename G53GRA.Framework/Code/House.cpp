#include "House.h"
#include <cmath>

float pi = 3.1415926f;	// pi for trigonometric calculation

// initialise the parameters of the house class
House::House() : baseWidth(6.0f), baseLength(10.0f), baseHeight(0.5f), roofAngle(30.0f) {
	// initialise the size of the stair
	stairLength = 0.3f * baseWidth;
	stairWidth = 0.25f * baseHeight;
	stairHeight = stairWidth;

	// initialise the size of the pillar
	pillarWidth = stairWidth;
	pillarLength = stairWidth;
	pillarHeight = 0.4f * baseWidth;

	// initialise the size of the fence
	fenceWidth = pillarWidth;
	fenceLength = 0.4f * 0.5f * (baseLength - pillarLength) - pillarLength;	
	fenceHeight = 0.3f * pillarHeight;	

	// initialise the height of the house
	topHeight = pillarHeight + 0.5f * baseWidth * tan(roofAngle * pi / 180.0f);
	//printf("tan %f: %f",roofAngle, tan(roofAngle));

	// there are 6 walls corresponding to 12 vertexes, the cooridinates are stored for
	// easier coding of later wall constructions
	// vertex 1
	wallCoord[0][0] = -0.5f * baseWidth;
	wallCoord[0][1] = 0.5f * baseHeight;
	wallCoord[0][2] = 0.5f * baseLength - 2.0f * pillarLength - fenceLength;

	// vertex 2
	wallCoord[1][0] = 0.5f * baseWidth;
	wallCoord[1][1] = 0.5f * baseHeight;
	wallCoord[1][2] = 0.5f * baseLength - 2.0f * pillarLength - fenceLength;

	// vertex 3
	wallCoord[2][0] = 0.5f * baseWidth;
	wallCoord[2][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[2][2] = 0.5f * baseLength - 2.0f * pillarLength - fenceLength;

	// vertex 4
	wallCoord[3][0] = -0.5f * baseWidth;
	wallCoord[3][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[3][2] = 0.5f * baseLength - 2.0f * pillarLength - fenceLength;

	// vertex 5
	wallCoord[4][0] = -0.5f * baseWidth;
	wallCoord[4][1] = 0.5f * baseHeight;
	wallCoord[4][2] = -0.5f * baseLength;

	// vertex 6
	wallCoord[5][0] = 0.5f * baseWidth;
	wallCoord[5][1] = 0.5f * baseHeight;
	wallCoord[5][2] = -0.5f * baseLength;

	// vertex 7
	wallCoord[6][0] = 0.5f * baseWidth;
	wallCoord[6][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[6][2] = -0.5f * baseLength;

	// vertex 8
	wallCoord[7][0] = 0.0f;
	wallCoord[7][1] = 0.5f * baseHeight + topHeight;
	wallCoord[7][2] = -0.5f * baseLength;

	// vertex 9
	wallCoord[8][0] = -0.5f * baseWidth;
	wallCoord[8][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[8][2] = -0.5f * baseLength;

	// vertex 10
	wallCoord[9][0] = -0.5f * baseWidth;
	wallCoord[9][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[9][2] = 0.5f * baseLength;

	// vertex 11
	wallCoord[10][0] = 0.5f * baseWidth;
	wallCoord[10][1] = 0.5f * baseHeight + pillarHeight;
	wallCoord[10][2] = 0.5f * baseLength;

	// vertex 12
	wallCoord[11][0] = 0.0f;
	wallCoord[11][1] = 0.5f * baseHeight + topHeight;
	wallCoord[11][2] = 0.5f * baseLength;

	// load the roof texture
	texID_roof = Scene::GetTexture("Code/resource/roof.bmp");
	// initialise the size of the roof
	roofHeight = stairWidth;
	roofWidth = 0.5f * baseWidth / cos(roofAngle *pi / 180.0f) + 2.0f * roofHeight * tan(roofAngle * pi / 180.0f);
	roofLength = 1.05f * baseLength;

	// load the window texture
	texID_window = Scene::GetTexture("Code/resource/window.bmp");
	// initialise the size of the window
	windowWidth = 0.5f * stairWidth;
	windowHeight = 0.6f * pillarHeight;
	windowLength = 0.65f * windowHeight;

	// load the door texture
	texID_door = Scene::GetTexture("Code/resource/brown-door.bmp");
	// initialise the size of the door
	doorWidth = 0.5f * stairWidth;
	doorHeight = pillarHeight;
	doorLength = stairLength;

	// load the floor texture
	texID_base = Scene::GetTexture("Code/resource/floor.bmp");
}

// Display the house
void House::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	// draw the house
	DrawHouse();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

// draw the house
void House::DrawHouse()
{
	glPushMatrix();		// save original state
	
	// draw base 
	glPopMatrix();
	glPushMatrix();
	DrawBase();

	// move to front of the base to draw stairs
	glTranslatef(0.0f, 0.0f, 0.5f * baseLength + 3.5f * stairWidth);
	// draw stairs
	DrawStairs();

	// draw pillars
	glPopMatrix();
	glPushMatrix();
	DrawPillars();

	// draw fences
	glPopMatrix();
	glPushMatrix();
	DrawFences();

	// draw walls
	glPopMatrix();
	glPushMatrix();
	DrawWalls();

	// draw roofs
	glPopMatrix();
	glPushMatrix();
	DrawRoofs();

	// draw windows
	glPopMatrix();
	glPushMatrix();
	DrawWindows();

	// draw a door
	glPopMatrix();
	glPushMatrix();
	DrawDoor();

	// add a beam over the doorway
	glPopMatrix();
	glPushMatrix();
	glColor3ub(150, 150, 150);
	glTranslatef(0.0f, 0.5f * (baseHeight - pillarWidth) + pillarHeight, 0.5f * (baseLength - pillarLength));
	glScalef(baseWidth / stairLength, 1.0f, 1.0f);
	DrawStair();

	glPopMatrix();
}

// draw the base
void House::DrawBase()
{
	glPushMatrix();
	// set base size
	glScalef(baseWidth, baseHeight, baseLength);
	glColor3ub(150, 150, 150);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add floor texture to the top of the base 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_base);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * baseWidth, 0.5f * baseHeight + 0.001f, -0.5f * baseLength);
	glTexCoord2f(6.0f, 0.0f);
	glVertex3f(-0.5f * baseWidth, 0.5f * baseHeight + 0.001f, 0.5f * baseLength);
	glTexCoord2f(6.0f, 3.0f);
	glVertex3f(0.5f * baseWidth, 0.5f * baseHeight + 0.001f, 0.5f * baseLength);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(0.5f * baseWidth, 0.5f * baseHeight + 0.001f, -0.5f * baseLength);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// draw the stairs
void House::DrawStairs()
{
	glPushMatrix();
	// first level, 4 stairs
	glColor3ub(100, 100, 100);
	glTranslatef(0.0f, -1.5f * stairHeight, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		DrawStair();
		if (i < 3)
		{
			glTranslatef(0.0f, 0.0f, -stairWidth);
		}
	}
	
	// second level, 3 stairs
	glTranslatef(0.0f, stairWidth, 0.0f);
	for (int i = 0; i < 3; i++)
	{
		DrawStair();
		if (i < 2)
		{
			glTranslatef(0.0f, 0.0f, stairWidth);
		}
	}

	// third level, 2 stairs
	glTranslatef(0.0f, stairWidth, 0.0f);
	glTranslatef(0.0f, 0.0f, -stairWidth);
	DrawStair();
	glTranslatef(0.0f, 0.0f, -stairWidth);
	DrawStair();

	// fourth level, 1 stair
	glTranslatef(0.0f, stairWidth, 0.0f);
	DrawStair();

	glPopMatrix();
}

// draw a unit stair
void House::DrawStair()
{
	glPushMatrix();
	// set the size of the stair
	glScalef(stairLength, stairHeight, stairWidth);
	glutSolidCube(1.0f);
	glPopMatrix();
}

// draw the pillars
void House::DrawPillars()
{
	glPushMatrix();
	glColor3ub(150, 150, 150);
	// pillar 1
	glTranslatef(-0.5f * (baseWidth - pillarWidth), 0.5f * (pillarHeight + baseHeight), 0.6f * 0.5f * (baseLength - pillarWidth));
	DrawPillar();

	// pillar 2
	glTranslatef(0.0f, 0.0f, 0.4f * 0.5f * (baseLength - pillarWidth));
	DrawPillar();

	// pillar 3
	glTranslatef(0.5f * (baseWidth - stairLength) - pillarLength, 0.0f, 0.0f);
	DrawPillar();

	// pillar 4
	glTranslatef(stairLength + pillarLength, 0.0f, 0.0f);
	DrawPillar();

	// pillar 5
	glTranslatef(0.5f * (baseWidth - stairLength) - pillarLength, 0.0f, 0.0f);
	DrawPillar();

	// pillar 6
	glTranslatef(0.0f, 0.0f, -(0.4f * 0.5f * (baseLength - pillarWidth)));
	DrawPillar();

	glPopMatrix();
}

// draw a single pillar
void House::DrawPillar()
{
	glPushMatrix();
	// set the size of the pillar
	glScalef(pillarWidth, pillarHeight, pillarLength);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void House::DrawFences()
{
	glPushMatrix();
	glColor3ub(65, 120, 119);

	// fence 1
	glPopMatrix();
	glTranslatef(0.0f, 0.5f * (fenceHeight + baseHeight), 0.0f);
	glPushMatrix();
	glTranslatef(-0.5f * (baseWidth - 2.0f * pillarWidth - fenceLength), 0.0f, 0.5f * (baseLength - pillarLength));
	DrawFence();

	// fence 2
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5f * (baseWidth - 2.0f * pillarWidth - fenceLength), 0.0f, 0.5f * (baseLength - pillarLength));
	DrawFence();

	// fence 3
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5f * (baseWidth - pillarWidth), 0.0f, 0.8f * 0.5f * (baseLength - pillarLength));
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	DrawFence();

	// fence 4
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5f * (baseWidth - pillarWidth), 0.0f, 0.8f * 0.5f * (baseLength - pillarLength));
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawFence();

	glPopMatrix();
}

void House::DrawFence()
{
	glPushMatrix();
	// set the size of the fence
	glScalef(fenceLength, fenceHeight, fenceWidth);
	glutSolidCube(1.0f);
	glPopMatrix();
}

void House::DrawWalls()
{
	glPushMatrix();

	glColor3ub(255, 204, 117);
	
	// front wall
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(wallCoord[0][0], wallCoord[0][1], wallCoord[0][2]);
	glVertex3f(wallCoord[1][0], wallCoord[1][1], wallCoord[1][2]);
	glVertex3f(wallCoord[2][0], wallCoord[2][1], wallCoord[2][2]);
	glVertex3f(wallCoord[3][0], wallCoord[3][1], wallCoord[3][2]);
	glEnd();

	// left wall
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(wallCoord[4][0], wallCoord[4][1], wallCoord[4][2]);
	glVertex3f(wallCoord[0][0], wallCoord[0][1], wallCoord[0][2]);
	glVertex3f(wallCoord[3][0], wallCoord[3][1], wallCoord[3][2]);
	glVertex3f(wallCoord[8][0], wallCoord[8][1], wallCoord[8][2]);
	glEnd();

	// right wall
	glBegin(GL_QUADS);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(wallCoord[1][0], wallCoord[1][1], wallCoord[1][2]);
	glVertex3f(wallCoord[5][0], wallCoord[5][1], wallCoord[5][2]);
	glVertex3f(wallCoord[6][0], wallCoord[6][1], wallCoord[6][2]);
	glVertex3f(wallCoord[2][0], wallCoord[2][1], wallCoord[2][2]);
	glEnd();

	// back wall
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(wallCoord[6][0], wallCoord[6][1], wallCoord[6][2]);
	glVertex3f(wallCoord[5][0], wallCoord[5][1], wallCoord[5][2]);
	glVertex3f(wallCoord[4][0], wallCoord[4][1], wallCoord[4][2]);
	glVertex3f(wallCoord[8][0], wallCoord[8][1], wallCoord[8][2]);
	glVertex3f(wallCoord[7][0], wallCoord[7][1], wallCoord[7][2]);
	glEnd();

	// suspending wall
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(wallCoord[2][0], wallCoord[2][1], wallCoord[3][2]);
	glVertex3f(wallCoord[10][0], wallCoord[10][1], wallCoord[10][2]);
	glVertex3f(wallCoord[9][0], wallCoord[9][1], wallCoord[9][2]);
	glVertex3f(wallCoord[3][0], wallCoord[3][1], wallCoord[3][2]);
	glEnd();

	// front trangle wall
	glColor3ub(158, 60, 24);
	glBegin(GL_TRIANGLES);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(wallCoord[9][0], wallCoord[9][1], wallCoord[9][2]);
	glVertex3f(wallCoord[10][0], wallCoord[10][1], wallCoord[10][2]);
	glColor3ub(64, 0, 161);
	glVertex3f(wallCoord[11][0], wallCoord[11][1], wallCoord[11][2]);
	glEnd();

	glPopMatrix();
}

void House::DrawRoofs()
{
	glPushMatrix();

	glPopMatrix();
	glPushMatrix();
	// left half roof
	glColor3ub(150, 150, 150);
	glTranslatef(-(0.25f * baseWidth + 0.5f * roofHeight * sin(roofAngle * pi / 180.0f)), 0.5f * baseHeight + pillarHeight + 0.25f * baseWidth * tan(roofAngle * pi / 180.0f) + 0.5f * roofHeight * cos(roofAngle * pi / 180.0f), 0.0f);
	glRotatef(roofAngle, 0.0f, 0.0f, 1.0f);
	DrawRoof();

	glPopMatrix();
	glPushMatrix();
	// right half roof
	glTranslatef(0.25f * baseWidth + 0.5f * roofHeight * sin(roofAngle * pi / 180.0f), 0.5f * baseHeight + pillarHeight + 0.25f * baseWidth * tan(roofAngle * pi / 180.0f) + 0.5f * roofHeight * cos(roofAngle * pi / 180.0f), 0.0f);
	glRotatef(-roofAngle, 0.0f, 0.0f, 1.0f);
	DrawRoof();

	glPopMatrix();
}

void House::DrawRoof()
{
	glPushMatrix();

	// set the size of the roof
	glScalef(roofWidth, roofHeight, roofLength);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add texture to roof 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * roofWidth, 0.5f * roofHeight + 0.001f, -0.5f * roofLength);
	glTexCoord2f(6.0f, 0.0f);
	glVertex3f(-0.5f * roofWidth, 0.5f * roofHeight + 0.001f, 0.5f * roofLength);
	glTexCoord2f(6.0f, 3.0f);
	glVertex3f(0.5f * roofWidth, 0.5f * roofHeight + 0.001f, 0.5f * roofLength);
	glTexCoord2f(0.0f, 3.0f);
	glVertex3f(0.5f * roofWidth, 0.5f * roofHeight + 0.001f, -0.5f * roofLength);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void House::DrawWindows()
{
	glPushMatrix();

	glPopMatrix();
	glPushMatrix();
	// front window 1
	glTranslatef(-0.5f * (baseWidth - pillarLength - fenceLength), 0.5f * (baseHeight + pillarHeight), 0.6f * 0.5f * (baseLength - pillarLength));
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// front window 2
	glTranslatef(0.5f * (baseWidth - pillarLength - fenceLength), 0.5f * (baseHeight + pillarHeight), 0.6f * 0.5f * (baseLength - pillarLength));
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// back window 1
	glTranslatef(-0.5f * (baseWidth - pillarLength - fenceLength), 0.5f * (baseHeight + pillarHeight), -0.5f * baseLength);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// back window 2
	glTranslatef(0.5f * (baseWidth - pillarLength - fenceLength), 0.5f * (baseHeight + pillarHeight), -0.5f * baseLength);
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// left window 1
	glTranslatef(-0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), 1.5f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// left window 2
	glTranslatef(-0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), -1.0f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// left window 3
	glTranslatef(-0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), -3.5f);
	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// right window 1
	glTranslatef(0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), 1.5f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// right window 2
	glTranslatef(0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), -1.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
	glPushMatrix();
	// right window 3
	glTranslatef(0.5f * baseWidth, 0.5f * (baseHeight + pillarHeight), -3.5f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawWindow();

	glPopMatrix();
}

void House::DrawWindow()
{
	glPushMatrix();
	
	// set the size of the window
	glScalef(windowLength, windowHeight, windowWidth);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add texture to window 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID_window);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * windowLength, -0.5f * windowHeight, 0.5f * windowWidth + 0.001f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f * windowLength, -0.5f * windowHeight, 0.5f * windowWidth + 0.001f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f * windowLength, 0.5f * windowHeight, 0.5f * windowWidth + 0.001f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f * windowLength, 0.5f * windowHeight, 0.5f * windowWidth + 0.001f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}

void House::DrawDoor()
{
	glPushMatrix();

	glTranslatef(0.0f, 0.5f * (baseHeight + pillarHeight), 0.6f * 0.5f * (baseLength - pillarLength));
	Door();

	glPopMatrix();
}

void House::Door()
{
	glPushMatrix();

	// set the size of the door
	glScalef(doorLength, doorHeight, doorWidth);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add texture to door 
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID_door);

	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * doorLength, -0.5f * doorHeight, 0.5f * doorWidth + 0.001f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f * doorLength, -0.5f * doorHeight, 0.5f * doorWidth + 0.001f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f * doorLength, 0.5f * doorHeight, 0.5f * doorWidth + 0.001f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f * doorLength, 0.5f * doorHeight, 0.5f * doorWidth + 0.001f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}