#pragma once
#include "stdafx.h"

class Projectiles
{
protected:
	int x;
	int y;

public:

	Projectiles(int a, int b);
	int getX();
	int getY();
	void setX(int newX);
	void setY(int newY);
	~Projectiles();
	virtual void tirerSimple() = 0;
};

class JoueurProjo : public Projectiles {
public:

	Sprite sprite;
	RectangleShape recProjo;

	void initSpriteProjo();

	JoueurProjo(int a, int b);

	void tirerSimple() override;

	void renderProjo(RenderTarget& target);

};



