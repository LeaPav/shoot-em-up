#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Projectile.h"

enum MovementType {
	STRAIGHT,
	STRAIGHT_FAST,
	DIAGONAL_INVERSE,
	DIAGONAL,
	
};

class Ennemy : public Entity
{
private:
	Sprite sprite;
	

	Texture ennemies1;

	//RectangleShape recEnnemy;
	MovementType movementType;
	float timeElapsed;
	int initSprite();
	void initTexture();
	bool alive = true;
	bool canShootVerif;
	int hp;
	int shootCooldown;
	int fireRate;
	Vector2f velocity;
public:
	Ennemy(MovementType type = STRAIGHT, int life =1, int cooldown = 0, int rate = 30, bool passif = false);

	~Ennemy();
	void movement(int dx, int dy) override;

	void setPosition(const float x, const float y);
	void update();
	void render(RenderTarget& target);
	void damage(int damages);
	int getHp() const;
	bool getPassif() const;
	const Vector2f getPosition() const;
	bool isDead() const;
	bool isOutOfScreen;
	bool destroy();
	bool canShoot();
	bool verifSpawnEnnemy();
	void updateShootCooldown();
	void resetShootCooldown();
	void shoot(vector<Projectile*>& projectiles);
	FloatRect getGlobalBounds() const;
};

