#include "GameManager.h"

GameManager::GameManager()
{
    const char* fontPath = "American Captain.ttf";
    if (!font.loadFromFile(fontPath)) {
        cout << "Failed to load font\n";
    }
    numberOfLivesText.setFont(font);
    numberOfLivesText.setFillColor(sf::Color::White);
    numberOfLivesText.setPosition(570.f, 20.f);
    numberOfLivesText.setString("Number Of Lives = " + to_string(numberOfLives));

    ControlsText.setFont(font);
    ControlsText.setFillColor(sf::Color::White);
    ControlsText.setPosition(200.f, 20.f);
    ControlsText.setString("                           PRESS UP TO THRUST\nPRESS LEFT AND RIGHT TO ROTATE THE SHIP\n                           PRESS SPACE TO SHOOT\nEACH LEVEL YOU SURPASS GIVES YOU ONE LIFE");

    playerScoreText.setFont(font);
    playerScoreText.setFillColor(sf::Color::White);
    playerScoreText.setPosition(70.f, 20.f);
    playerScoreText.setString("SCORE = " + to_string(playerScore));

    gameLevelText.setFont(font);
    gameLevelText.setFillColor(sf::Color::White);
    gameLevelText.setPosition(350.f, 20.f);
    gameLevelText.setString("LEVEL " + to_string(gameLevel));

    EndScreenScoreText.setFont(font);
    EndScreenScoreText.setFillColor(sf::Color::White);
    EndScreenScoreText.setPosition(275.f, 220.f);

    GoToMainMenuText.setFont(font);
    GoToMainMenuText.setFillColor(sf::Color::White);
    GoToMainMenuText.setPosition(275.f, 280.f);
    GoToMainMenuText.setString("PRESS M TO GO TO MAIN MENU");

    PlayGameText.setFont(font);
    PlayGameText.setFillColor(sf::Color::White);
    PlayGameText.setPosition(285.f, 320.f);
    PlayGameText.setString("PRESS P TO PLAY THE GAME");

    ResumeText.setFont(font);
    ResumeText.setFillColor(sf::Color::White);
    ResumeText.setPosition(285.f, 320.f);
    ResumeText.setString("PRESS R TO RESUME THE GAME");

    QuitGameText.setFont(font);
    QuitGameText.setFillColor(sf::Color::White);
    QuitGameText.setPosition(285.f, 360.f);
    QuitGameText.setString("PRESS Q TO QUIT THE GAME");

    RespawnText.setFont(font);
    RespawnText.setFillColor(sf::Color::White);
    RespawnText.setPosition(200.f, 520.f);
    RespawnText.setString("YOU HAVE LOST A LIFE, GO SOMEWHERE SAFE");

    DeathText.setFont(font);
    DeathText.setFillColor(sf::Color::White);
    DeathText.setPosition(350.f, 520.f);
    DeathText.setString("YOU DIED");



    const char* bufferPath = "BGM.wav";
    if (!BGMBuffer.loadFromFile(bufferPath)) {
        cout << "Failed to load buffer\n";
    }
    const char* a = "Shoot.wav";
    if (!shootBuffer.loadFromFile(a)) {
        cout << "Failed to load buffer a\n";
    }
    const char* b = "Death.wav";
    if (!deathBuffer.loadFromFile(b)) {
        cout << "Failed to load buffer b\n";
    }
    const char* c = "GameOverAudio.wav";
    if (!gameOverBuffer.loadFromFile(c)) {
        cout << "Failed to load buffer c\n";
    }
    const char* d = "WinLevel.wav";
    if (!winLevelBuffer.loadFromFile(d)) {
        cout << "Failed to load buffer d\n";
    }
    const char* e = "AstHit.wav";
    if (!AstHitBuffer.loadFromFile(e)) {
        cout << "Failed to load buffer e\n";
    }


    BGM.setBuffer(BGMBuffer);
    shoot.setBuffer(shootBuffer);
    death.setBuffer(deathBuffer);
    gameOverSound.setBuffer(gameOverBuffer);
    winLevelSound.setBuffer(winLevelBuffer);
    astHitSound.setBuffer(AstHitBuffer);

}
