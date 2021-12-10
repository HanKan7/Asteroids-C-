#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<iostream>
#include<math.h>
#include "Math.h"
#include<iostream>
using namespace std;
using namespace sf;
class Asteroid
{
public:
	CircleShape asteroid;
	Vector2f size;
	Vector2f initialPostion;
	Vector2f initialVelocity;
	Vector2f asteroidVelocity;
	Vector2f assignedPosition;
	

	vector<Vector2f> positionVector = {
									   Vector2f(20, 0),  Vector2f(220, 20),  Vector2f(420, 20) ,  Vector2f(720, 20),
									   Vector2f(120, 120), Vector2f(520, 120), 
									   Vector2f(20, 220),  Vector2f(720, 220),
									   Vector2f(120, 320), Vector2f(220, 320),  Vector2f(720, 320),
									   Vector2f(120, 420),  Vector2f(520, 420), 
									    Vector2f(120, 520), Vector2f(520, 520), Vector2f(720, 520),
									  };

	vector<Vector2f> velocityVector = {
								   Vector2f(-20, 20),  Vector2f(120, 20),  Vector2f(-220, -20),  Vector2f(320, 20),  Vector2f(42, 20) ,  Vector2f(-52, -20),  Vector2f(60, 20),  Vector2f(72, 20),
								   Vector2f(20, -12), Vector2f(-10, 12), Vector2f(220, 12), Vector2f(-30, -12), Vector2f(42, 12) , Vector2f(-50, -12), Vector2f(-20, 12), Vector2f(70, -12),
								   Vector2f(20, -22), Vector2f(120, -22), Vector2f(-20, -22), Vector2f(20, 20), Vector2f(-42, -20) , Vector2f(-52, -22), Vector2f(60, 22), Vector2f(-72, 22),
								   Vector2f(-20, 32), Vector2f(120, -32), Vector2f(20, -32), Vector2f(-30, 30), Vector2f(42, -32) , Vector2f(-52, -30), Vector2f(62, -32), Vector2f(72, 32),
								   Vector2f(20, 42), Vector2f(-12, -40), Vector2f(22, 42), Vector2f(32, -40), Vector2f(42, 40) , Vector2f(-52, 42), Vector2f(-62, 42), Vector2f(72, -42),
								   Vector2f(-20, 52), Vector2f(120, -50), Vector2f(20, 50), Vector2f(32, 52),
	};

	Texture texture;
	Sprite asteroidSprite;
	
	float radius;
	int childIndex1, childIndex2, parentIndex;
	bool isDead, isBigAsteroid, valuesHaveBeenPassed = false, isDisabled = true;;

	int scoreIncrementOnDestroy = 10;

	Asteroid(int index, int radius, int scoreIncrement, bool isBigAsteroid);
	void UpdateMovement(RenderWindow* window, float deltaTime);
	void AsteroidToAsteroidCollision(Asteroid* asteroid);
};

