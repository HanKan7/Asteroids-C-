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
#include"MediumAsteroid.h"
#include"GameManager.h"
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


    Texture texture;
    const char* texturePath("Space.jpg");
    if (!texture.loadFromFile(texturePath)) {
        cout << "Failed to load texture\n";
    }
    Sprite spaceSprite;
    spaceSprite.setTexture(texture);

    int gameLevel = 1;
    bool didGameRestart = false;
    bool isInMainMenu;
    bool isInGame = false;
    bool isInGameOverScreen;
    bool areAllAsteroidDestroyed = false;
    bool bigAsteroidsAreDestroyed = false;
    bool mediumAsteroidsAreDestroyed = false;
    bool smallAsteroidsAreDestroyed = false;


    Clock clock;
    Clock bulletClock;

    Spaceship ship;
    GameManager gameManager;


#pragma region  MainMenu



#pragma endregion

    vector<Bullet> bullets;
    vector<Asteroid> bigAsteroids;
    vector<Asteroid> medAsteroids;
    vector<Asteroid> smallAsteroids;

    int bulletCount = 3;
    int bulletIndex = 0;
    float clockValue = 0.f;
    float clockReleaseValue = 0;
    float shipClock = 0;

    bool bulletSpawned = false;
    bool spacePressed = false;

    int asteroidCount = 7;
    int mediumAsteroidCount = asteroidCount * 2;
    int smallAsteroidCount = mediumAsteroidCount * 2;

    for (int i = 0; i < bulletCount; i++) 
    {
        Bullet newBullet;
        newBullet.SpawnBullet(ship.ship.getPosition());
        bullets.push_back(newBullet);
    }

    for (int i = 0; i < asteroidCount; i++)
    {
        Asteroid newAsteroid(i, 50, 5, true);
        bigAsteroids.push_back(newAsteroid);
    }

    for (int i = 0; i < mediumAsteroidCount; i++) 
    {
        Asteroid newMed(i, 25, 10,false);
        newMed.initialPostion = bigAsteroids[i / 2].initialPostion;
        if (i % 2 == 0)	newMed.initialVelocity = -(bigAsteroids[i / 2].initialVelocity + Vector2f(40.f, 40.f));
        else newMed.initialVelocity = bigAsteroids[i / 2].initialVelocity + Vector2f(40.f, 40.f);
        newMed.asteroidVelocity = newMed.initialVelocity;
        newMed.isDisabled = true;
        //newMed.InitMediumAsteroid(i, 15, bigAsteroids[i / 2].initialVelocity, bigAsteroids[i / 2].initialVelocity);
        medAsteroids.push_back(newMed);
    }
    for (int i = 0; i < smallAsteroidCount; i++)
    {
        Asteroid smallMed(i, 15, 15,false);
        smallMed.initialPostion = medAsteroids[i / 2].initialPostion;
        if (i % 2 == 0)	smallMed.initialVelocity = -(medAsteroids[i / 2].initialVelocity + Vector2f(20.f, 20.f));
        else smallMed.initialVelocity = medAsteroids[i / 2].initialVelocity + Vector2f(20.f, 20.f);
        smallMed.asteroidVelocity = smallMed.initialVelocity;
        smallMed.isDisabled = true;
        //newMed.InitMediumAsteroid(i, 15, bigAsteroids[i / 2].initialVelocity, bigAsteroids[i / 2].initialVelocity);
        smallAsteroids.push_back(smallMed);
        
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

#pragma region MainMenu
        if (!isInGame) 
        {
            cout << "Back to main menu";
            bool playerHasEnteredTheInput = false;
            while (!playerHasEnteredTheInput)
            {

                window.clear();
                window.draw(spaceSprite);
                window.draw(gameManager.PlayGameText);
                window.draw(gameManager.QuitGameText);
#pragma region drawAsteroids
                for (int i = 0; i < asteroidCount; i++)
                {
                    if (!bigAsteroids[i].isDead)
                    {
                        bigAsteroids[i].asteroid.setTexture(&bigAsteroids[i].texture);
                        window.draw(bigAsteroids[i].asteroid);
                    }

                }

                for (int i = 0; i < mediumAsteroidCount; i++)
                {
                    if (!medAsteroids[i].isDead)
                    {
                        medAsteroids[i].asteroid.setTexture(&medAsteroids[i].texture);
                        window.draw(medAsteroids[i].asteroid);
                    }

                }

                for (int i = 0; i < smallAsteroidCount; i++)
                {
                    if (!smallAsteroids[i].isDead)
                    {
                        smallAsteroids[i].asteroid.setTexture(&smallAsteroids[i].texture);
                        window.draw(smallAsteroids[i].asteroid);
                    }

                }
#pragma endregion
                window.display();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
                {
                    isInGame = true;
                    playerHasEnteredTheInput = true;
                    gameManager.numberOfLives = 3;
                    gameManager.numberOfLivesText.setString("Number Of Lives = " + to_string(gameManager.numberOfLives));
                    gameManager.playerScore = 0;
                    gameManager.playerScoreText.setString("SCORE = " + to_string(gameManager.playerScore));


                    gameLevel = 1;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                {
                    return 1;
                }
            }
        }
#pragma endregion


#pragma region KeyBoardInput

        ship.Movement(delta_s);
        ship.WarpShip(&window);
        for (int i = 0; i < bulletCount; i++) {
            bullets[i].StickToShip(ship.ship.getPosition());
            //bullets[i].WarpBullet(&window);
        }
        for (int i = 0; i < asteroidCount; i++) {
            bigAsteroids[i].UpdateMovement(&window, delta_s);
        }
        for (int i = 0; i < bigAsteroids.size(); i++)
        {
            if (bigAsteroids[i].isDead && !bigAsteroids[i].valuesHaveBeenPassed) 
            {
                bigAsteroids[i].valuesHaveBeenPassed = true;
                //cout << "X =" << medAsteroids[bigAsteroids[i].childIndex1].asteroidVelocity.x << " Y " << medAsteroids[bigAsteroids[i].childIndex2].asteroidVelocity.y << endl;
                medAsteroids[bigAsteroids[i].childIndex1].isDisabled = false;
                medAsteroids[bigAsteroids[i].childIndex2].isDisabled = false;
                medAsteroids[bigAsteroids[i].childIndex1].asteroid.setPosition(bigAsteroids[i].asteroid.getPosition() + Vector2f(30.f, 30.f));
                medAsteroids[bigAsteroids[i].childIndex2].asteroid.setPosition(bigAsteroids[i].asteroid.getPosition()  - Vector2f(30.f, 30.f));
            }
            //cout << "X ="<<medAsteroids[bigAsteroids[i].childIndex1].asteroidVelocity.x << " Y " << medAsteroids[bigAsteroids[i].childIndex2].asteroidVelocity.y << endl;
            medAsteroids[bigAsteroids[i].childIndex1].UpdateMovement(&window, delta_s);
            medAsteroids[bigAsteroids[i].childIndex2].UpdateMovement(&window, delta_s);
        }
        for (int j = 0; j < mediumAsteroidCount; j++) 
            {
                if ( (!medAsteroids[j].isDisabled && !medAsteroids[j].valuesHaveBeenPassed))
                {
                    medAsteroids[j].valuesHaveBeenPassed = true;
                    smallAsteroids[medAsteroids[j].childIndex1].isDisabled = false;
                    smallAsteroids[medAsteroids[j].childIndex2].isDisabled = false;
                    smallAsteroids[medAsteroids[j].childIndex1].asteroid.setPosition(medAsteroids[j].asteroid.getPosition() + Vector2f(30.f, 30.f) );
                    smallAsteroids[medAsteroids[j].childIndex2].asteroid.setPosition(medAsteroids[j].asteroid.getPosition() - Vector2f(30.f, 30.f) );
                }
                smallAsteroids[medAsteroids[j].childIndex1].UpdateMovement(&window, delta_s);
                smallAsteroids[medAsteroids[j].childIndex2].UpdateMovement(&window, delta_s);
            }
            
        
        //Shooting
        if (!ship.isDead) 
            {
                if (Keyboard::isKeyPressed(Keyboard::Key::Space))
                {
                    if (!bullets[bulletIndex].bulletSpawned)
                    {
                        clockValue = bullets[bulletIndex].bulletClock.getElapsedTime().asSeconds(); //20
                        clockReleaseValue = bulletClock.getElapsedTime().asSeconds();
                        bullets[bulletIndex].direction = ship.Direction(ship.angle);
                        bullets[bulletIndex].bulletSpawned = true;
                        spacePressed = true;

                    }

                    if (clockValue + 0.35f >= bullets[bulletIndex].bulletClock.getElapsedTime().asSeconds())
                    {
                        bullets[bulletIndex].BulletMovement(ship.ship.getPosition(), bullets[bulletIndex].direction, delta_s, 800, 600);
                    }

                    else
                    {
                        bullets[bulletIndex].bulletSpawned = false;
                        bulletIndex = (bulletIndex + 1) % bulletCount;
                        bullets[bulletIndex].bulletSpawned = false;
                        spacePressed = false;
                    }
                }

                if (!Keyboard::isKeyPressed(Keyboard::Key::Space))
                {
                    if (clockReleaseValue + 1.f >= bulletClock.getElapsedTime().asSeconds())
                        bullets[bulletIndex].BulletMovement(ship.ship.getPosition(), bullets[bulletIndex].direction, delta_s, 800, 600);
                    else
                    {
                        bullets[bulletIndex].bulletSpawned = false;
                    }
                }
            }

#pragma region Going Back to The Main Menu
        bool playerHasEnteredTheInput = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            while (!playerHasEnteredTheInput) 
            {
                window.clear();
                window.draw(spaceSprite);
                window.draw(gameManager.ResumeText);
                window.draw(gameManager.GoToMainMenuText);
                window.draw(gameManager.QuitGameText);
                window.display();


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) 
                {
                    break;
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) 
                {
                    return 1;
                }

                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) 
                {
                    for (int i = 0; i < bigAsteroids.size(); i++) 
                    {
                        bigAsteroids[i].isDead = false;
                        bigAsteroids[i].isDisabled = false;
                        bigAsteroids[i].valuesHaveBeenPassed = false;
                    }
                    for (int i = 0; i < medAsteroids.size(); i++)
                    {
                        medAsteroids[i].isDead = false;
                        medAsteroids[i].isDisabled = true;
                        medAsteroids[i].valuesHaveBeenPassed = false;
                    }
                    for (int i = 0; i < smallAsteroids.size(); i++)
                    {
                        smallAsteroids[i].isDead = false;
                        smallAsteroids[i].isDisabled = true;
                    }
                    gameManager.numberOfLives = 3;
                    gameManager.playerScore = 0;
                    isInGame = false;
                    window.clear();
                    break;
                }
            }
            continue;
            gameLevel = 1;
        }
