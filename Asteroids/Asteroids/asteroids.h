#pragma once
#include "raylib.h"
#include "bullet.h"

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
	Vector2 position;
	float rotation;
	float rotationSpeed;
	float creationTime;
	Vector2 velocity;
};


Asteroids static asteroidsArray[maxAsteroids] = { 0 };
static asSize asteroidSizes[] = { Small, Medium, Big };

Asteroids createAsteroids(Vector2 position, Vector2 velocity, asSize SIZE);
void asteroidsUpdate(Asteroids& asteroid);
void asteroidDraw(Asteroids asteroid);
void addAsteroid(Vector2 position, asSize SIZE);
void asteroidsCreation();
Vector2 nextAsteroidPosition();
void updateAsteroidArray();
void drawAsteroidArray();
void asteroidsMirroring(Asteroids& asteroid, float screenWidth, float screenHeight);