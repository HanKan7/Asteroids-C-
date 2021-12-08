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

using namespace std;
using namespace sf;
class Math
{
	float Magnitude(Vector2f vector);
	float Dot(Vector2f vector1, Vector2f vector2);
	float Angle(Vector2f vec1, Vector2f vec2);
	Vector2f Rotate(Vector2f vec, float angle, bool clockWise);
	Vector2f Normal(Vector2f vector);
	float Cross(Vector2f vec1, Vector2f vec2);
};

