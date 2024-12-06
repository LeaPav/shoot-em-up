#pragma once
#include "stdafx.h"

class Projectile
{
private:
	RectangleShape projectile;
	Vector2f velocity;

	bool isOutOfScreen;
	void initProjectiles();
public:
	Projectile(float x, float y, float speedX, float speedY);
	~Projectile();

	void update();
	void render(RenderTarget& target);
	const RectangleShape& getShape() const;
	FloatRect getGlobalBounds() const;
	void markAsOutOfScreen();
	bool outOfScreen() const; // avec IsOutOfScreen

};

