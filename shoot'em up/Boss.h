#pragma once
#include "stdafx.h"
#include "Entity.h"
class Boss : public Entity
{
private:
	Sprite sprite;
	Texture boss;
	RectangleShape recBoss;
	RectangleShape recRobot1, recRobot2;
	int hp;
	bool isActive;
	
	Vector2f velocity;
	float shootSpeed;

	int phase;
	int robotHp1, robotHp2;

	//Projectiles
	vector<RectangleShape> projectiles;
	Clock shootClock;

	void initSprite();
	void initTexture();

public:
	Boss();
	void takeDamage(int damage);
	void movement(int dx, int dy) override;
	const Vector2f getPosition() const;
	int getHp();
	void render(RenderTarget& target);
	FloatRect getGlobalBounds() const;
	void update();
	bool canSpawn(int bossScore);
	bool isBossActive() const;
	void reset();
	void handleRobots();
	void shooting();
};

