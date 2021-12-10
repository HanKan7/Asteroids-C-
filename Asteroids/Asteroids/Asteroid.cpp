#include "Asteroid.h"
Asteroid::Asteroid(int index, int radius, int scoreIncrement, bool isBigAsteroid) 
{
	this->isBigAsteroid = isBigAsteroid;
	this->radius = radius;
	this->scoreIncrementOnDestroy = scoreIncrement;
	this->parentIndex = index;
	this->childIndex1 = index * 2;
	this->childIndex2 = index * 2 + 1;
	this->isDead = false;
	asteroid.setRadius(radius);
	asteroid.setOrigin(Vector2f(radius, radius));

	const char* texturePath("Asteroid.png");
	if (!texture.loadFromFile(texturePath)) {
		cout << "Failed to load texture\n";
	}
	asteroid.setTexture(&texture);

	if (isBigAsteroid) 
	{
			srand(time(0));
			int value = rand() % positionVector.size();
			isDisabled = false;
			initialPostion = positionVector[(parentIndex + value) % positionVector.size()];
			assignedPosition = initialPostion;
			initialVelocity = velocityVector[(parentIndex + value) % velocityVector.size()];
			asteroidVelocity = initialVelocity;
			asteroid.setPosition(initialPostion);
	}
}

void Asteroid::UpdateMovement(RenderWindow* window, float deltaTime)
{
	if (!isDead && !isDisabled) 
	{
		auto asteroidPos = asteroid.getPosition();
		asteroidPos += asteroidVelocity * deltaTime;
		auto maxX = window->getSize().x - asteroid.getRadius();
		auto maxY = window->getSize().y - asteroid.getRadius();

		if (asteroidPos.y < 0.0)
		{
			asteroidPos.y = maxY;
		}
		if (asteroidPos.x < 0.0)
		{
			asteroidPos.x = maxX;
		}
		if (asteroidPos.x > maxX) {
			asteroidPos.x = 0;
		}
		if (asteroidPos.y > maxY) {
			asteroidPos.y = 0;
		}
		asteroid.setPosition(asteroidPos);
	}

}

void Asteroid::AsteroidToAsteroidCollision(Asteroid* asteroid)
{
	if ((!isDead && !isDisabled) && (!asteroid->isDead && !asteroid->isDisabled)) 
	{
		FloatRect thisClassRect = this->asteroid.getGlobalBounds();
		FloatRect asteroidRect = asteroid->asteroid.getGlobalBounds();
		if (thisClassRect.intersects(asteroidRect)) 
		{
			this->asteroidVelocity.x = -(this->asteroidVelocity.x);
			this->asteroidVelocity.y = (this->asteroidVelocity.y);
			asteroid->asteroidVelocity.x = -(asteroid->asteroidVelocity.x);
			asteroid->asteroidVelocity.y = (asteroid->asteroidVelocity.y);
		}
	}
}



