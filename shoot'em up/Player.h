#pragma once
#include "Entity.h"
#include "stdafx.h"

class Player : public Entity 
{
private:
	Sprite sprite;
	Texture vaisseau, vaisseauBouclierDef, vaisseauBouclierOff;
	RectangleShape recPlayer;
	RectangleShape healthBar;
	RectangleShape backgroundHealthBar;
	void initSprite(); 
	void initTexture();
	void initHealthBar();

	int hp;
	int maxHp;

	float speed = 12.f;
public:
	Player();

	void movement(int dx, int dy) override;
	
	const Vector2f getPosition() const;
	void playerCollisions();
	void playerMovement();

	void damage(int damages);
	bool isDead() const;
	void playerUpdate();
	void render(RenderTarget &target);

	void udpateHealthBar();
	void renderHealthBar(RenderTarget& target);
	FloatRect getGlobalBounds() const;

	void setHealth(int newHp);
	void setSpeed(float newSpeed);
	float getSpeed() const;
	int getHealth() const;
	int getHealthMax() const;
	void reset();

	void resetSprite();
	float resetSpeed();
	void setupBonusShieldDef();
	void setupBonusShieldOff();

};

