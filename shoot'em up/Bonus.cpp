#include "Bonus.h"

int Bonus::initSprite()
{
	if (!texture.loadFromFile("test.png"));
	return -1;
}

void Bonus::initTexture()
{
	this->sprite.setTexture(texture);
}

Bonus::Bonus(AllBonus bonus, const Texture& texture, Vector2f pos) : bonus(bonus), isActive(true), position(pos)
{
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	//this->initSprite();
	
}

void Bonus::render(RenderTarget& target)
{
	if (isActive) {
		target.draw(this->sprite);
	}
}

FloatRect Bonus::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

bool Bonus::contains(const FloatRect& bounds) const
{
	return FloatRect(position, size).intersects(bounds);
}

Bonus::AllBonus Bonus::getBonus() const
{
	return bonus;
}

void Bonus::deactivate()
{
	isActive = false;
}
