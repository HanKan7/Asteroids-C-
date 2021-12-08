#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<iostream>
#include "Spaceship.h"
#include"Bullet.h"
#include"Math.h"

using namespace std;
using namespace sf;

float Magnitude(Vector2f vector)
{

    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2f Normal(Vector2f vector)
{
    return Vector2f(vector.x / Magnitude(vector), vector.y / Magnitude(vector));
}

int main()
{
    RenderWindow window(VideoMode(800, 600), "ASTEROIDS!");
    window.setVerticalSyncEnabled(true);
    Clock clock;
    Clock bulletClock;

    Spaceship ship;
    vector<Bullet> bullets;
    int bulletCount = 5;
    int bulletIndex = 0;
    float clockValue;
    bool bulletSpawned = false;

    for (int i = 0; i < bulletCount; i++) 
    {
        Bullet newBullet;
        newBullet.SpawnBullet(ship.ship.getPosition());
        bullets.push_back(newBullet);
    }


    while (window.isOpen())
    {
#pragma region ClockEvent
        float delta_s = clock.getElapsedTime().asSeconds();
        clock.restart();
#pragma endregion

#pragma region WindowEvents
        sf::Event evt;
        while (window.pollEvent(evt)) {
            switch (evt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:

                //cout << "New Window width:" << evt.size.width << " New Window Height: " << evt.size.height << endl;
                break;

            default:
                break;
            }
        }
#pragma endregion

#pragma region KeyBoardInput
        /*paddle.Movement(&paddle.paddle, 10.5f);
        paddle.MovementWithMouse(&paddle.paddle, 10.5f, &window);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
            mainBall.hasLaunchedTheBall = true;
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            mainBall.hasLaunchedTheBall = true;
        }*/

        ship.Movement(delta_s);
        ship.WarpShip(&window);
        for (int i = 0; i < bulletCount; i++) {
            bullets[i].StickToShip(ship.ship.getPosition());
            bullets[i].WarpBullet(&window);
        }
        

        if (Keyboard::isKeyPressed(Keyboard::Key::Space)) 
        {
            if (!bulletSpawned) 
            {
                clockValue = bulletClock.getElapsedTime().asSeconds();
                bullets[bulletIndex].direction = ship.Direction(ship.angle);
                bulletSpawned = true;               
            }
            
            if (clockValue + 0.35f >= bulletClock.getElapsedTime().asSeconds()) 
            {
                //cout << "Clock value " << clockValue + bullets[bulletIndex].bulletLifeTime << "   bulletClock = " << bulletClock.getElapsedTime().asSeconds()<<endl;
                bullets[bulletIndex].BulletMovement(ship.ship.getPosition(), bullets[bulletIndex].direction, delta_s, 800, 600);
            }

            else 
            {
                bullets[bulletIndex].bulletSpawned = false;
                bulletIndex = (bulletIndex + 1) % bulletCount;
                bulletSpawned = false;
            }
        }
        if (!Keyboard::isKeyPressed(Keyboard::Key::Space))
        {
            bullets[bulletIndex].BulletMovement(ship.ship.getPosition(), bullets[bulletIndex].direction, delta_s, 800, 600);
        }
#pragma endregion

#pragma region UpdateBallsPosition
        /*if (mainBall.hasLaunchedTheBall)
        {
            mainBall.UpdateBallPosition(&window, delta_s);
        }
        else
        {
            mainBall.CollisionWithPaddle(&paddle.paddle, mainBall.hasLaunchedTheBall);
        }*/

#pragma endregion

#pragma region Collision Check
        /*mainBall.CollisionWithPaddle(&paddle.paddle, mainBall.hasLaunchedTheBall);

        for (int i = 0; i < bricks.size(); i++)
        {
            mainBall.CollisionWithBrick(&bricks[i]);
        }*/
#pragma endregion   
 
#pragma region GameHasEnded
        //bool didGameRestart = false;
        //if (mainBall.numberOfLives <= 0)
        //{
        //    GameOverText.setString("GAME OVER\nYOUR SCORE IS " + to_string(mainBall.playerScore) + "\n Press R to restart the game\n Q to quit the game");
        //    bool playerHasEnteredTheInput = false;
        //    while (!playerHasEnteredTheInput)
        //    {
        //        window.clear();
        //        window.draw(GameOverText);
        //        window.display();

        //        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
        //        {
        //            didGameRestart = true;
        //            playerHasEnteredTheInput = true;
        //            mainBall.numberOfLives = 3;
        //            mainBall.numberOfLivesText.setString("Number Of Lives = " + to_string(mainBall.numberOfLives));
        //            mainBall.playerScore = 0;
        //            mainBall.playerScoreText.setString("SCORE = " + to_string(mainBall.playerScore));
        //            gameLevel = 1;
        //        }
        //        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
        //        {
        //            return 1;
        //        }
        //    }
        //}

#pragma endregion

#pragma region AreAllBrickDestroyed

        //for (int i = 0; i < brickCount; i++)
        //{
        //    if (!bricks[i].isDead)   break;
        //    if (i == brickCount - 1 && bricks[i].isDead)
        //    {
        //        areAllBrickDestroyed = true;
        //    }
        //}

        //if (areAllBrickDestroyed)
        //{
        //    mainBall.ResetBallWithMoreSpeed(didGameRestart);
        //    didGameRestart = false;
        //    /*for (int i = 0; i < bricks.size(); i++) {
        //        bricks[i].isDead = false;
        //    }*/
        //    gameLevel = (gameLevel + 1) % 2;
        //    bricks.clear();

        //    if (gameLevel == 0)
        //    {
        //        vector<sf::Vector2f> BrickPosition;
        //        sf::Vector2f brickStartPos = sf::Vector2f(620.f, 75.f);
        //        brickCount = 2;
        //        areAllBrickDestroyed = false;

        //        for (float i = 0; i < brickCount; i++)
        //        {
        //            BrickPosition.push_back(brickStartPos);
        //            cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
        //            brickStartPos.x -= 45;
        //            brickStartPos.y += 45;
        //        }



        //        for (float i = 0; i < BrickPosition.size(); i++)
        //        {
        //            Brick brick(1, BrickPosition[i]);
        //            bricks.push_back(brick);
        //        }
        //    }

        //    if (gameLevel == 1)
        //    {

        //        vector<sf::Vector2f> BrickPosition;
        //        sf::Vector2f brickStartPos = sf::Vector2f(37.5f, 75.f);
        //        brickCount = 7;
        //        areAllBrickDestroyed = false;

        //        for (float i = 0; i < brickCount; i++)
        //        {
        //            BrickPosition.push_back(brickStartPos);
        //            cout << " X = " << brickStartPos.x << "    Y = " << brickStartPos.y << endl;
        //            brickStartPos.x += 105;
        //        }



        //        for (float i = 0; i < BrickPosition.size(); i++)
        //        {
        //            Brick brick(1, BrickPosition[i]);
        //            bricks.push_back(brick);
        //        }
        //    }


        //    areAllBrickDestroyed = false;
        //}

#pragma endregion


#pragma region WindowReset
        window.clear();
       /* window.draw(paddle.paddle);
        window.draw(mainBall.ball);
        for (int i = 0; i < bricks.size(); i++)
        {
            if (!bricks[i].isDead)
            {
                bricks[i].brick.setTexture(&bricks[i].texture);
                window.draw(bricks[i].brick);
            }

        }
        window.draw(mainBall.numberOfLivesText);
        window.draw(mainBall.playerScoreText);

        window.draw(mainBall.ballSprite);*/
        for (int i = 0; i < bulletCount; i++) {
            window.draw(bullets[i].bullet);
        }
        window.draw(ship.ship);
        window.display();
#pragma endregion
    }
}
