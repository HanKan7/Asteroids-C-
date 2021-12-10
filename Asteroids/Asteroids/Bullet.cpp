#include "Bullet.h"

void Bullet::SpawnBullet(Vector2f shipPosition)
{
		radius = 5;
		bullet.setRadius(radius);
		bullet.setPosition(shipPosition.x - bullet.getRadius(), shipPosition.y - bullet.getRadius());
	    bullet.setFillColor(Color::White);
		shoulGoBackToInitialPosition = true;
}

void Bullet::StickToShip(Vector2f shipPosition) 
{
	if(!bulletSpawned) bullet.setPosition(shipPosition.x - bullet.getRadius(), shipPosition.y - bullet.getRadius());
}

void Bullet::BulletMovement(Vector2f shipPosition, Vector2f directionToFace, float deltaTime, float winX, float winY)
{
		bulletSpawned = true;
		Vector2f currentPos = bullet.getPosition();
		direction = directionToFace;
		currentPos += direction * bulletSpeed * deltaTime;
		bullet.setPosition(currentPos);	
}

void Bullet::WarpBullet(RenderWindow* window) 
{
	auto bulletPos = bullet.getPosition();
	auto maxX = window->getSize().x - bullet.getRadius() * 2.0f;
	auto maxY = window->getSize().y - bullet.getRadius() * 2.0f;
	if (bulletPos.y < 0.0)
	{
		bulletPos.y = maxY;
	}
	if (bulletPos.x < 0.0)
	{
		bulletPos.x = maxX;
	}
	if (bulletPos.x > maxX) {
		bulletPos.x = 0;
	}
	if (bulletPos.y > maxY) {
		bulletPos.y = 0;
	}
	bullet.setPosition(bulletPos);
}

void Bullet::CollisionWithAsteroid(Asteroid* asteroid, GameManager* gameManager)
{
	if (asteroid->isDead || asteroid->isDisabled)	return;
	FloatRect ballRect = bullet.getGlobalBounds();
	FloatRect asteroidRect = asteroid->asteroid.getGlobalBounds();

	if (ballRect.intersects(asteroidRect) && bulletSpawned)
	{
		gameManager->astHitSound.play();
		asteroid->isDead = true;
		asteroid->initialPostion = asteroid->asteroid.getPosition();
		gameManager->playerScore += asteroid->scoreIncrementOnDestroy;
		gameManager->playerScoreText.setString("SCORE = " + to_string(gameManager->playerScore));

	}
}
