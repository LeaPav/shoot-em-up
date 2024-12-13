#pragma once
#include "stdafx.h"
#include "Entity.h"
class Boss : public Entity
{
private:
	Sprite sprite;
	Texture boss;
	RectangleShape recBoss;
	RectangleShape recRobot;
	int hp;
	bool isActive;
	Vector2f targetPosition; // là où il doit se rendre
	Vector2f initialPosition;
	Vector2f velocity;
	float shootSpeed;

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
	void reset();
};