#pragma endregion



#pragma endregion


#pragma region Collision Check
        //Bullet collision
        for (int i = 0; i < bullets.size(); i++)
        {
            for (int j = 0; j < bigAsteroids.size(); j++) 
            {
                bullets[i].CollisionWithAsteroid(&bigAsteroids[j], &gameManager);
            }
            for (int j = 0; j < medAsteroids.size(); j++)
            {
                bullets[i].CollisionWithAsteroid(&medAsteroids[j], &gameManager);
            }
            for (int j = 0; j < smallAsteroids.size(); j++)
            {
                bullets[i].CollisionWithAsteroid(&smallAsteroids[j], &gameManager);
            }
            
        }

        //Asteroid to asteroid
        /*for (int i = 0; i < asteroidCount; i++) 
        {
            for (int j = i + 1; j < asteroidCount; j++) 
            {
                bigAsteroids[i].AsteroidToAsteroidCollision(&bigAsteroids[j]);
            }
        }*/
        for (int i = 0; i < mediumAsteroidCount; i++)
        {
            for (int j = i + 1; j < mediumAsteroidCount; j++)
            {
                medAsteroids[i].AsteroidToAsteroidCollision(&medAsteroids[j]);
            }
        }
        for (int i = 0; i < smallAsteroidCount; i++)
        {
            for (int j = i + 1; j < smallAsteroidCount; j++)
            {
                smallAsteroids[i].AsteroidToAsteroidCollision(&smallAsteroids[j]);
            }
        }

        //Asteroid Collision
        bool didCollisionHappen = false;
        for (int i = 0; i < bigAsteroids.size(); i++) 
        {
            ship.CollisionWithAsteroid(&bigAsteroids[i], &gameManager);
            /*if (ship.justDied) 
            {
                shipClock = ship.respawnClock.getElapsedTime().asSeconds();
                if (shipClock + 1 <= ship.respawnClock.getElapsedTime().asSeconds()) 
                {
                    ship.disableMesh = false;
                }
                if (shipClock + 2 <= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = true;
                }
                if (shipClock + 2 <= ship.respawnClock.getElapsedTime().asSeconds()) 
                {
                    ship.disableMesh = false;
                    ship.justDied = false;
                }
            }*/
        }
        for (int i = 0; i < medAsteroids.size(); i++)
        {
            ship.CollisionWithAsteroid(&medAsteroids[i], &gameManager);
        }
        for (int i = 0; i < smallAsteroids.size(); i++)
        {
            ship.CollisionWithAsteroid(&smallAsteroids[i], &gameManager);
        }

        //ship.DisableMesh(bulletClock.getElapsedTime().asSeconds());
        //Disable Mesh
        if (ship.justDied)
            {
            shipClock = ship.hitTime;
                if (shipClock + 0.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = false;
                    //cout << "First\n";
                }
                else if (shipClock + 1.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = true;
                    //cout << "First2\n";
                }
                else if (shipClock + 2.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = false;
                    //cout << "First3\n";
                }
                else if (shipClock + 3.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = true;
                    //cout << "First3\n";
                }
                else if (shipClock + 4.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = false;
                    //cout << "First3\n";
                }
                else if (shipClock + 5.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = true;
                    //cout << "First3\n";
                }
                else if (shipClock + 6.35f >= ship.respawnClock.getElapsedTime().asSeconds())
                {
                    ship.disableMesh = false;
                    ship.justDied = false;
                    //cout << "First3\n";
                }
            }
