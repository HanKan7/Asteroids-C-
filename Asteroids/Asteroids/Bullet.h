#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<math.h>
#include "Math.h"
#include<iostream>

class Bullet
{
public:
	CircleShape bullet;
	Color color;
	Vector2f direction;
	Clock bulletClock;
	float radius;
	float bulletSpeed = 2000.f;
	float bulletLifeTime = 5.f;
	bool shoulGoBackToInitialPosition;

	float clockValue;
	bool bulletSpawned = false;

	void SpawnBullet(Vector2f shipPosition);
	void StickToShip(Vector2f shipPosition);
	void BulletMovement(Vector2f shipPosition, Vector2f directionToFace, float deltaTime, float winX, float winY);
	void WarpBullet(RenderWindow* window);
};

