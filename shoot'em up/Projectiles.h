#pragma once
class Projectiles
{
protected:
	int x;
	int y;

public:

	Projectiles(int a, int b) : x(a), y(b) {}
	int getX() {}
	int getY() {}
	void setX(int newX) {}
	void setY(int newY) {}
	~Projectiles() {}
	virtual void tirerSimple() = 0;
};

class JoueurProjo : public Projectiles {
public:

	Sprite sprite;
	RectangleShape recProjo;

	void initSpriteProjo();

	JoueurProjo(int a, int b) : Projectiles(a, b) {}

	void tirerSimple() override {}

	void renderProjo(RenderTarget& target);

};



