#include "Skybox.h"
#include "iostream"

Skybox::Skybox()
{
	texID1 = Scene::GetTexture("Code/skybox/back.bmp");
	texID2 = Scene::GetTexture("Code/skybox/front.bmp");
	texID3 = Scene::GetTexture("Code/skybox/left.bmp");
	texID4 = Scene::GetTexture("Code/skybox/right.bmp");
	texID5 = Scene::GetTexture("Code/skybox/top.bmp");
	texID6 = Scene::GetTexture("Code/skybox/bottom.bmp");
}

void Skybox::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);

	DrawSkybox();
	
	glPopAttrib();
	glPopMatrix();
}

void Skybox::DrawSkybox()
{
	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Enable setting the colour of the material the cube is made from
	// as well as the material for blending.
	glEnable(GL_COLOR_MATERIAL);

	// Tell openGL which texture buffer to use

	glBindTexture(GL_TEXTURE_2D, texID1);
	glBegin(GL_QUADS);

	// draw the front sky

	// set the colour of the front sky
	glColor3f(1.0f, 1.0f, 1.0f);

	// set the normal of the front sky
	glNormal3f(0.0f, 0.0f, -1.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID2);
	glBegin(GL_QUADS);
	// draw the back sky

	// set the normal of the back sky
	glNormal3f(0.0f, 0.0f, 1.0f);

	// define texture coordinates for the 4 vertices

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID3);
	glBegin(GL_QUADS);
	// draw the left sky

	// set the normal of the left sky
	glNormal3f(1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID4);
	glBegin(GL_QUADS);
	// draw the right sky

	// set the normal of the right sky
	glNormal3f(-1.0f, 0.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID5);
	glBegin(GL_QUADS);
	// draw the top sky

	// set the normal of the top sky
	glNormal3f(0.0f, -1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID6);
	glBegin(GL_QUADS);
	// draw the bottom sky

	// set the normal of the bottom sky
	glNormal3f(0.0f, 1.0f, 0.0f);

	// define texture coordinates for the 4 vertices
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);

	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}
