#include "player.h"

Vector2 posMouse;
float angle = 0.0f;
Vector2 origin;


void playerMovement(Player& player, Texture2D playerTexture, int screenWidth, int screenHeight)
{
    posMouse = GetMousePosition();

    player.dir = Vector2Normalize(Vector2Subtract(posMouse, player.pos));

    player.pos = Vector2Add(player.pos, Vector2Scale(player.velocity, GetFrameTime()));

    angle = atan2(player.dir.y, player.dir.x) * RAD2DEG + 90.0f;

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.velocity.x += player.dir.x * GetFrameTime() * player.aceleration.x;
        player.velocity.y += player.dir.y * GetFrameTime() * player.aceleration.y;
    }

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		addBullet(player, Vector2Add(player.pos, player.dir));
	}

    DrawCircle(posMouse.x, posMouse.y, 5, RED);

	screenReflection(player, screenWidth, screenHeight);
}

void drawPlayer(Rectangle rec, Player player, Color color)
{
	angle = atan2(player.dir.y, player.dir.x) * RAD2DEG + 90.0f;

	origin = { rec.width / 2, rec.height / 2 };

    DrawRectanglePro(rec, origin, angle, color);
}

void screenReflection(Player& player, int screenWidth, int screenHeight)
{
	if (player.pos.x + player.velocity.x * GetFrameTime() > screenWidth)
	{
		player.pos.x = 0;
		if (player.velocity.y > 0)
		{
			if (player.pos.y > screenHeight / 2)
				player.pos.y = screenHeight - player.pos.y;
		}
		else if (player.velocity.y < 0)
		{
			if (player.pos.y < screenHeight / 2)
				player.pos.y = screenHeight - player.pos.y;
		}
	}
	else if (player.pos.x + player.velocity.x * GetFrameTime() < 0)
	{
		player.pos.x = screenWidth;
		if (player.velocity.y > 0)
		{
			if (player.pos.y > screenHeight / 2)
				player.pos.y = screenHeight - player.pos.y;
		}
		else if (player.velocity.y < 0)
		{
			if (player.pos.y < screenHeight / 2)
				player.pos.y = screenHeight - player.pos.y;
		}
	}

	if (player.pos.y + player.velocity.y * GetFrameTime() > screenHeight)
	{
		player.pos.y = 0;
		if (player.velocity.x > 0)
		{
			if (player.pos.x > screenWidth / 2)
				player.pos.x = screenWidth - player.pos.x;
		}
		else if (player.velocity.x < 0)
		{
			if (player.pos.x < screenWidth / 2)
				player.pos.x = screenWidth - player.pos.x;
		}
	}
	else if (player.pos.y + player.velocity.y * GetFrameTime() < 0)
	{
		player.pos.y = screenHeight;
		if (player.velocity.x > 0)
		{
			if (player.pos.x > screenWidth / 2)
				player.pos.x = screenWidth - player.pos.x;
		}
		else if (player.velocity.x < 0)
		{
			if (player.pos.x < screenWidth / 2)
				player.pos.x = screenWidth - player.pos.x;
		}
	}
}

void addBullet(Player& player, Vector2 position)
{
	for (int i = 0; i < player.maxBullets; i++)
	{
		if (player.bulletsArray[i].isActive)
		{
			continue;
		}

		player.bulletsArray[i] = createBullet(position, player.dir);
		break;
	}
}

void checkUpdateBullets(Player& player)
{
	for (int i = 0; i < player.maxBullets; i++)
	{
		bulletUpdate(player.bulletsArray[i]);
	}
}

void checkDrawBullets(Player& player)
{
	for (int i = 0; i < player.maxBullets; i++)
	{
		bulletDrawing(player.bulletsArray[i]);
	}
}

