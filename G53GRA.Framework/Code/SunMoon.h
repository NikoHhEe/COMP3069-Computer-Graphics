#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class SunMoon :
	public DisplayableObject,
	public Animation

{
public:
	SunMoon();
	~SunMoon() {};

	void Display();
	void Update(const double& deltaTime);

private:

	void DrawSunMoon();		// function to draw the sun and the moon
	
	float orbitRadius;		// the radius of the orbit of sun and moon
	float sunRadius;		// radius of the sun
	float moonRadius;		// radius of the moon
	float animateTime;		// time of the animation

};

