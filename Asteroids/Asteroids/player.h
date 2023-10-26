#pragma once
#include "raylib.h"
#include "raymath.h"
#include "bullet.h"

struct Player
{
	Vector2 pos;
	Vector2 dir;
	Vector2 aceleration = {300, 300};
	Vector2 velocity = {0, 0};
};

void playerMovement(Player& player, Texture2D playerTexture, int screenWidth, int screenHeight);

void drawPlayer(Rectangle rec, Vector2 origin, float angle, Color color);

void CheckScreenBoundsCollision(Player& player, int screenWidth, int screenHeight);

