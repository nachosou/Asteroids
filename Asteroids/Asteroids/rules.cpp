#include "rules.h"

void drawRules(Texture2D rulesMenu, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, GameScenes& actualScene, Texture2D crosshair, Sound touchingButtons)
{
	Vector2 posMouse = GetMousePosition();

	DrawTexture(rulesMenu, 0, 0, WHITE);

	GameScenes menu = GameScenes::Menu;

	buttons(actualScene, menu, 899, 618, 200, 100, menuUnselectedButton, menuSelectedButton, touchingButtons);

	DrawTexture(crosshair, posMouse.x, posMouse.y, WHITE);
}