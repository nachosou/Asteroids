#pragma once
#include "raylib.h"
#include "raymath.h"
#include "bullet.h"

struct Player
{
	Vector2 pos;
	Vector2 dir;
	Vector2 aceleration = {500, 500};
	Vector2 velocity = {0, 0};
	static const int maxBullets = 20;
	Bullets bulletsArray[maxBullets];
};

void playerMovement(Player& player, Texture2D playerTexture, int screenWidth, int screenHeight);

void drawPlayer(Rectangle rec, Player player, Color color);

void screenReflection(Player& player, int screenWidth, int screenHeight);

void addBullet(Player& player, Vector2 position);

void checkUpdateBullets(Player& player);

void checkDrawBullets(Player& player);

