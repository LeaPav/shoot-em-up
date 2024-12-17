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

Bonus::Bonus(AllBonus bonus, const Texture& texture, Vector2f position) : bonus(bonus), isActive(true)
{
	sprite.setTexture(texture);
	sprite.setPosition(position);
	//this->initSprite();
	
}

void Bonus::render(RenderTarget& target)
{
	if (isActive) {
		target.draw(this->sprite);
	}
}

const FloatRect Bonus::getBounds() const
{
	return sprite.getGlobalBounds();
}

Bonus::AllBonus Bonus::getBonus() const
{
	return bonus;
}

void Bonus::deactivate()
{
	isActive = false;
}
