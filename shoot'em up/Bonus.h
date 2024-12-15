#pragma once
#include "stdafx.h"
class Bonus
{
private:
	Sprite sprite;
	Texture texture;
	Vector2f position;
public:
	Bonus();
	void render(RenderTarget& target);
	FloatRect getGlobalBounds() const;

};

