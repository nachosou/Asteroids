#include "raylib.h"
#include "iostream"
#include "player.h"
#include "scenes.h"
#include "bullet.h"
#include "menu.h"
#include "asteroids.h"
#include "rules.h"
#include "pause.h"
#include "lose.h"
#include "win.h"

using namespace std;
const int screenWidth = 1024;
const int screenHeight = 768;

Texture2D playUnselectedButton;
Texture2D playSelectedButton;
Texture2D rulesUnselectedButton;
Texture2D rulesSelectedButton;
Texture2D exitUnselectedButton;
Texture2D exitSelectedButton;
Texture2D menuUnselectedButton;
Texture2D menuSelectedButton;
Texture2D resumeUnselectedButton;
Texture2D resumeSelectedButton;
Texture2D creditUnselectedButton;
Texture2D creditSelectedButton;
Texture2D background;
Texture2D playerSpray;
Texture2D harpoon;
Texture2D crosshair;
Texture2D rulesMenu;
Texture2D logo;
Texture2D win;
Texture2D lose;
Texture2D bigEnemy;
Texture2D mediumEnemy;
Texture2D smallEnemy;

Music menuMusic;
Music gameMusic;

Wave creditSound;
Wave deathSound;
Wave dyingFish;
Wave shootingHarpoon;
Wave touchingButtons;

void gamePlay(Player& player, GameScenes& actualScene, float gameTimer);
void drawGamePlay(Player& player, Texture2D background, Texture2D harpoon);
void resetStats(Player& player, float& gameTimer);
void winOrLose(GameScenes& actualScene, Player& player, float gameTimer);

static Asteroids asteroidsArray[maxAsteroids];

