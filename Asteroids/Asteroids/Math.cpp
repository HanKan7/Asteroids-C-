#include "Math.h"

float Math::Magnitude(Vector2f vector)
{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Math::Normal(Vector2f vector)
{
	return Vector2f(vector.x / Magnitude(vector), vector.y / Magnitude(vector));
}

float Math::Cross(Vector2f vec1, Vector2f vec2)
{
	float zVal = vec1.x * vec2.y - vec1.y * vec2.x;
	return zVal;
}

float Math::Dot(Vector2f vector1, Vector2f vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y;
}

float Math::Angle(Vector2f vec1, Vector2f vec2)
{
	float dotDivide = Dot(vec1, vec2)/(Magnitude(vec1) * Magnitude(vec2));
	return acos(dotDivide); //in radians. For degrees * 180/PI
}

Vector2f Math::Rotate(Vector2f vec, float angle, bool clockWise)
{
	if (clockWise)	angle = 2 * 3.14 - angle;
	float xVal = vec.x * cos(angle) - vec.y * sin(angle);
	float yVal= vec.x * sin(angle) + vec.y * cos(angle);
	return Vector2f(xVal, yVal);
}


