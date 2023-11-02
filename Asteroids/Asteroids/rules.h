#pragma once
#include "buttons.h"
#include "raylib.h"
#include "scenes.h"

void drawRules(Texture2D rulesMenu, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, GameScenes& actualScene, Texture2D crosshair, Sound touchingButtons);