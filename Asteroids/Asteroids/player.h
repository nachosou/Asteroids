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
	float rotation; 
	Vector2 origin;
	static const int maxBullets = 20;
	Bullets bulletsArray[maxBullets];
	Rectangle source;
	Rectangle dest;
	int lifes = 3; 
	float radius = 15; 
	bool isActive;
	int points;
	float invulnerabilityTime = 1.2f;
};

void playerMovement(Player& player, int screenWidth, int screenHeight, Sound shootingSound);

void drawPlayer(Player player, Color color, Texture2D playerSpray, Texture2D crosshair);

void screenReflection(Player& player, int screenWidth, int screenHeight);

void addBullet(Player& player, Vector2 position);

void checkUpdateBullets(Player& player);

void checkDrawBullets(Player& player, Texture2D harpoon);

