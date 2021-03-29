#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Station :
	public DisplayableObject
	//public Animation

{
public:
	Station();
	~Station() {};

	void Display();

private:

	void DrawStation();		// function to draw the station
	void DrawTop();			// function to draw the top of the station
	void DrawPillar();		// function to draw the pillar of the station
 	
	float height;			// height of the station
	float length;			// length of the station
	float width;			// width of the station
	float pillarRadius;		// radius of the pillar

	GLint texID_roof;		// texture of the roof
};

