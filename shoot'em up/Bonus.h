#pragma once
#include "stdafx.h"
class Bonus
{
public:
	enum AllBonus {
		DoubleShooting,
		TripleShooting,
		TripleShootingDiag,
		Laser,
		Shield,
		HealthKit,
		SlowEnnemyProjectiles,
		OffensiveShield,
		Speed
	};
private:
	AllBonus bonus;
	Sprite sprite;
	Texture texture;
	Vector2f position;
	Vector2f size;
	bool isActive;
	int initSprite();
	void initTexture();
public:
	Bonus(AllBonus bonus, const Texture& texture, Vector2f position);
	void render(RenderTarget& target);
	FloatRect getBounds() const;
	bool contains(const FloatRect& bounds) const;
	AllBonus getBonus() const;
	void deactivate();
};

