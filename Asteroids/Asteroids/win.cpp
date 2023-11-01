#include "win.h"

void drawWinScreen(GameScenes& actualScene, Texture2D crosshair, Texture2D win, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, Texture2D playUnselectedButton, Texture2D playSelectedButton)
{
	Vector2 posMouse = GetMousePosition();

	DrawTexture(win, 0, 0, WHITE);

	GameScenes menu = GameScenes::Menu;
	GameScenes play = GameScenes::Game;

	buttons(actualScene, menu, 849, 618, 200, 100, menuUnselectedButton, menuSelectedButton);
	buttons(actualScene, play, 699, 618, 200, 100, playUnselectedButton, playSelectedButton);

	DrawTexture(crosshair, posMouse.x, posMouse.y, WHITE);
}