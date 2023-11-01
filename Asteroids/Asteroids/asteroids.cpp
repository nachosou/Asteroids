#include "asteroids.h"
#include "raymath.h"
#include <iostream>

Asteroids createAsteroids(Vector2 pos, Vector2 velocity, asSize SIZE)
{
	Asteroids asteroid;
	asteroid.isActive = true;
	asteroid.SIZE = SIZE;
	asteroid.pos = pos;
	asteroid.velocity = velocity;
	asteroid.rotation = static_cast<float>(rand() % 360);
	asteroid.rotationSpeed = 70;
	asteroid.creationTime = static_cast<float>(GetTime());
	if (asteroid.SIZE & Small)
		asteroid.radius = 12;
	else if (asteroid.SIZE & Medium)
		asteroid.radius = 24;
	else if (asteroid.SIZE & Big)
		asteroid.radius = 48;
	return asteroid;
}

void asteroidsUpdate(Asteroids& asteroid)
{
	if (!asteroid.isActive)
	{
		return;
	}

	asteroidsMirroring(asteroid, (GetScreenWidth()), (GetScreenHeight()));

	asteroid.pos = Vector2Add(asteroid.pos, Vector2Scale(asteroid.velocity, GetFrameTime()));
	asteroid.rotation += asteroid.rotationSpeed * GetFrameTime();
}

void asteroidDraw(Asteroids asteroid)
{
	if (!asteroid.isActive)
	{
		return;
	}

	DrawCircleLines((asteroid.pos.x), (asteroid.pos.y), asteroid.radius, WHITE);
}

void addAsteroid(Vector2 pos, asSize SIZE, Vector2 secondAsteroidVelocity, bool isSpawned)
{
	Vector2 screenCenter = { (GetScreenHeight() / 2),  (GetScreenWidth() / 2) };

	Vector2 firstAsteroidVelocity = Vector2Subtract(screenCenter, pos);
	firstAsteroidVelocity = Vector2Scale(Vector2Normalize(firstAsteroidVelocity), (speed));

	firstAsteroidVelocity = Vector2Rotate(firstAsteroidVelocity, speed);

	if (isSpawned) 
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroidsArray[i].isActive)
			{
				continue;
			}

			asteroidsArray[i] = createAsteroids(pos, firstAsteroidVelocity, SIZE);
			asteroidCounter++;
			break;
		}
	}
	else
	{
		for (int i = 0; i < maxAsteroids; i++)
		{
			if (asteroidsArray[i].isActive)
			{
				continue;
			}

			asteroidsArray[i] = createAsteroids(pos, secondAsteroidVelocity, SIZE);
			asteroidCounter++;
			break;
		}
	}
}

void asteroidsCreation()
{
	if (GetTime() > lastAsteroidCreationTime + asteroidCoolDown && asteroidCounter < maxAsteroids / 4)
	{
		asSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
		addAsteroid(nextAsteroidPosition(), nextSize, { 0, 0 }, true);
		lastAsteroidCreationTime = (GetTime());
	}
}

Vector2 nextAsteroidPosition()
{
	float offScreen = 128.0f;
	Vector2 pos = { -offScreen, -offScreen };

	if (GetRandomValue(0, 1))
	{
		if (GetRandomValue(0, 1))
		{
			pos.y = GetScreenHeight() + offScreen;
		}

		pos.x = (GetRandomValue((-offScreen), GetScreenWidth() + (offScreen)));
	}
	else
	{
		if (GetRandomValue(0, 1))
		{
			pos.x = GetScreenWidth() + offScreen;
		}

		pos.y = (GetRandomValue((-offScreen), GetScreenHeight() + (offScreen)));
	}

	return pos;
}

void updateAsteroidArray()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		asteroidsUpdate(asteroidsArray[i]);
	}
}

void drawAsteroidArray()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		asteroidDraw(asteroidsArray[i]);
	}
}

bool cirCirCollision(float circle1x, float circle1y, float circle1r, float circle2x, float circle2y, float circle2r)
{
	float distX = circle1x - circle2x;
	float distY = circle1y - circle2y;
	float distance = static_cast<float>(sqrt((distX * distX) + (distY * distY)));

	if (distance <= circle1r + circle2r)
	{
		return true;
	}

	return false;
}

void checkGameCollisions(Player& player)
{
	bulletAsteroidCollision(player);
	asteroidPlayerCollision(player);
}

