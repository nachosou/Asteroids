#include "asteroids.h"
#include "raymath.h"
#include <iostream>

Asteroids createAsteroids(Vector2 position, Vector2 velocity, asSize SIZE)
{
	Asteroids asteroid;
	asteroid.isActive = true;
	asteroid.SIZE = SIZE;
	asteroid.position = position;
	asteroid.velocity = velocity;
	asteroid.rotation = static_cast<float>(rand() % 360);
	asteroid.rotationSpeed = 70;
	asteroid.creationTime = static_cast<float>(GetTime());
	return asteroid;
}

void asteroidsUpdate(Asteroids& asteroid)
{
	if (!asteroid.isActive)
	{
		return;
	}

	asteroidsMirroring(asteroid, (GetScreenWidth()), (GetScreenHeight()));

	asteroid.position = Vector2Add(asteroid.position, Vector2Scale(asteroid.velocity, GetFrameTime()));
	asteroid.rotation += asteroid.rotationSpeed * GetFrameTime();
}

void asteroidDraw(Asteroids asteroid)
{
	if (!asteroid.isActive)
	{
		return;
	}

	float asteroidRadius = 0;

	if (asteroid.SIZE & Small)
		asteroidRadius = 12;
	else if (asteroid.SIZE & Medium)
		asteroidRadius = 24;
	else if (asteroid.SIZE & Big)
		asteroidRadius = 48;

	DrawCircleLines((asteroid.position.x), (asteroid.position.y), asteroidRadius, WHITE);
}

void addAsteroid(Vector2 position, asSize SIZE)
{
	Vector2 screenCenter = { (GetScreenHeight() / 2),  (GetScreenWidth() / 2) };

	Vector2 velocity = Vector2Subtract(screenCenter, position);
	velocity = Vector2Scale(Vector2Normalize(velocity), (speed));

	velocity = Vector2Rotate(velocity, speed);

	for (int i = 0; i < 10; i++)
	{
		if (asteroidsArray[i].isActive)
		{
			continue;
		}

		asteroidsArray[i] = createAsteroids(position, velocity, SIZE);
		asteroidCounter++;
		break;
	}
}

void asteroidsCreation()
{
	if (GetTime() > lastAsteroidCreationTime + asteroidCoolDown && asteroidCounter < maxAsteroids / 4)
	{
		asSize nextSize = asteroidSizes[GetRandomValue(0, 2)];
		addAsteroid(nextAsteroidPosition(), nextSize);
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

void asteroidsMirroring(Asteroids& asteroid, float screenWidth, float screenHeight)
{
	if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() > screenWidth)
	{
		asteroid.position.x = 0;
		if (asteroid.velocity.y > 0)
		{
			if (asteroid.position.y > screenHeight / 2)
				asteroid.position.y = screenHeight - asteroid.position.y;
		}
		else if (asteroid.velocity.y < 0)
		{
			if (asteroid.position.y < screenHeight / 2)
				asteroid.position.y = screenHeight - asteroid.position.y;
		}
	}
	else if (asteroid.position.x + asteroid.velocity.x * GetFrameTime() < 0)
	{
		asteroid.position.x = screenWidth;
		if (asteroid.velocity.y > 0)
		{
			if (asteroid.position.y > screenHeight / 2)
				asteroid.position.y = screenHeight - asteroid.position.y;
		}
		else if (asteroid.velocity.y < 0)
		{
			if (asteroid.position.y < screenHeight / 2)
				asteroid.position.y = screenHeight - asteroid.position.y;
		}
	}

	if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() > screenHeight)
	{
		asteroid.position.y = 0;
		if (asteroid.velocity.x > 0)
		{
			if (asteroid.position.x > screenWidth / 2)
				asteroid.position.x = screenWidth - asteroid.position.x;
		}
		else if (asteroid.velocity.x < 0)
		{
			if (asteroid.position.x < screenWidth / 2)
				asteroid.position.x = screenWidth - asteroid.position.x;
		}
	}
	else if (asteroid.position.y + asteroid.velocity.y * GetFrameTime() < 0)
	{
		asteroid.position.y = screenHeight;
		if (asteroid.velocity.x > 0)
		{
			if (asteroid.position.x > screenWidth / 2)
				asteroid.position.x = screenWidth - asteroid.position.x;
		}
		else if (asteroid.velocity.x < 0)
		{
			if (asteroid.position.x < screenWidth / 2)
				asteroid.position.x = screenWidth - asteroid.position.x;
		}
	}
}