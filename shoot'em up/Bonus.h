#pragma once
#include "stdafx.h"
class Bonus
{
public:
	enum AllBonus {
		FastShooting,
		TripleShooting,
		Laser,
		Shield,
		HealthKit,
		SlowEnnemyProjectiles,
		OffensiveShield,
		Speed,
	};
private:
	AllBonus bonus;
	Sprite sprite;
	Texture texture;
	bool isActive;
	int initSprite();
	void initTexture();
public:
	Bonus(AllBonus bonus, const Texture& texture, Vector2f position);
	void render(RenderTarget& target);
	const FloatRect getBounds() const;
	AllBonus getBonus() const;
	void deactivate();
};

