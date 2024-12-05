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

Ennemy::~Ennemy()
{
	
}

void Ennemy::movement(int dx, int dy)
{
	//recEnnemy.setPosition(x, y);
	FloatRect speedEnnemy = recEnnemy.getGlobalBounds();

	if (speedEnnemy.getPosition().x + speedEnnemy.width > 0) {
		//if(){}
		recEnnemy.move(-10.f, 0.f);
		//if(){}
	}
	if (speedEnnemy.getPosition().x == 0) {
		isCollisions = true;
	}
}

void Ennemy::setPosition(const float x, const float y)
{
	recEnnemy.setPosition(x, y);
}

void Ennemy::update()
{
	movement(x, y);

}

void Ennemy::render(RenderTarget& target)
{
	target.draw(recEnnemy);
}

bool Ennemy::destroy()
{
	return isCollisions;
}
