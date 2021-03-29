#include "Train.h"
#include <cmath>

// initialize the parameters of the Train object
Train::Train() : railOuterRadius(48.3f), railWidth(0.1f), carriageWidth(2.0f), 
				 wheelWidth(0.1f), animateTime(0.0f), roundTime(40.0f) {
	// calculate the radius of the inner rail
	railInnerRadius = railOuterRadius - carriageWidth - wheelWidth;
	
	// calcualte the size of the crosstie
	crosstieWidth = 4.0f * railWidth;
	crosstieHeight = 0.25f * crosstieWidth;
	crosstieLength = 1.2f * (carriageWidth + wheelWidth);
	
	// calculate the size of the carriage
	carriageLength = 2.0f * carriageWidth;	// length of the carriage
	carriageHeight = carriageWidth;			// Height of the carriage
	
	// load the textures of the train
	texID_train = Scene::GetTexture("Code/resource/train.bmp");
	texID_train_top = Scene::GetTexture("Code/resource/train-top.bmp");
	texID_train_front = Scene::GetTexture("Code/resource/train-front.bmp");

	// calcualte the radius of the wheel
	wheelRadius = 0.2f * carriageHeight;

	// calculate the size of the chimney
	chimneyHeight = carriageHeight;
	chimneyRadius = wheelRadius;

}

// update animation time
void Train::Update(const double& deltaTime)
{
	animateTime += static_cast<float>(deltaTime);
}

// Display the windmill with dynamic rotation
void Train::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	
	glPopMatrix();
	glPushMatrix();
	// draw rail
	DrawRail();

	glPopMatrix();
	glPushMatrix();
	// draw train
	
	glRotatef(animateTime * 360.0f / roundTime, 0.0f, 1.0f, 0.0f);	// train animation
	DrawTrain();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

// draw the train
void Train::DrawTrain()
{
	glPushMatrix();		// save original state
	
	// chimney of the first carriage
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.25f * carriageLength, carriageHeight, -0.5f * (railOuterRadius + railInnerRadius));
	DrawChimney();

	glPopMatrix();
	glPushMatrix();
	// draw the first carriage and the following carriages
	DrawCarriage();
	for (int i = 0; i < 10; ++i)
	{
		glRotatef(-6.0f, 0.0f, 1.0f, 0.0f);
		DrawCarriage();
	}
	glPopMatrix();
}

// draw the rail
void Train::DrawRail()
{
	glPushMatrix();		// save original state
	
	glPopMatrix();
	glPushMatrix();
	glColor3ub(31, 31, 31);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	// outer rail
	glutSolidTorus(railWidth, railOuterRadius + 0.5f * railWidth, 100, 100);

	// inner rail
	glutSolidTorus(railWidth, railInnerRadius + 0.5f * railWidth, 100, 100);

	glPopMatrix();
	glPushMatrix();
	// rotate to draw a cycle of crossties
	for (float i = 0.0f; i < 360.0f; ++i)
	{
		glRotatef(1.0f, 0.0f, 1.0f, 0.0f);
		DrawCrosstie();
	}

	glPopMatrix();
}

// draw the crosstie
void Train::DrawCrosstie()
{
	glPushMatrix();

	glColor3ub(51, 33, 5);
	// move the crosstie to the center of the inner nad outer rails
	glTranslatef(0.0f, 0.0f, -0.5f * (railOuterRadius + railInnerRadius));
	// set the size of the crosstie
	glScalef(crosstieWidth, crosstieHeight, crosstieLength);
	glutSolidCube(1.0f);

	glPopMatrix();
}

// draw the carriages
void Train::DrawCarriage() 
{
	glPushMatrix();

	// body
	glColor3ub(255, 255, 255);
	glTranslatef(0.0f, 0.5f * carriageHeight + wheelRadius + 0.2f * wheelRadius, -0.5f * (railOuterRadius + railInnerRadius));
	glPushMatrix();
	Carriage();

	glPopMatrix();
	glPushMatrix();
	// wheel 1
	glTranslatef(-0.25f * carriageLength, -0.5f * carriageHeight, 0.5f * (carriageWidth + wheelWidth));
	DrawWheel();

	glPopMatrix();
	glPushMatrix();
	// wheel 2
	glTranslatef(0.25f * carriageLength, -0.5f * carriageHeight, 0.5f * (carriageWidth + wheelWidth));
	DrawWheel();

	glPopMatrix();
	glPushMatrix();
	// wheel 3
	glTranslatef(-0.25f * carriageLength, -0.5f * carriageHeight, -0.5f * (carriageWidth + wheelWidth));
	DrawWheel();

	glPopMatrix();
	glPushMatrix();
	// wheel 4
	glTranslatef(0.25f * carriageLength, -0.5f * carriageHeight, -0.5f * (carriageWidth + wheelWidth));
	DrawWheel();

	glPopMatrix();
	glPushMatrix();
	// connection between carriages
	glColor3ub(42, 128, 122);
	glTranslatef(0.5f * carriageLength, -0.5f * carriageHeight, 0.0f);
	glScalef(2.0f, 0.2f, 0.2f);
	glutSolidCube(1.0);

	glPopMatrix();
	glPopMatrix();
}

