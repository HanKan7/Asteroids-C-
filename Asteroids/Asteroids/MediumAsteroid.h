#pragma once
#include"Asteroid.h"
class MediumAsteroid : public Asteroid
{
public:
	bool areValuesAssigned = false;
	int parentOfMedIndex = parentIndex;
	int childOfMedIndex1 = parentOfMedIndex * 2;
	int childOfMedIndex2 = parentOfMedIndex * 2 + 1;
	
	MediumAsteroid() = default;
	void InitMediumAsteroid(int index, int radius, Vector2f initialPosition, Vector2f initialVelocity);
};

