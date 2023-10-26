#pragma once
#include "raylib.h"
#include "player.h"

struct Bullets
{
	Vector2 pos;
	Vector2 dir;
	float rotation;
	bool active;
	float coolDown;
	int speed = 200;
};

