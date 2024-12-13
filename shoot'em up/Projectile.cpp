#include "Projectile.h"

int Projectile::initProjectiles()
{

	if (!projoAll.loadFromFile("assets\\Ennemies\\Projo lisse.png"))
		return -1;

	
	//projectile.setSize(Vector2f(40.f, 20.f));
	//projectile.setFillColor(Color::Blue);
}

void Projectile::initTexture()
{
	this->sprite.setTexture(projoAll);
}

Projectile::Projectile(float x, float y, float speedX, float speedY) : velocity(speedX, speedY), isOutOfScreen(false)
{
	this->initProjectiles();
	this->initTexture();
	this->sprite.setPosition(x, y);
}

Projectile::~Projectile(){}

void Projectile::update()
{
	this->sprite.move(this->velocity);

}

void Projectile::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

FloatRect Projectile::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Projectile::markAsOutOfScreen()
{
	this->isOutOfScreen = true;
}

bool Projectile::outOfScreen() const
{
	return this->isOutOfScreen;
}
