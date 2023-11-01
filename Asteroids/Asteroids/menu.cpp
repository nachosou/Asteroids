#include "menu.h"

void drawMenu(GameScenes& actualScene, int screenWidth, Texture2D crosshair, Texture2D playUnselectedButton, Texture2D playSelectedButton, Texture2D rulesUnselectedButton, Texture2D rulesSelectedButton, Texture2D exitUnselectedButton, Texture2D exitSelectedButton, Texture2D background, Texture2D credits)
{
	Vector2 posMouse = GetMousePosition();

	int height = 100;
	int width = 200;

	int middleButtons = screenWidth / 2 - width / 4;
	int middleCredits = screenWidth / 2 - 200;

	DrawTexture(background, 0, 0, WHITE);
	DrawTexture(credits, middleCredits, 650, WHITE);

	GameScenes playScene = GameScenes::Game;
	GameScenes rulesScene = GameScenes::Rules;
	GameScenes exitScene = GameScenes::Exit;

	buttons(actualScene, playScene, middleButtons, 300, width, height, playUnselectedButton, playSelectedButton);

	buttons(actualScene, rulesScene, middleButtons, 400, width, height, rulesUnselectedButton, rulesSelectedButton);

	buttons(actualScene, exitScene, middleButtons, 500, width, height, exitUnselectedButton, exitSelectedButton);

	DrawTexture(crosshair, posMouse.x, posMouse.y, WHITE);
}