#pragma endregion   
 
#pragma region GameHasEnded

        if (gameManager.numberOfLives <= 0) 
        {
            isInGameOverScreen = true;
            bool playerHasEnteredTheInput = false;
                    while (!playerHasEnteredTheInput)
                    {
                        window.clear();
                        window.draw(spaceSprite);
                        window.draw(gameManager.DeathText);
                        window.draw(gameManager.EndScreenScoreText);
                        window.draw(gameManager.GoToMainMenuText);
                        window.draw(gameManager.QuitGameText);
                        window.display();

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M))
                        {
                            didGameRestart = true;
                            playerHasEnteredTheInput = true;
                            gameManager.numberOfLives = 3;
                            gameManager.numberOfLivesText.setString("Number Of Lives = " + to_string(gameManager.numberOfLives));
                            gameManager.playerScore = 0;
                            gameManager.playerScoreText.setString("SCORE = " + to_string(gameManager.playerScore));

                            
                            gameLevel = 1;

                            for (int i = 0; i < bigAsteroids.size(); i++)
                            {
                                bigAsteroids[i].isDead = false;
                                bigAsteroids[i].isDisabled = false;
                                bigAsteroids[i].valuesHaveBeenPassed = false;
                            }
                            for (int i = 0; i < medAsteroids.size(); i++)
                            {
                                medAsteroids[i].isDead = false;
                                medAsteroids[i].isDisabled = true;
                                medAsteroids[i].valuesHaveBeenPassed = false;
                            }
                            for (int i = 0; i < smallAsteroids.size(); i++)
                            {
                                smallAsteroids[i].isDead = false;
                                smallAsteroids[i].isDisabled = true;
                            }
                            gameManager.numberOfLives = 3;
                            gameManager.playerScore = 0;
                            isInGame = false;
                            ship.isDead = false;
                            ship.justDied = false;
                            window.clear();
                            break;
                        }
                        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
                        {
                            return 1;
                        }
                    }
        }


