#include "Ennemy.h"

void Ennemy::initSprite()
{
	recEnnemy.setSize(Vector2f(75.f, 75.f));
	//recEnnemy.setFillColor(Color::Red);
	//recEnnemy.setPosition(1000, 1000);
}

void Ennemy::initTexture()
{

}

Ennemy::Ennemy()
{
	initSprite();
}

void Ennemy::movement(int dx, int dy)
{

}

void Ennemy::setPosition()
{
	recEnnemy.setPosition(1830, 500);
}

void Ennemy::render(RenderTarget& target)
{
	target.draw(recEnnemy);
}
