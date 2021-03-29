#include "SunMoon.h"
#include <cmath>

// initialise the parameters in SunMoon class
SunMoon::SunMoon() : orbitRadius(60.0f), sunRadius(5.0f), animateTime(0.0f) {
	moonRadius = sunRadius;
}

// update the animation time
void SunMoon::Update(const double& deltaTime)
{
	animateTime += static_cast<float>(deltaTime);
}

// Display the sun and the moon
void SunMoon::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(animateTime * 2.0f, 0.0f, 0.0f, 1.0f);

	// draw the sun and the moon
	DrawSunMoon();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

// draw the Sun and the Moon
void SunMoon::DrawSunMoon()
{
	glPushMatrix();		// save original state

	glPopMatrix();
	glPushMatrix();
	// draw sun
	glColor3ub(255, 191, 0);
	glTranslatef(orbitRadius, 0.0f, 0.0f);
	glutSolidSphere(sunRadius, 64, 64);

	glPopMatrix();
	glPushMatrix();
	// draw moon
	glColor3ub(74, 72, 66);
	glTranslatef(-orbitRadius, 0.0f, 0.0f);
	glutSolidSphere(sunRadius, 64, 64);
	glPopMatrix();
}
