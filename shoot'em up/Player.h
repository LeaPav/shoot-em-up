#pragma once
#include "Entity.h"
#include "stdafx.h"
#include "Projectiles.h"

class Player : public Entity 
{
private:
	Sprite sprite;
	RectangleShape recPlayer;

	void initSprite(); 

	void initTexture();
public:
	vector<JoueurProjo*> joueurProjo;
	Player();

	void movement(int dx, int dy) override;

	void playerMovement();

	void playerUpdate();
	void render(RenderTarget &target);
};

