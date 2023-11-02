#pragma once
#include "raylib.h"
#include "bullet.h"
#include "player.h"

static const int asteroidRandomAngle = static_cast<int>(30 * DEG2RAD);

static const int asteroidCoolDown = 1.0f;
static int lastAsteroidCreationTime = -1.0f;

static const int maxAsteroids = 24;
static const int speed = 110;

enum asSize
{
	Small = 1,
	Medium = 2,
	Big = 4
};

struct Asteroids
{
	bool isActive;
	asSize SIZE;
	Vector2 pos;
	Vector2 velocity;
	float radius;
	bool isSpawned;
	Texture2D texture;
};

static asSize asteroidSizes[] = { Small, Medium, Big };

Asteroids createAsteroids(Vector2 pos, Vector2 velocity, asSize SIZE, Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemy);
void asteroidsUpdate(Asteroids& asteroid);
void asteroidDraw(Asteroids asteroid);
void addAsteroid(Vector2 pos, asSize SIZE, Vector2 secondAsteroidVelocity, bool isSpawne, Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemyd, int& asteroidCounter);
void asteroidsCreation(Asteroids asteroidsArray[], Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemy, int& asteroidCounter);
Vector2 nextAsteroidPosition();
void updateAsteroidArray(Asteroids asteroidsArray[]);
void drawAsteroidArray(Asteroids asteroidsArray[]);
bool cirCirCollision(float circle1x, float circle1y, float circle1r, float circle2x, float circle2y, float circle2r);
void checkGameCollisions(Player& player, Asteroids asteroidsArray[], Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemy, Sound deathSound, Sound dyingFish, int& asteroidCounter);
void asteroidPlayerCollision(Player& player, Asteroids asteroidsArray[], Sound deathSound);
void asteroidDivider(Asteroids& asteroid, Player& player, Asteroids asteroidsArray[], Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemy, int& asteroidCounter);
void bulletAsteroidCollision(Player& player, Asteroids asteroidsArray[], Texture2D smallEnemy, Texture2D mediumEnemy, Texture2D bigEnemy, Sound dyingFish, int& asteroidCounter);
void asteroidsMirroring(Asteroids& asteroid, float screenWidth, float screenHeight);