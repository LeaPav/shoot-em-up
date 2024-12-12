#pragma once
#include "stdafx.h"

class Projectile
{
private:
	RectangleShape projectile;
	Vector2f velocity;

	Texture projoAll;
	Sprite sprite;

	bool isOutOfScreen;
	int initProjectiles();
	
	void initTexture();
public:
	Projectile(float x, float y, float speedX, float speedY);
	~Projectile();

	void update();
	void render(RenderTarget& target);
	FloatRect getGlobalBounds() const;
	void markAsOutOfScreen();
	bool outOfScreen() const; // avec IsOutOfScreen

};