// draw a single carriage
void Train::Carriage()
{
	glPushMatrix();

	// set the size of the carriage
	glScalef(carriageLength, carriageHeight, carriageWidth);
	glutSolidCube(1.0f);

	glPopMatrix();
	glPushMatrix();
	// add texture to door 
	glEnable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID_train);

	glBegin(GL_QUADS);
	// left side texture
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * carriageLength, -0.5f * carriageHeight, 0.5f * carriageWidth + 0.001f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f * carriageLength, -0.5f * carriageHeight, 0.5f * carriageWidth + 0.001f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f * carriageLength, 0.5f * carriageHeight, 0.5f * carriageWidth + 0.001f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f * carriageLength, 0.5f * carriageHeight, 0.5f * carriageWidth + 0.001f);
	
	// right side texture
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f * carriageLength, -0.5f * carriageHeight, -(0.5f * carriageWidth + 0.001f));
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f * carriageLength, -0.5f * carriageHeight, -(0.5f * carriageWidth + 0.001f));
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f * carriageLength, 0.5f * carriageHeight, -(0.5f * carriageWidth + 0.001f));
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f * carriageLength, 0.5f * carriageHeight, -(0.5f * carriageWidth + 0.001f));
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID_train_top);
	glBegin(GL_QUADS);
	// top texture
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f * carriageLength, 0.5f * carriageHeight + 0.001f, 0.5f * carriageWidth);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f * carriageLength, 0.5f * carriageHeight + 0.001f, 0.5f * carriageWidth);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f * carriageLength, 0.5f * carriageHeight + 0.001f, -0.5f * carriageWidth);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f * carriageLength, 0.5f * carriageHeight + 0.001f, -0.5f * carriageWidth);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texID_train_front);
	glBegin(GL_QUADS);
	// front texture
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-(0.5f * carriageLength + 0.001f), -0.5f * carriageHeight, -0.5f * carriageWidth);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-(0.5f * carriageLength + 0.001f), -0.5f * carriageHeight, 0.5f * carriageWidth);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-(0.5f * carriageLength + 0.001f), 0.5f * carriageHeight, 0.5f * carriageWidth);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-(0.5f * carriageLength + 0.001f), 0.5f * carriageHeight, -0.5f * carriageWidth);
	
	// back texture
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f * carriageLength + 0.001f, -0.5f * carriageHeight, 0.5f * carriageWidth);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f * carriageLength + 0.001f, -0.5f * carriageHeight, -0.5f * carriageWidth);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f * carriageLength + 0.001f, 0.5f * carriageHeight, -0.5f * carriageWidth);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f * carriageLength + 0.001f, 0.5f * carriageHeight, 0.5f * carriageWidth);

	glEnd();

	//glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

// draw a single wheel
void Train::DrawWheel()
{
	glPushMatrix();

	glColor3ub(255, 0, 0);
	glRotatef(animateTime * 500.0f, 0.0f, 0.0f, 1.0f);
	glutSolidTorus(0.1f * wheelRadius, wheelRadius, 10, 10);

	glColor3ub(0, 0, 0);
	
	// draw the spokes of the wheel
	for (int i = 0; i < 5; ++i)
	{
		glRotatef(36.0f, 0.0f, 0.0f, 1.0f);
		DrawSpokes();
	}

	glPopMatrix();
}

// draw the spokes on the wheel
void Train::DrawSpokes()
{
	glPushMatrix();

	glScalef(0.1f * wheelRadius, 2.0f * wheelRadius, 0.1f * wheelRadius);
	glutSolidCube(1.0f);

	glPopMatrix();
}

// draw the chimney
void Train::DrawChimney()
{
	glPushMatrix();

	glPopMatrix();
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(148, 143, 6);
	GLUquadricObj* objCylinder = gluNewQuadric();
	gluCylinder(objCylinder, chimneyRadius, chimneyRadius, chimneyHeight, 10, 10);

	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0f, chimneyHeight, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidTorus(0.2f * wheelRadius, chimneyRadius, 10, 10);

	glPopMatrix();
}