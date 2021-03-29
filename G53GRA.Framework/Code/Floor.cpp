#include "Floor.h"

void Floor::Display()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_COLOR_MATERIAL);
	float bDiffuse[] = {1.0f,0.0f,0.0f,1.0f};
	float wDiffuse[] = {1.0f,1.0f,1.0f,1.0f};
	float specular[] = {1.0f,1.0f,1.0f,1.0f};
	float shininess = 64.0f;
	int floorSize = 50;

	// load the texture of soil
	GLint texID_main = Scene::GetTexture("Code/resource/dry-ground.bmp");
	// load the texture of railway ground
	GLint texID_rock = Scene::GetTexture("Code/resource/floor-smooth.bmp");
	// load the texture of road
	GLint texID_stone = Scene::GetTexture("Code/resource/floor-stone.bmp");
	// load the texture of water
	GLint texID_water = Scene::GetTexture("Code/resource/water.bmp");

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Enable setting the colour of the material the cube is made from
	// as well as the material for blending.
	glEnable(GL_COLOR_MATERIAL);

	// Tell openGL which texture buffer to use

	// apply the texture of soil to the whole circular floor
	glBindTexture(GL_TEXTURE_2D, texID_main);

	glBegin(GL_QUADS);

	for (int i = -floorSize; i < floorSize; i++)
	{
		for (int j = -floorSize; j < floorSize; j++)
		{
			// generate a circular region
			if (sqrt(i * i + j * j) >= floorSize)
				continue;
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j) + scale[2]);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j) + scale[2]);

			
		}
	}
	glEnd();

	// load the texture of railway ground
	glBindTexture(GL_TEXTURE_2D, texID_rock);
	glBegin(GL_QUADS);
	for (int i = -floorSize; i < floorSize; i++)
	{
		for (int j = -floorSize; j < floorSize; j++)
		{
			// generate a  circular ring region for the railway
			if (sqrt(i * i + j * j) <= 44.0f || sqrt(i * i + j * j) >= floorSize)
				continue;

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j) + scale[2]);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j) + scale[2]);


		}
	}
	glEnd();

	// load the texture of water
	glBindTexture(GL_TEXTURE_2D, texID_water);
	glBegin(GL_QUADS);
	for (int i = -floorSize; i < floorSize; i++)
	{
		for (int j = -floorSize; j < floorSize; j++)
		{
			// determine the area of the water
			if (sqrt(i * i + j * j) < 40 && (j > 15 || j < -25))
			{
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j) + scale[2]);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j));
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j) + scale[2]);

			}

		}
	}
	glEnd();

	// load the texture of the road
	glBindTexture(GL_TEXTURE_2D, texID_stone);
	glBegin(GL_QUADS);
	for (int i = -floorSize; i < floorSize; i++)
	{
		for (int j = -floorSize; j < floorSize; j++)
		{
			// determine the area of the road
			if (j == -1 || j == 0 || j == 1 || ((i == -1 || i == 0) && j > -11) || ((i == -21 || i == -20 || i == 19 || i == 20) && (j > -11 && j < 0)))
			{
				glNormal3f(0.0f, 1.0f, 0.0f);
				glTexCoord2f(0.0f, 0.0f);
				glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j) + scale[2]);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 0.0f, scale[2] * static_cast<float>(j));
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j));
				glTexCoord2f(1.0f, 0.0f);
				glVertex3f(scale[0] * static_cast<float>(i), 0.0f, scale[2] * static_cast<float>(j) + scale[2]);

			}

		}
	}
	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}