#pragma endregion

#pragma region AreAllAsteroidsDestroyed
        for (int i = 0; i < smallAsteroids.size(); i++)
        {
            if (!smallAsteroids[i].isDead)
            {
                areAllAsteroidDestroyed = false;
                break;
            }
            areAllAsteroidDestroyed = true;
        }
        
        if (areAllAsteroidDestroyed) 
        {
            gameLevel++;
            gameManager.numberOfLives++;
            gameManager.numberOfLivesText.setString("Number Of Lives = " + to_string(gameManager.numberOfLives));
            gameManager.gameLevel++;
            gameManager.gameLevelText.setString("LEVEL " + to_string(gameLevel));


            for (int i = 0; i < bigAsteroids.size(); i++)
            {
                bigAsteroids[i].isDead = false;
                bigAsteroids[i].isDisabled = false;
                bigAsteroids[i].asteroidVelocity *= 1.5f;
                bigAsteroids[i].valuesHaveBeenPassed = false;
            }
            for (int i = 0; i < medAsteroids.size(); i++)
            {
                medAsteroids[i].isDead = false;
                medAsteroids[i].isDisabled = true;
                medAsteroids[i].asteroidVelocity *= 1.1f;
                medAsteroids[i].valuesHaveBeenPassed = false;
            }
            for (int i = 0; i < smallAsteroids.size(); i++)
            {
                smallAsteroids[i].isDead = false;
                smallAsteroids[i].asteroidVelocity *= 1.05f;
                smallAsteroids[i].isDisabled = true;
            }


        }     

