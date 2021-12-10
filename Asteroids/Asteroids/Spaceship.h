#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<math.h>
#include "GameManager.h"
#include"Asteroid.h"
#include<iostream>

using namespace std;
using namespace sf;
class Spaceship
{
public:
	RectangleShape ship;
	RectangleShape thruster;
	Vector2f Size;
	Vector2f InitialPostion;
	Vector2f shipVelocity = Vector2f(0.f, 0.f);
	Color color;
	FloatRect shipRect;
	Vector2i prevMousPos = sf::Vector2i(0, 0);
	Texture texture;
	Texture fireTexture;
	float speed;
	float angle = -90.f;
	float lastAngle = -90.f;
	bool isDead = false;
	bool justDied = false;
	bool disableMesh = false;
	bool disableFire;
	Clock respawnClock;
	float respawnTimer = 3.f;
	float hitTime = 0;
	Vector2f currentShipPos;

	float rotationSpeed = 10;

	Spaceship();
	Vector2f Rotate(Vector2f vec, float angle, bool clockWise);
	void Movement(float deltaTime);
	void WarpShip(RenderWindow* window);
	Vector2f Velocity(float speed);
	Vector2f Direction(float ang);
	void ContinueMovement(float speede, float deltTime);
	void CollisionWithAsteroid(Asteroid* asteroid, GameManager* gameManager);
	void DisableMesh(int shipClock);

};

