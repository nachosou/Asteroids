#include "raylib.h"
#include "iostream"
#include "player.h"
#include "scenes.h"
#include "bullet.h"
#include "menu.h"
#include "asteroids.h"

using namespace std;
const int screenWidth = 1024;
const int screenHeight = 768;

Texture2D playUnselectedButton;
Texture2D playSelectedButton;
Texture2D rulesUnselectedButton;
Texture2D rulesSelectedButton;
Texture2D exitUnselectedButton;
Texture2D exitSelectedButton;

void gamePlay(Player& player);
void drawGamePlay(Player& player);

void main()
{
    Player player;
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;

    Rectangle rec;
    rec.width = 20;
    rec.height = 20;

    GameScenes actualScene = GameScenes::Menu;
    bool newScene = true;
    GameScenes prevScene = actualScene;

    bool exitProgram = false;
    bool isGamePaused = false;

    InitWindow(screenWidth, screenHeight, "ASTEROIDS");

    playUnselectedButton = LoadTexture("assets/playUnselectedButton.png");
    playSelectedButton = LoadTexture("assets/playSelectedButton.png");
    rulesUnselectedButton = LoadTexture("assets/rulesUnselectedButton.png");
    rulesSelectedButton = LoadTexture("assets/rulesSelectedButton.png");
    exitUnselectedButton = LoadTexture("assets/exitUnselectedButton.png");
    exitSelectedButton = LoadTexture("assets/exitSelectedButton.png");

    while (!WindowShouldClose() && !exitProgram)
    {
        rec.x = player.pos.x;
        rec.y = player.pos.y;

        newScene = actualScene != prevScene;
        prevScene = actualScene;

        switch (actualScene)
        {
        case GameScenes::Menu:
            
            break;

        case GameScenes::Game:
            if (!isGamePaused) 
            {
                gamePlay(player);
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
            drawMenu(actualScene, screenWidth, playUnselectedButton, playSelectedButton, rulesUnselectedButton, rulesSelectedButton, exitUnselectedButton, exitSelectedButton);
            break;

        case GameScenes::Game:
            drawGamePlay(player);
            break;

        case GameScenes::Rules:

            break;

        case GameScenes::Exit:

            break;

        case GameScenes::Win:

            break;

        case GameScenes::Lose:

            break;

        case GameScenes::Pause:

            break;
        }

        EndDrawing();
    }

    CloseWindow();       
}

void gamePlay(Player& player)
{
    playerMovement(player, screenWidth, screenHeight);
    checkUpdateBullets(player);
    updateAsteroidArray();
    asteroidsCreation();
}

void drawGamePlay(Player& player)
{
    HideCursor();
    drawPlayer(player, WHITE);
    checkDrawBullets(player);
    drawAsteroidArray();
}

