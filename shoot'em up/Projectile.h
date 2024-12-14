#pragma once
#include "stdafx.h"

class Projectile
{
public: 
	enum ProjectileType {
		PLAYER,
		ENNEMY,
		BOSS
	};
private:
	RectangleShape projectile;
	Vector2f velocity;

	Texture projoPlayer, projoBoss, projoEnnemy;
	Sprite sprite;
	ProjectileType type;
	bool isOutOfScreen;
	void initProjectiles();
	
	void initTexture();
public:
	Projectile(float x, float y, float speedX, float speedY, ProjectileType type);
	~Projectile();

	void update();
	void render(RenderTarget& target);
	FloatRect getGlobalBounds() const;
	void markAsOutOfScreen();
	bool outOfScreen() const; // avec IsOutOfScreen

};

