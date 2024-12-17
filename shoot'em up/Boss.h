#pragma once
#include "stdafx.h"
#include "Entity.h"
#include "Player.h"
class Boss : public Entity
{
private:
	Sprite sprite, spriteRobot1, spriteRobot2;
	Texture boss, bossPhase2, bossPhaseInterHaut, bossPhaseInterBas, bossPresqueMort, bossMort;
	Texture robot1, robot2;
	int hp;
	int maxHp;
	bool isActive;
	bool firstMove;
	Vector2f velocity;
	float shootSpeed;
	float speedX; 
	float speedY;
	
	Vector2f direction;
	int phase;
	int robotHp1, robotHp2;

	//Projectiles
	vector<RectangleShape> projectiles;
	Clock shootClock;

	void initSprite();
	void initTexture();

	//Barre de vie
	RectangleShape healthBar;
	RectangleShape backgroundHealthBar;

public:
	Boss(float x = 3.5f, float y = 2.f);
	void takeDamage(int damage);
	void movement(int dx, int dy) override;
	const Vector2f getPosition() const;
	int getHp();
	void render(RenderTarget& target);
	FloatRect getGlobalBounds() const;
	void update();
	bool canSpawn(int bossScore, int spawnBoss);
	bool isBossActive() const;
	bool isBossDead() const;
	bool verifSpawnBoss() const;
	void initHealthBar();
	void udpateHealthBar();
	void renderHealthBar(RenderTarget& target);
	void initName();
	void reset();
	
	bool shouldShoot() const;
	int getPhase() const;
	Vector2f getRobot1Position() const;
	Vector2f getRobot2Position() const;
	
	void restartShootClock();

	bool isRobot1Active() const;
	bool isRobot2Active() const;

	FloatRect getRobot1Bounds() const;
	FloatRect getRobot2Bounds() const;

	void damageRobot1(int damage);
	void damageRobot2(int damage);
	
	
	bool isRobot1Dead();
	bool isRobot2Dead();

	Text nameBoss;
	Font font;
}; 

