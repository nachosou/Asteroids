#include "buttons.h"

void buttons(GameScenes& actualScene, GameScenes scene, int buttonX, int buttonY, int width, int height, Texture2D buttonUnselected, Texture2D buttonSelected)
{
	if (GetMouseX() >= buttonX 
		&& GetMouseX() <= buttonX + width / 2
		&& GetMouseY() >= buttonY 
		&& GetMouseY() <= buttonY + height / 2)
	{
		
		DrawTexture(buttonSelected, buttonX, buttonY, WHITE);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			actualScene = scene;
		}
	}
	else
	{
		DrawTexture(buttonUnselected, buttonX, buttonY, WHITE);
	}
}