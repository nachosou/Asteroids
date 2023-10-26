#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "player.h"
#include "scenes.h"
#include "bullet.h"

using namespace std;
const int screenWidth = 1024;
const int screenHeight = 768;

void main()
{
    Player player;
    player.pos.x = screenWidth / 2;
    player.pos.y = screenHeight / 2;

    Bullets bullet;

    GameScenes scene = GameScenes::Game;

    bool newScene = true;
    GameScenes prevScene = scene;

    Texture2D playerTexture = LoadTexture("assets/buzo.png");

    InitWindow(screenWidth, screenHeight, "ASTEROIDS");

    while (!WindowShouldClose())
    {
        switch (scene)
        {
        case GameScenes::Menu:

            break;

        case GameScenes::Game:
            playerMovement(player, playerTexture, screenWidth, screenHeight);
            break;

        case GameScenes::Rules:

            break;

        case GameScenes::Exit:

            break;

        case GameScenes::History:

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

        HideCursor();

        switch (scene)
        {
        case GameScenes::Menu:

            break;

        case GameScenes::Game:
            playerMovement(player, playerTexture, screenWidth, screenHeight);
            break;

        case GameScenes::Rules:

            break;

        case GameScenes::Exit:

            break;

        case GameScenes::History:

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

