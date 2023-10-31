#include "bullet.h"

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

void bulletDrawing(Bullets bullet)
{
	if (bullet.isActive)
	{
		DrawCircle(bullet.pos.x, bullet.pos.y, bullet.radius, RED);
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


