#include "MyScene.h"

#include "Floor.h"
#include "Skybox.h"
#include "House.h"
#include "Tree.h"
#include "SunMoon.h"
#include "Train.h"
#include "Station.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight){}

void MyScene::Initialise()
{
	// set the background colour of the scene to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	// add floor to the scene
	Floor* f = new Floor();
	f->position(0.0f, 0.0f, 0.0f);
	AddObjectToScene(f);

	// add skybox to the scene
	Skybox* skb = new Skybox();
	skb->size(500.0f);
	AddObjectToScene(skb);

	// add house to the scene
	House* h1 = new House();
	h1->position(0.0f, 0.25f, -15.0f);
	AddObjectToScene(h1);

	House* h2 = new House();
	h2->position(20.0f, 0.25f, -15.0f);
	AddObjectToScene(h2);

	House* h3 = new House();
	h3->position(-20.0f, 0.25f, -15.0f);
	AddObjectToScene(h3);

	// add trees to the scene
	for (float i = 0; i < 4; ++i)
	{
		Tree* t = new Tree();
		t->size(0.3f);
		t->position(-30.0f + i * 20.0f, 0.0f, -15.0f);
		AddObjectToScene(t);
	}

	for (float i = 0; i < 4; ++i)
	{
		Tree* t = new Tree();
		t->size(0.3f);
		t->position(-30.0f + i * 20.0f, 0.0f, 15.0f);
		AddObjectToScene(t);
	}

	// add sun and moon
	SunMoon* sm = new SunMoon();
	AddObjectToScene(sm);

	// add the train
	Train* tr = new Train();
	AddObjectToScene(tr);

	// add the station
	Station* st = new Station();
	AddObjectToScene(st);

}

/// set the perspective of camera
void MyScene::Projection()
{
    GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
    gluPerspective(60.0, aspect, 1.0, 50000.0);
}
