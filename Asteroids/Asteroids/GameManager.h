#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include<iostream>
using namespace std;
using namespace sf;
class GameManager
{
public:
	int numberOfLives = 30;
	int playerScore = 0;
	int gameLevel = 1;

	Font font;
	Text numberOfLivesText;
	Text gameLevelText;
	Text playerScoreText;

	Text EndScreenScoreText;
	Text GoToMainMenuText;
	Text QuitGameText;

	Text RespawnText;
	Text DeathText;
	Text ResumeText;
	Text QuitText;
	Text PlayerScoreOnMenuText;

	Text PlayGameText;

	GameManager();

};

