#pragma once
#include "raylib.h"
#include "buttons.h"
#include "scenes.h"

void drawWinScreen(GameScenes& actualScene, Texture2D crosshair, Texture2D win, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, Texture2D playUnselectedButton, Texture2D playSelectedButton, Sound touchingButtons);