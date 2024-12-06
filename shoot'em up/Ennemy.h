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
	int hp;
public:
	Ennemy(MovementType type = STRAIGHT, int hp);

	~Ennemy();
	void movement(int dx, int dy) override;

	void setPosition(const float x, const float y);
	void update();
	void render(RenderTarget& target);
	void degat(int degats);
	bool isOutOfScreen;
	bool destroy();
};

