#pragma once
#include "Entity.h"
#include "stdafx.h"

class Player : public Entity 
{
private:
	Sprite sprite;
	RectangleShape recPlayer;

	void initSprite(); 

	void initTexture();
public:
	Player();

	void movement(int dx, int dy) override;
	void setPosition(const float x, const float y);
	void playerCollisions();
	void playerMovement();

	void playerUpdate();
	void render(RenderTarget &target);
};

