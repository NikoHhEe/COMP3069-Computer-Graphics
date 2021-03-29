#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Train :
	public DisplayableObject,
	public Animation

{
public:
	Train();
	~Train() {};

	void Display();
	void Update(const double& deltaTime);

private:

	void DrawRail();		// function to draw the railway
	void DrawCrosstie();	// function to draw the crossties of the rail

	void DrawTrain();		// function to draw the sun train
	void DrawCarriage();	// function to draw the carriage of the train
	void Carriage();
	void DrawWheel();		// function to draw the wheel of the train
	void DrawSpokes();		// function to draw the spoke of the wheel
	void DrawChimney();		// function to draw the chimney of the first carriage
	
	float railOuterRadius;	// radius of the outer rail
	float railInnerRadius;	// radius of the inner rail
	float railWidth;		// width of the single rail

	float crosstieWidth;	// width of the crosstie
	float crosstieHeight;	// height of the crosstie
	float crosstieLength;	// length of the crosstie

	float carriageLength;	// length of the carriage
	float carriageWidth;	// width of the carriage
	float carriageHeight;	// Height of the carriage
	GLint texID_train;		// texture of the train
	GLint texID_train_top;	// texture of the train top
	GLint texID_train_front;// texture of the train front

	float wheelRadius;		// radius of the wheel
	float wheelWidth;		// width of the wheel

	float chimneyHeight;	// height of the chimney
	float chimneyRadius;	// radius of the chimney

	float animateTime;		// time of the animation
	float roundTime;		// time of one cycle of the train
};

