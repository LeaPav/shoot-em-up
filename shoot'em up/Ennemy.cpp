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

Ennemy::Ennemy(MovementType type) : movementType(type), timeElapsed(0.f), isOutOfScreen(false), hp(1)
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

	float frequency = 2.f;
	float amplitude = 50.f;

	switch (movementType) {
	case STRAIGHT:
		recEnnemy.move(-10.f, 0.f);
		break;
	case DIAGONAL:
		recEnnemy.move(-10.f, 5.f);
		break;
	case SINUSOIDAL:
		recEnnemy.move(-5.f, amplitude * sin(frequency * timeElapsed));
		timeElapsed += 0.1f;
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

int Ennemy::getHp() const
{
	return hp;
}

const Vector2f Ennemy::getPosition() const
{
	return this->sprite.getPosition();
}

bool Ennemy::isDead() const
{
	return this->hp <= 0;
}

void Ennemy::damage(int damages)
{
	this->hp -= damages;
	if (this->hp <= 0) this->hp = 0;
}

bool Ennemy::destroy()
{
	return isOutOfScreen;
}

FloatRect Ennemy::getGlobalBounds() const
{
	return this->recEnnemy.getGlobalBounds();
}
