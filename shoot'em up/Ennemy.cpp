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

Ennemy::Ennemy(MovementType type, int hp) : movementType(type), timeElapsed(0.f), isOutOfScreen(false), hp(1)
{
	initSprite();
}

Ennemy::~Ennemy()
{
	
}

void Ennemy::movement(int dx, int dy)
{

	/*if (speedEnnemy.getPosition().x < 1000) {
		recEnnemy.move(-5.f, -10.f);
	}*/
	switch (movementType) {
	case STRAIGHT:
		recEnnemy.move(-10.f, 0.f);
		break;
	case DIAGONAL:
		recEnnemy.move(-10.f, 5.f);
		
		break;
	}

	FloatRect speedEnnemy = recEnnemy.getGlobalBounds();
	if (speedEnnemy.left + speedEnnemy.width <= 0) {
		isOutOfScreen = true;
	}
	if (speedEnnemy.getPosition().y + speedEnnemy.height < 0) {
		isOutOfScreen = true;
	}

	if (speedEnnemy.getPosition().y  > 1080) {
		isOutOfScreen = true;
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

void Ennemy::degat(int degats)
{
	hp -= degats;
	if (hp < 0) hp = 0;
}

bool Ennemy::destroy()
{
	return isOutOfScreen;
}
