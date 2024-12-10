#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Projectile.h"

enum MovementType {
	STRAIGHT,
	DIAGONAL,
	SINUSOIDAL
};

class Ennemy : public Entity
{
private:
	Sprite sprite;
	RectangleShape recEnnemy;
	MovementType movementType;
	float timeElapsed;
	void initSprite();
	void initTexture();
	bool alive = true;
	int hp;
	int shootCooldown;
	int fireRate;
	Vector2f velocity;
public:
	Ennemy(MovementType type = STRAIGHT, int life =1);

	~Ennemy();
	void movement(int dx, int dy) override;

	void setPosition(const float x, const float y);
	void update();
	void render(RenderTarget& target);
	void damage(int damages);
	int getHp() const;
	const Vector2f getPosition() const;
	bool isDead() const;
	bool isOutOfScreen;
	bool destroy();
	bool canShoot();
	void updateShootCooldown();
	void resetShootCooldown();
	void shoot(vector<Projectile*>& projectiles);
	FloatRect getGlobalBounds() const;
};

