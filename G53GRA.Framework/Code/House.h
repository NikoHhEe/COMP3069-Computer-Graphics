#pragma once

#include "DisplayableObject.h"

class House :
	public DisplayableObject

{
public:
	House();
	~House() {};

	void Display();

private:

	void DrawHouse();		// function to draw the house
	void DrawBase();		// function to draw the base of the house
	void DrawStairs();		// function to draw stairs
	void DrawStair();		// function to draw a unit stair
	void DrawPillars();		// function to draw pillars
	void DrawPillar();		// function to draw a single pillar
	void DrawFences();		// function to draw fences
	void DrawFence();		// function to draw a single fence
	void DrawWalls();		// function to draw walls
	void DrawRoofs();		// function to draw roofs
	void DrawRoof();		// function to draw a single roof
	void DrawWindows();		// function to draw windows
	void DrawWindow();		// function to draw a sigle window
	void DrawDoor();		// function to draw a door
	void Door();			// helper function to draw a door
	
	float baseWidth;		// width of the base
	float baseLength;		// length of the base
	float baseHeight;		// height of the base
	GLint texID_base;		// texture for base
	
	float stairWidth;		// width of the base
	float stairLength;		// length of the stair
	float stairHeight;		// height of the stair

	float pillarWidth;		// width of the pillar
	float pillarLength;		// length of the pillar
	float pillarHeight;		// height of the pillar

	float fenceWidth;		// width of the fence
	float fenceLength;		// length of the fence
	float fenceHeight;		// height of the fence

	float topHeight;		// height of the top point of the house
	float wallCoord[12][3];	// coordinates of 12 vertices of the wall

	float roofWidth;		// width of the roof
	float roofLength;		// length of the roof
	float roofHeight;		// height of the roof
	float roofAngle;		// the angle between roof and floor
	GLint texID_roof;		// texture for roof

	float windowWidth;		// width of the window
	float windowLength;		// length of the window
	float windowHeight;		// height of the window
	GLint texID_window;		// texture for window

	float doorWidth;		// width of the door
	float doorLength;		// length of the door
	float doorHeight;		// height of the door
	GLint texID_door;		// texture for door

};

