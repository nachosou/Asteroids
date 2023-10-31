#include "menu.h"

void drawMenu(GameScenes& actualScene, int screenWidth, Texture2D playUnselectedButton, Texture2D playSelectedButton, Texture2D rulesUnselectedButton, Texture2D rulesSelectedButton, Texture2D exitUnselectedButton, Texture2D exitSelectedButton)
{
	int height = 100;
	int width = 200;

	int middleButtons = screenWidth / 2 - 50;

	GameScenes playScene = GameScenes::Game;
	GameScenes rulesScene = GameScenes::Rules;
	GameScenes exitScene = GameScenes::Exit;

	buttons(actualScene, playScene, middleButtons, 300, width, height, playUnselectedButton, playSelectedButton);

	buttons(actualScene, rulesScene, middleButtons, 400, width, height, rulesUnselectedButton, rulesSelectedButton);

	buttons(actualScene, exitScene, middleButtons, 500, width, height, exitUnselectedButton, exitSelectedButton);
}