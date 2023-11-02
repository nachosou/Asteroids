#pragma once
#include "buttons.h"
#include "scenes.h"

void drawPause(GameScenes& actualScene, Texture2D logo, Texture2D crosshair, Texture2D background, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, Texture2D resumeUnselectedButton, Texture2D resumeSelectedButton, int screenHeight, int screenWidth, bool& isGamePaused, Sound touchingButtons);
