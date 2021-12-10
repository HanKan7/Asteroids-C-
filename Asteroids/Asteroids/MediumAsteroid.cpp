#include "MediumAsteroid.h"

void MediumAsteroid::InitMediumAsteroid(int index, int radius, Vector2f initialPosition, Vector2f initialVelocity)
{
	this->initialPostion = initialPosition;
	if (parentIndex % 2 == 0)	this->initialVelocity = -initialVelocity;
	else this->initialVelocity = initialVelocity;
	asteroidVelocity = initialVelocity;
	asteroid.setPosition(initialPostion);
}
