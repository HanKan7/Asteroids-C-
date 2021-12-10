#include "Spaceship.h"


Spaceship::Spaceship() 
{
    this->InitialPostion = sf::Vector2f(385.0f, 300.0f);
    this->Size = sf::Vector2f(50.0f, 50.0f);
    this->color = sf::Color::White;
    ship.setFillColor(color);
    ship.setOrigin(Vector2f(25.f, 25.f));
    ship.setPosition(InitialPostion);
    ship.setSize(Size);
    shipRect = ship.getGlobalBounds();
    const char* texturePath("Spaceship.png");
    if (!texture.loadFromFile(texturePath)) {
        cout << "Failed to load texture\n";
    }
    ship.setTexture(&texture);
}

Vector2f Spaceship::Rotate(Vector2f vec, float angle, bool clockWise)
{
    if (clockWise)	angle = 2 * 3.14 - angle;
    float xVal = vec.x * cos(angle) - vec.y * sin(angle);
    float yVal = vec.x * sin(angle) + vec.y * cos(angle);
    return Vector2f(xVal, yVal);
}

void Spaceship::Movement(float deltaTime)
{
    if (!isDead) 
    {
        Vector2f position = ship.getPosition();
        position += shipVelocity * deltaTime;
        if (Keyboard::isKeyPressed(Keyboard::Key::Up))
        {
            speed = 200.f;
            ContinueMovement(speed, deltaTime);
            lastAngle = angle;
        }

        else if (!Keyboard::isKeyPressed(Keyboard::Up))
        {
            float dampSpeed = 200.f;
            if (speed > 0)
            {
                speed -= dampSpeed * deltaTime;
                ContinueMovement(speed, deltaTime);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::Left))
        {
            float val = -400.0f * deltaTime;
            angle += val;

            if (abs(angle) > 360)
            {
                if (angle > 0)
                {
                    angle = abs(angle) - 360;
                }
                else
                {
                    angle = -(abs(angle) - 360);
                }
            }
            ship.rotate(val);
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Right))
        {
            float val = 400.0f * deltaTime;
            angle += val;

            if (abs(angle) > 360)
            {
                if (angle > 0)
                {
                    angle = abs(angle) - 360;
                }
                else
                {
                    angle = -(abs(angle) - 360);
                }
            }
            ship.rotate(val);
        }
    }
    
}

void Spaceship::WarpShip(RenderWindow* window)
{
    auto shipPos = ship.getPosition();
    auto maxX = window->getSize().x - ship.getSize().x;
    auto maxY = window->getSize().y - ship.getSize().y;
    if (shipPos.y < 0.0) 
    {
        shipPos.y = maxY;
    }
    if (shipPos.x < 0.0) 
    {
        shipPos.x = maxX;
    }
    if (shipPos.x > maxX) {
        shipPos.x = 0;
    }
    if (shipPos.y > maxY) {
        shipPos.y = 0;
    }
    ship.setPosition(shipPos);
}

void Spaceship::DisableMesh(int shipClock)
{
    if (justDied)
    {
        shipClock = respawnClock.getElapsedTime().asSeconds();   
        cout << "ShipClock " << shipClock << "RT " << respawnClock.getElapsedTime().asSeconds()<<endl;
        if (shipClock + 1 <= respawnClock.getElapsedTime().asSeconds())
        {
            cout << "Collision1\n";
            disableMesh = false;
        }
        if (shipClock + 2 <= respawnClock.getElapsedTime().asSeconds())
        {
            cout << "Collision2\n";
            disableMesh = true;
        }
        if (shipClock + 2 <= respawnClock.getElapsedTime().asSeconds())
        {
            cout << "Collision3\n";
           disableMesh = false;
           justDied = false;
        }
    }
}

Vector2f Spaceship::Direction(float angle)
{
    Vector2f direction = Vector2f(cos(angle * 3.1416 / 180), sin(angle * 3.1416 / 180));
    return Vector2f(direction);
}

Vector2f Spaceship::Velocity(float speed)
{
    Vector2f velocity;
    if (Keyboard::isKeyPressed(Keyboard::Key::Up))
    {
         velocity = Vector2f(speed * Direction(angle).x, speed * Direction(angle).y);
    }
    else 
    {
         velocity = Vector2f(speed * Direction(lastAngle).x, speed * Direction(lastAngle).y);
    }
    return Vector2f(velocity);
}

void Spaceship::ContinueMovement(float speed, float deltaTime)
{
    if (!isDead) 
    {
        currentShipPos = ship.getPosition();
        currentShipPos += Velocity(speed) * deltaTime;
        ship.setPosition(currentShipPos);
    }
    
}

void Spaceship::CollisionWithAsteroid(Asteroid* asteroid, GameManager* gameManager)
{
    if (asteroid->isDead)	return;
    FloatRect shipRect = ship.getGlobalBounds();
    FloatRect asteroidRect = asteroid->asteroid.getGlobalBounds();

    if ((shipRect.intersects(asteroidRect) && (!asteroid->isDead && !asteroid->isDisabled)) && !justDied)
    {
        hitTime = respawnClock.getElapsedTime().asSeconds();
        justDied = true;
        gameManager->numberOfLives--;
        if (gameManager->numberOfLives <= 0) 
        {
            gameManager->numberOfLives = 0;
            isDead = true;
            gameManager->DeathText.setString("You DIED!");
            gameManager->EndScreenScoreText.setString("YOUR FINAL SCORE = " + to_string(gameManager->playerScore));
        }  
        gameManager->numberOfLivesText.setString("Number Of Lives = " + to_string(gameManager->numberOfLives));
    }
}