#include "Station.h"
#include <cmath>

// initialise the parameters in station class
Station::Station() : height(5.0f), pillarRadius(0.5f), width(6.0f), length(19.0f) {
	texID_roof = Scene::GetTexture("Code/resource/station-roof.bmp");
}

// Display the station
void Station::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	// station 1
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-46.0f, 0.0f, pillarRadius);
	DrawStation();

	// station 2
	glPopMatrix();
	glPushMatrix();
	glTranslatef(47.0f, 0.0f, pillarRadius);
	DrawStation();

	// station 3
	glPopMatrix();
	glPushMatrix();
	glTranslatef(pillarRadius, 0.0f, 47.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	DrawStation();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

// draw the station
void Station::DrawStation()
{
	glPushMatrix();		// save original state

	DrawTop();

	// pillar 1
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-(0.5f * width - pillarRadius), 0.0f, 0.5f * length - pillarRadius);
	DrawPillar();

	// pillar 2
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5f * width - pillarRadius, 0.0f, 0.5f * length - pillarRadius);
	DrawPillar();

	// pillar 3
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5f * width - pillarRadius, 0.0f, -(0.5f * length - pillarRadius));
	DrawPillar();

	// pillar 1
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-(0.5f * width - pillarRadius), 0.0f, -(0.5f * length - pillarRadius));
	DrawPillar();

	glPopMatrix();
}

// draw the top of the station
void Station::DrawTop()
{
	glPushMatrix();		// save original state

	glColor3ub(24, 219, 131);
	glTranslatef(0.0f, height, 0.0f);
	// set the size of the top of the station
	glScalef(width, 1.0f, length);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add texture to door 
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
	glColor3ub(255, 255, 255);
	glBegin(GL_QUADS);
	// top texture
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f * width, 0.5f + height + 0.001f, 0.5f * length);
	glTexCoord2f(19.0f, 0.0f);
	glVertex3f(0.5f * width, 0.5f + height + 0.001f, -0.5f * length);
	glTexCoord2f(19.0f, 6.0f);
	glVertex3f(-0.5f * width, 0.5f + height + 0.001f, -0.5f * length);
	glTexCoord2f(0.0f, 6.0f);
	glVertex3f(-0.5f * width, 0.5f + height + 0.001f, 0.5f * length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// draw the pillar of the  station
void Station::DrawPillar()
{
	glPushMatrix();		// save original state

	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(131, 57, 204);
	GLUquadricObj* objCylinder = gluNewQuadric();
	gluCylinder(objCylinder, pillarRadius, pillarRadius, height, 10, 10);

	glPopMatrix();
}