#pragma endregion


#pragma region WindowReset
        window.clear();
        window.draw(spaceSprite);

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
        if (!ship.isDead) 
        {
            for (int i = 0; i < bulletCount; i++) {
                window.draw(bullets[i].bullet);
            }
        }
#pragma region drawAsteroids
        for (int i = 0; i < asteroidCount; i++)
        {
            if (!bigAsteroids[i].isDead)
            {
                bigAsteroids[i].asteroid.setTexture(&bigAsteroids[i].texture);
                window.draw(bigAsteroids[i].asteroid);
            }

        }

        for (int i = 0; i < mediumAsteroidCount; i++)
        {
            if (!medAsteroids[i].isDead && !medAsteroids[i].isDisabled)
            {
                medAsteroids[i].asteroid.setTexture(&medAsteroids[i].texture);
                window.draw(medAsteroids[i].asteroid);
            }

        }

        for (int i = 0; i < smallAsteroidCount; i++)
        {
            if (!smallAsteroids[i].isDead &&  !smallAsteroids[i].isDisabled)
            {
                smallAsteroids[i].asteroid.setTexture(&smallAsteroids[i].texture);
                window.draw(smallAsteroids[i].asteroid);
            }

        }
#pragma endregion

        
        if(!ship.isDead && !ship.disableMesh)
        window.draw(ship.ship);
        window.draw(gameManager.numberOfLivesText);
        window.draw(gameManager.gameLevelText);
        if (ship.justDied && gameManager.numberOfLives > 0)   window.draw(gameManager.RespawnText);
        
        window.draw(gameManager.playerScoreText);
        window.display();
#pragma endregion
    }
}
