#include "bullet.h"

static float bulletAngle = 0.0f;

bool bulletUpdate(Bullets& bullet)
{
	if (!bullet.isActive)
	{
		return false;
	}

	bullet.currentTime += GetFrameTime();

	if (bullet.currentTime > bullet.timeAlive)
	{
		bullet.isActive = false;
		return false;
	}

	bullet.pos.x += bullet.speed * bullet.dir.x * GetFrameTime();
	bullet.pos.y += bullet.speed * bullet.dir.y * GetFrameTime();

	return true;
}

void bulletDrawing(Bullets bullet, Texture2D harpoon)
{
	if (bullet.isActive)
	{
		bulletAngle = atan2(bullet.dir.y, bullet.dir.x) * RAD2DEG;

		DrawTexturePro(harpoon, { 0, 0, static_cast<float>(harpoon.width), static_cast<float>(harpoon.height) }, { bullet.pos.x, bullet.pos.y, static_cast<float>(harpoon.width), static_cast<float>(harpoon.height) }, { static_cast<float>(harpoon.width / 2), static_cast<float>(harpoon.height / 2) }, bulletAngle, WHITE);
	} 	
}

Bullets createBullet(Vector2 position, Vector2 direction)
{
	Bullets bullet;
	bullet.pos = position;
	bullet.dir = direction;
	bullet.isActive = true;
	return bullet;
}