void main()
{
    Player player;
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;

    float gameTimer = 0.0f;

    int resetCounter = 0;

    GameScenes actualScene = GameScenes::Menu;
    bool newScene = true;
    GameScenes prevScene = actualScene;

    bool exitProgram = false;
    bool isGamePaused = false;

    InitWindow(screenWidth, screenHeight, "ASTEROIDS");

    background = LoadTexture("assets/background.png");
    playerSpray = LoadTexture("assets/buzo.png");
    harpoon = LoadTexture("assets/arpon.png");
    crosshair = LoadTexture("assets/mira.png");
    rulesMenu = LoadTexture("assets/rules.png");
    logo = LoadTexture("assets/logo.png");
    win = LoadTexture("assets/win.png");
    lose = LoadTexture("assets/lose.png");
    bigEnemy = LoadTexture("assets/bigEnemy.png");
    mediumEnemy = LoadTexture("assets/mediumEnemy.png");
    smallEnemy = LoadTexture("assets/smallEnemy.png");
    creditUnselectedButton = LoadTexture("assets/creditUnselectedButton.png");
    creditSelectedButton = LoadTexture("assets/creditSelectedButton.png");
    playUnselectedButton = LoadTexture("assets/playUnselectedButton.png");
    playSelectedButton = LoadTexture("assets/playSelectedButton.png");
    rulesUnselectedButton = LoadTexture("assets/rulesUnselectedButton.png");
    rulesSelectedButton = LoadTexture("assets/rulesSelectedButton.png");
    exitUnselectedButton = LoadTexture("assets/exitUnselectedButton.png");
    exitSelectedButton = LoadTexture("assets/exitSelectedButton.png");
    menuUnselectedButton = LoadTexture("assets/menuUnselectedButton.png");
    menuSelectedButton = LoadTexture("assets/menuSelectedButton.png");
    resumeUnselectedButton = LoadTexture("assets/resumeUnselectedButton.png");
    resumeSelectedButton = LoadTexture("assets/resumeSelectedButton.png");

    if (resetCounter < 1)
    {
        if (actualScene == GameScenes::Game)
        {
            resetCounter++;
        }
    }

    InitAudioDevice();

    menuMusic = LoadMusicStream("assets/menuMusic.wav");
    gameMusic = LoadMusicStream("assets/gameMusic.wav");

    creditSound = LoadWave("assets/creditSound.wav");
    deathSound = LoadWave("assets/deathSound.wav");
    dyingFish = LoadWave("assets/dyingFish.wav");
    shootingHarpoon = LoadWave("assets/shootingHarpoon.wav");
    touchingButtons = LoadWave("assets/touchingButtons.wav");

    SetMusicVolume(menuMusic, 0.3);
    SetMusicVolume(gameMusic, 0.3);

    while (!WindowShouldClose() && !exitProgram)
    {
        HideCursor();

        newScene = actualScene != prevScene;
        prevScene = actualScene;

        switch (actualScene)
        {
        case GameScenes::Menu:
        case GameScenes::Win:
        case GameScenes::Lose:
        case GameScenes::Rules:
            StopMusicStream(gameMusic);

            PlayMusicStream(menuMusic);         
            UpdateMusicStream(menuMusic);

            resetStats(player, gameTimer);
            break;

        case GameScenes::Game:
            if (!isGamePaused) 
            {
                if (resetCounter >= 1)
                {
                    asteroidsArray[0].isActive = true;
                    resetCounter = 0;
                }

                StopMusicStream(menuMusic);

                PlayMusicStream(gameMusic);
                UpdateMusicStream(gameMusic);

                gameTimer += GetFrameTime();
                gamePlay(player, actualScene, gameTimer);
            }         
            break;

        case GameScenes::Exit:
            exitProgram = true;
            break;

        case GameScenes::Pause:
            StopMusicStream(menuMusic);

            PlayMusicStream(gameMusic);
            UpdateMusicStream(gameMusic);
            break;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        switch (actualScene)
        {
        case GameScenes::Menu:
            drawMenu(actualScene, screenWidth, logo, crosshair, playUnselectedButton, playSelectedButton, rulesUnselectedButton, rulesSelectedButton, exitUnselectedButton, exitSelectedButton, background, creditUnselectedButton, creditSelectedButton);
            break;

        case GameScenes::Game:
            if (!isGamePaused)
            {
                drawGamePlay(player, background, harpoon);
            }
            break;

        case GameScenes::Rules:
            drawRules(rulesMenu, menuUnselectedButton, menuSelectedButton, actualScene, crosshair);
            break;

        case GameScenes::Exit:
            exitProgram = true;
            break;

        case GameScenes::Win:
            drawWinScreen(actualScene, crosshair, win, menuUnselectedButton, menuSelectedButton, playUnselectedButton, playSelectedButton);
            break;

        case GameScenes::Lose:
            drawLoseScreen(actualScene, crosshair, lose, menuUnselectedButton, menuSelectedButton, playUnselectedButton, playSelectedButton);
            break;

        case GameScenes::Pause:
            drawPause(actualScene, logo, crosshair, background, menuUnselectedButton, menuSelectedButton, resumeUnselectedButton, resumeSelectedButton, screenHeight, screenWidth, isGamePaused);
            break;
        }

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();       
}

void gamePlay(Player& player, GameScenes& actualScene, float gameTimer)
{
    if (IsMouseButtonPressed(2))
    {
        actualScene = GameScenes::Pause;
    }

    playerMovement(player, screenWidth, screenHeight);
    checkUpdateBullets(player);
    updateAsteroidArray(asteroidsArray);
    asteroidsCreation(asteroidsArray, smallEnemy, mediumEnemy, bigEnemy);
    checkGameCollisions(player, asteroidsArray, smallEnemy, mediumEnemy, bigEnemy);
    winOrLose(actualScene, player, gameTimer);
}

void drawGamePlay(Player& player, Texture2D background, Texture2D harpoon)
{
    DrawTexture(background, 0, 0, WHITE);
    checkDrawBullets(player, harpoon);
    drawPlayer(player, WHITE, playerSpray, crosshair);
    drawAsteroidArray(asteroidsArray);
    checkGameCollisions(player, asteroidsArray, smallEnemy, mediumEnemy, bigEnemy);
}

void resetStats(Player& player, float& gameTimer)
{
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;
    player.velocity = { 0, 0 };
    player.lifes = 3;

    for (int i = 0; i < player.maxBullets; i++)
    {
        player.bulletsArray[i].isActive = false;
    }

    for (int i = 0; i < maxAsteroids; i++)
    {
        asteroidsArray[i].isActive = false;
    }

    gameTimer = 0.0f;
}

void winOrLose(GameScenes& actualScene, Player& player, float gameTimer)
{
    if (player.lifes <= 0)
    {
        actualScene = GameScenes::Lose;
    }

    if (gameTimer >= 150 && player.lifes > 0)
    {
        actualScene = GameScenes::Win;
    }
}