void asteroidPlayerCollision(Player& player)
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		if (!asteroidsArray[i].isActive) continue;

		if (cirCirCollision(player.pos.x, player.pos.y, player.radius, asteroidsArray[i].pos.x, asteroidsArray[i].pos.y, asteroidsArray[i].radius))
		{
			player.lifes--;
		}
	}

	if (player.lifes <= 0)
	{
		player.isActive = false;
	}
}

void asteroidDivider(Asteroids& asteroid, Player& player)
{
	Vector2 screenCenter = { (GetScreenHeight() / 2),  (GetScreenWidth() / 2) };

	Vector2 newFirstAsteroidVelocity = Vector2Subtract(screenCenter, asteroid.pos);
	Vector2 newSecondAsteroidVelocity = Vector2Subtract(screenCenter, asteroid.pos);
	newFirstAsteroidVelocity = Vector2Scale(Vector2Normalize(newFirstAsteroidVelocity), (speed));
	newSecondAsteroidVelocity = Vector2Scale(Vector2Normalize(newFirstAsteroidVelocity), (speed));

	newFirstAsteroidVelocity = Vector2Rotate(newFirstAsteroidVelocity, speed);
	newSecondAsteroidVelocity = Vector2Rotate(newFirstAsteroidVelocity, speed);

	asteroid.isActive = false;
	asteroidCounter--;
	player.points += 10;

	switch (asteroid.SIZE)
	{
	case Big:
		addAsteroid(asteroid.pos, Medium, newFirstAsteroidVelocity, false);
		addAsteroid(asteroid.pos, Medium, newSecondAsteroidVelocity, false);
		break;

	case Medium:
		addAsteroid(asteroid.pos, Small, newFirstAsteroidVelocity, false);
		addAsteroid(asteroid.pos, Small, newSecondAsteroidVelocity, false);
		break;

	case Small:
		asteroid.isActive = false;
		asteroidCounter--;
		break;
	}
}

void bulletAsteroidCollision(Player& player)
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		for (int j = 0; j < player.maxBullets; j++)
		{
			if (!asteroidsArray[i].isActive || !player.bulletsArray[j].isActive) continue;

			if (cirCirCollision(player.bulletsArray[j].pos.x, player.bulletsArray[j].pos.y, player.bulletsArray[j].radius, asteroidsArray[i].pos.x, asteroidsArray[i].pos.y, asteroidsArray[i].radius))
			{
				asteroidDivider(asteroidsArray[i], player);
				player.bulletsArray[j].isActive = false;
			}
		}
	}
}

void asteroidsMirroring(Asteroids& asteroid, float screenWidth, float screenHeight)
{
	if (asteroid.pos.x + asteroid.velocity.x * GetFrameTime() > screenWidth)
	{
		asteroid.pos.x = 0;
		if (asteroid.velocity.y > 0)
		{
			if (asteroid.pos.y > screenHeight / 2)
				asteroid.pos.y = screenHeight - asteroid.pos.y;
		}
		else if (asteroid.velocity.y < 0)
		{
			if (asteroid.pos.y < screenHeight / 2)
				asteroid.pos.y = screenHeight - asteroid.pos.y;
		}
	}
	else if (asteroid.pos.x + asteroid.velocity.x * GetFrameTime() < 0)
	{
		asteroid.pos.x = screenWidth;
		if (asteroid.velocity.y > 0)
		{
			if (asteroid.pos.y > screenHeight / 2)
				asteroid.pos.y = screenHeight - asteroid.pos.y;
		}
		else if (asteroid.velocity.y < 0)
		{
			if (asteroid.pos.y < screenHeight / 2)
				asteroid.pos.y = screenHeight - asteroid.pos.y;
		}
	}

	if (asteroid.pos.y + asteroid.velocity.y * GetFrameTime() > screenHeight)
	{
		asteroid.pos.y = 0;
		if (asteroid.velocity.x > 0)
		{
			if (asteroid.pos.x > screenWidth / 2)
				asteroid.pos.x = screenWidth - asteroid.pos.x;
		}
		else if (asteroid.velocity.x < 0)
		{
			if (asteroid.pos.x < screenWidth / 2)
				asteroid.pos.x = screenWidth - asteroid.pos.x;
		}
	}
	else if (asteroid.pos.y + asteroid.velocity.y * GetFrameTime() < 0)
	{
		asteroid.pos.y = screenHeight;
		if (asteroid.velocity.x > 0)
		{
			if (asteroid.pos.x > screenWidth / 2)
				asteroid.pos.x = screenWidth - asteroid.pos.x;
		}
		else if (asteroid.velocity.x < 0)
		{
			if (asteroid.pos.x < screenWidth / 2)
				asteroid.pos.x = screenWidth - asteroid.pos.x;
		}
	}
}