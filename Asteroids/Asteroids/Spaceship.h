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

using namespace std;
using namespace sf;
class Spaceship
{
public:
	sf::RectangleShape ship;
	sf::Vector2f Size;
	sf::Vector2f InitialPostion;
	sf::Vector2f shipVelocity = Vector2f(0.f, 0.f);
	sf::Color color;
	sf::FloatRect shipRect;
	sf::Vector2i prevMousPos = sf::Vector2i(0, 0);
	sf::Texture texture;
	float speed;
	float angle = -90.f;
	float lastAngle = -90.f;
	Vector2f currentShipPos;

	float rotationSpeed = 10;

	Spaceship();
	Vector2f Rotate(Vector2f vec, float angle, bool clockWise);
	void Movement(float deltaTime);
	void WarpShip(RenderWindow* window);
	Vector2f Velocity(float speed);
	Vector2f Direction(float ang);
	void ContinueMovement(float speede, float deltTime);

};

