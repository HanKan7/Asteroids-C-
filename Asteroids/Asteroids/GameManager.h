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
	int numberOfLives = 5;
	int playerScore = 0;
	int gameLevel = 1;

	Font font;
	Text numberOfLivesText;
	Text gameLevelText;
	Text playerScoreText;
	Text ControlsText;

	Text EndScreenScoreText;
	Text GoToMainMenuText;
	Text QuitGameText;

	Text RespawnText;
	Text DeathText;
	Text ResumeText;
	Text QuitText;
	Text PlayerScoreOnMenuText;

	Text PlayGameText;


	SoundBuffer BGMBuffer;
	SoundBuffer shootBuffer;
	SoundBuffer deathBuffer;
	SoundBuffer gameOverBuffer;
	SoundBuffer winLevelBuffer;
	SoundBuffer AstHitBuffer;

	Sound BGM;
	Sound shoot;
	Sound death;
	Sound gameOverSound;
	Sound winLevelSound;
	Sound astHitSound;


	GameManager();

};

