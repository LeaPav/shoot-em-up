#pragma once
#include "stdafx.h"
#include "Entity.h"

enum MovementType {
	STRAIGHT,
	DIAGONAL
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
public:
	Ennemy(MovementType type = STRAIGHT);

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
	FloatRect getGlobalBounds() const;
};

