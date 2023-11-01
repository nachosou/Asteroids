#include "pause.h"

void drawPause(GameScenes& actualScene, Texture2D logo, Texture2D crosshair, Texture2D background, Texture2D menuUnselectedButton, Texture2D menuSelectedButton, Texture2D resumeUnselectedButton, Texture2D resumeSelectedButton, int screenHeight, int screenWidth, bool& isGamePaused)
{
	Vector2 posMouse = GetMousePosition();

	DrawTexture(background, 0, 0, WHITE);
	DrawTexture(logo, screenWidth / 2 - 200, 100, WHITE);

	GameScenes menu = GameScenes::Menu;
	GameScenes resume = GameScenes::Game;

	int middleButtons = screenHeight / 2; 

	buttons(actualScene, menu, screenWidth / 2 - 200, middleButtons, 200, 100, menuUnselectedButton, menuSelectedButton);

	if (GetMouseX() >= screenWidth / 2 + 100
		&& GetMouseX() <= screenWidth / 2 + 100 + 100
		&& GetMouseY() >= middleButtons
		&& GetMouseY() <= middleButtons + 50)
	{

		DrawTexture(resumeSelectedButton, screenWidth / 2 + 100, middleButtons, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			isGamePaused = false;
			actualScene = resume;
		}
	}
	else
	{
		DrawTexture(resumeUnselectedButton, screenWidth / 2 + 100, middleButtons, WHITE);
	}

	DrawTexture(crosshair, posMouse.x, posMouse.y, WHITE);
}