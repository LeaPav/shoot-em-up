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

	void movement(int dx, int dy) override;

	void setPosition();
	void render(RenderTarget& target);
};

