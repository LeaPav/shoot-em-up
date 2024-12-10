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

Ennemy::Ennemy(MovementType type, int life, int cooldown, int rate, bool passif) : movementType(type), hp(life), timeElapsed(0.f), isOutOfScreen(false), 
shootCooldown(cooldown), fireRate(rate), canShootVerif(passif)
{
	initSprite();
}

Ennemy::~Ennemy()
{
	
}

void Ennemy::movement(int dx, int dy)
{

	float frequency = 2.f;
	float amplitude = 50.f;

	switch (movementType) {
	case STRAIGHT:
		recEnnemy.move(-10.f, 0.f);
		break;
	case STRAIGHT_FAST:
		recEnnemy.move(-30.f, 0.f);
		break;
	case DIAGONAL:
		if (recEnnemy.getPosition().x <= 1000) {
			recEnnemy.move(-0.f, 10.f);
		}
		else {
			recEnnemy.move(-10.f, 0.f);
		}
		break;
	case DIAGONAL_INVERSE:
		if (recEnnemy.getPosition().x <= 1000) {
			recEnnemy.move(-0.f, -10.f);
		}
		else {
			recEnnemy.move(-10.f, 0.f);
		}
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

bool Ennemy::getPassif() const
{
	return canShootVerif;
}

const Vector2f Ennemy::getPosition() const
{
	return this->recEnnemy.getPosition();
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

bool Ennemy::canShoot()
{
	return shootCooldown <= 0;
}

void Ennemy::updateShootCooldown()
{
	if (shootCooldown > 0)
		shootCooldown--;
}

void Ennemy::resetShootCooldown()
{
	shootCooldown = fireRate;
}

FloatRect Ennemy::getGlobalBounds() const
{
	return this->recEnnemy.getGlobalBounds();
}
