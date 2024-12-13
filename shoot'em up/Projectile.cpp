#include "Projectile.h"

Projectile::Projectile(float x, float y, float speedX, float speedY) : velocity(speedX, speedY), isOutOfScreen(false)
{
	this->initProjectiles();
	this->initTexture();
	this->sprite.setPosition(x, y);
}

Projectile::~Projectile() {}

////////////////////////////////////////maj du projo/////////////////////////////////////

int Projectile::initProjectiles()
{
	if (!projoAll.loadFromFile("assets\\Ennemies\\Projo lisse.png"))
		return -1;
}

void Projectile::initTexture()
{
	this->sprite.setTexture(projoAll);
}

void Projectile::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

/////////////////////geter/////////////////////////////////////////////////////////////

FloatRect Projectile::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

////////////////////////////////////////////deplacement/////////////////////////////////////

void Projectile::update()
{
	this->sprite.move(this->velocity);
}

void Projectile::markAsOutOfScreen()
{
	this->isOutOfScreen = true;
}

bool Projectile::outOfScreen() const
{
	return this->isOutOfScreen;
}




