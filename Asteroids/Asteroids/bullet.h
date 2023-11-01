#pragma once
#include "raylib.h"
#include "raymath.h"

struct Bullets
{
	Vector2 pos;
	Vector2 dir;
	int radius = 5;
	bool isActive{false};
	int speed = 500;
	float timeAlive = 2.0f;
	float currentTime = 0;
};

bool bulletUpdate(Bullets& bullet);
void bulletDrawing(Bullets bullet, Texture2D harpoon);
Bullets createBullet(Vector2 position, Vector2 direction);
