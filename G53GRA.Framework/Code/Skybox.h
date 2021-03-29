#pragma once

#include "DisplayableObject.h"

#include <string>

class Skybox :
	public DisplayableObject
{
public:
	Skybox();
	~Skybox() {}

	void Display();

private:
	void DrawSkybox();

	GLint texID1;
	GLint texID2;
	GLint texID3;
	GLint texID4;
	GLint texID5;
	GLint texID6;

};

