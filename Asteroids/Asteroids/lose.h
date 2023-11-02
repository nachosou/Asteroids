#pragma once
#include "raylib.h"
#include "buttons.h"
#include "scenes.h"

void drawLoseScreen(GameScenes& actualScene, Texture2D crosshair, Texture2D lose, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, Texture2D playUnselectedButton, Texture2D playSelectedButton, Sound touchingButtons, Sound deathSound);