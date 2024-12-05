#pragma once
#include "stdafx.h"
#include "Entity.h"

class Ennemy : public Entity
{
private:
	Sprite sprite;
	RectangleShape recEnnemy;

	void initSprite();
	void initTexture();
public:
	Ennemy();

	~Ennemy();
	void movement(int dx, int dy) override;

	void setPosition(const float x, const float y);
	void update();
	void render(RenderTarget& target);

	bool isCollisions = false;
	bool destroy();
};

