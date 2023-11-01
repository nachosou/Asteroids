#include "raylib.h"
#include "iostream"
#include "player.h"
#include "scenes.h"
#include "bullet.h"
#include "menu.h"
#include "asteroids.h"
#include "rules.h"
#include "pause.h"

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
Texture2D background;
Texture2D playerSpray;
Texture2D credits;
Texture2D harpoon;
Texture2D crosshair;
Texture2D rulesMenu;
Texture2D logo;
Texture2D win;
Texture2D lose;

void gamePlay(Player& player, GameScenes& actualScene);
void drawGamePlay(Player& player, Texture2D background, Texture2D harpoon);
void resetStats(Player& player, Asteroids asteroidsArray[]);

void main()
{
    Player player;
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;

    GameScenes actualScene = GameScenes::Menu;
    bool newScene = true;
    GameScenes prevScene = actualScene;

    bool exitProgram = false;
    bool isGamePaused = false;

    InitWindow(screenWidth, screenHeight, "ASTEROIDS");

    background = LoadTexture("assets/background.png");
    playerSpray = LoadTexture("assets/buzo.png");
    credits = LoadTexture("assets/creditos.png");
    harpoon = LoadTexture("assets/arpon.png");
    crosshair = LoadTexture("assets/mira.png");
    rulesMenu = LoadTexture("assets/rules.png");
    logo = LoadTexture("assets/logo.png");
    win = LoadTexture("assets/win.png");
    lose = LoadTexture("assets/lose.png");
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

    while (!WindowShouldClose() && !exitProgram)
    {
        HideCursor();

        newScene = actualScene != prevScene;
        prevScene = actualScene;

        switch (actualScene)
        {
        case GameScenes::Menu:
            resetStats(player, asteroidsArray);
            break;

        case GameScenes::Game:
            if (!isGamePaused) 
            {
                gamePlay(player, actualScene);
            }         
            break;

        case GameScenes::Rules:
            
            break;

        case GameScenes::Exit:
            exitProgram = true;
            break;

        case GameScenes::Win:

            break;

        case GameScenes::Lose:

            break;

        case GameScenes::Pause:

            break;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        switch (actualScene)
        {
        case GameScenes::Menu:
            drawMenu(actualScene, screenWidth, logo, crosshair, playUnselectedButton, playSelectedButton, rulesUnselectedButton, rulesSelectedButton, exitUnselectedButton, exitSelectedButton, background, credits);
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

            break;

        case GameScenes::Win:

            break;

        case GameScenes::Lose:

            break;

        case GameScenes::Pause:
            drawPause(actualScene, logo, crosshair, background, menuUnselectedButton, menuSelectedButton, resumeUnselectedButton, resumeSelectedButton, screenHeight, screenWidth, isGamePaused);
            break;
        }

        EndDrawing();
    }

    CloseWindow();       
}

void gamePlay(Player& player, GameScenes& actualScene)
{
    if (IsMouseButtonPressed(2))
    {
        actualScene = GameScenes::Pause;
    }

    playerMovement(player, screenWidth, screenHeight);
    checkUpdateBullets(player);
    updateAsteroidArray();
    asteroidsCreation();
    checkGameCollisions(player);
}

void drawGamePlay(Player& player, Texture2D background, Texture2D harpoon)
{
    DrawTexture(background, 0, 0, WHITE);
    checkDrawBullets(player, harpoon);
    drawPlayer(player, WHITE, playerSpray, crosshair);
    drawAsteroidArray();
    checkGameCollisions(player);
}

void resetStats(Player& player, Asteroids asteroidsArray[])
{
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;
    player.velocity = { 0, 0 };

    for (int i = 0; i < player.maxBullets; i++)
    {
        player.bulletsArray[i].isActive = false;
    }
}

