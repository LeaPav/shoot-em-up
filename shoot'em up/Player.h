#pragma once
#include "Entity.h"
#include "stdafx.h"

class Player : public Entity 
{
private:
	Sprite sprite;
	Texture vaisseau;
	RectangleShape recPlayer;

	void initSprite(); 
	void initTexture();

	int hp;
public:
	Player();

	void movement(int dx, int dy) override;
	void setPosition(const float x, const float y);
	const Vector2f getPosition() const;
	void playerCollisions();
	void playerMovement();

	void damage(int damages);
	bool isDead() const;
	void playerUpdate();
	void render(RenderTarget &target);
	FloatRect getGlobalBounds() const;

};

