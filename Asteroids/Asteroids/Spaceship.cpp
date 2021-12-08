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
    Vector2f position = ship.getPosition();
    position += shipVelocity * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Key::Up)) 
    {
        speed = 450.f;
        /*shipVelocity.y -= speed * deltaTime;
        if (shipVelocity.y <= -500.f)    shipVelocity.y = -500.f;*/
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

    ///*else 
    //{
    //    float dampAmount = 250.f;

    //    if (shipVelocity.x >= 0) 
    //    {
    //        shipVelocity.x -= dampAmount * deltaTime;
    //    }
    //    else 
    //    {
    //        shipVelocity.x += dampAmount * deltaTime;
    //    }
    //    if (shipVelocity.y >= 0)
    //    {
    //        shipVelocity.y -= dampAmount * deltaTime;
    //    }
    //    else
    //    {
    //        shipVelocity.y += dampAmount * deltaTime;
    //    }
    //    
    //    if (shipVelocity.x >= -0.1f && shipVelocity.x <= 0.1f)  shipVelocity.x = 0.f;
    //    if (shipVelocity.y >= -0.1f && shipVelocity.y <= 0.1f)  shipVelocity.y = 0.f;
    //}*/
    ////cout << shipVelocity.x << "-----" << shipVelocity.y << endl;
    
    //ship.setPosition(position);
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
    currentShipPos = ship.getPosition();
    currentShipPos += Velocity( speed) * deltaTime;
    ship.setPosition(currentShipPos);
}









//void Bullet::Spawn(sf::Vector2f shipPos, sf::Vector2f direction)
//{
//    bullet.setPosition(shipPos.x - bullet.getRadius(), shipPos.y - bullet.getRadius());
//    bullet.setFillColor(sf::Color::Red);
//    showBullet = true;
//    dir = direction;
//}
//
//void Bullet::Movement(float dTime, sf::Vector2f shipPos, float win_x, float win_y)
//{
//    sf::Vector2f currentPos = bullet.getPosition();
//
//    currentPos += dir * bulletSpeed * dTime;
//}
//
//newBullet.Spawn(shipClass.shipShape.getPosition(), shipClass.Direction(shipClass.angle));