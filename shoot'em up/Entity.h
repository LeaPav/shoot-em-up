#pragma once

class Entity {
protected:
	int x, y;
	int hp;
	int shield;
public:
	Entity();
	virtual void movement(int dx, int dy) = 0;
};