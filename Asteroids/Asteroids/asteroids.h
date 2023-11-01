#pragma once
#include "raylib.h"
#include "bullet.h"
#include "player.h"

static const int asteroidRandomAngle = static_cast<int>(30 * DEG2RAD);

static const int asteroidCoolDown = 1.0f;
static int lastAsteroidCreationTime = -1.0f;

static const int maxAsteroids = 40;
static const int speed = 110;
static int asteroidCounter = 0;

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
	float rotation;
	float rotationSpeed;
	float creationTime;
	Vector2 velocity;
	float radius;
};


Asteroids static asteroidsArray[maxAsteroids] = { 0 };
static asSize asteroidSizes[] = { Small, Medium, Big };

Asteroids createAsteroids(Vector2 pos, Vector2 velocity, asSize SIZE);
void asteroidsUpdate(Asteroids& asteroid);
void asteroidDraw(Asteroids asteroid);
void addAsteroid(Vector2 pos, asSize SIZE, Vector2 secondAsteroidVelocity, bool isSpawned);
void asteroidsCreation();
Vector2 nextAsteroidPosition();
void updateAsteroidArray();
void drawAsteroidArray();
bool cirCirCollision(float circle1x, float circle1y, float circle1r, float circle2x, float circle2y, float circle2r);
void checkGameCollisions(Player& player);
void asteroidPlayerCollision(Player& player);
void asteroidDivider(Asteroids& asteroid, Player& player);
void bulletAsteroidCollision(Player& player);
void asteroidsMirroring(Asteroids& asteroid, float screenWidth, float screenHeight);