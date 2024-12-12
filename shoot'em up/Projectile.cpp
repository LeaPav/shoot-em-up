#include "Projectile.h"

void Projectile::initProjectiles()
{
	projectile.setSize(Vector2f(40.f, 20.f));
	projectile.setFillColor(Color::Blue);
}

Projectile::Projectile(float x, float y, float speedX, float speedY) : velocity(speedX, speedY), isOutOfScreen(false)
{
	this->initProjectiles();
	this->projectile.setPosition(x, y);
}

Projectile::~Projectile(){}

void Projectile::update()
{
	this->projectile.move(this->velocity);

	/*if (this->projectile.getPosition().x > 1920 || this->projectile.getPosition().x < 0 ||
		this->projectile.getPosition().y > 1080 || this-> projectile.getPosition().y < 0) {
		this->isOutOfScreen = true;
	}*/
}

void Projectile::render(RenderTarget& target)
{
	target.draw(this->projectile);
}

FloatRect Projectile::getGlobalBounds() const
{
	return this->projectile.getGlobalBounds();
}

void Projectile::markAsOutOfScreen()
{
	this->isOutOfScreen = true;
}

bool Projectile::outOfScreen() const
{
	return this->isOutOfScreen;
}
