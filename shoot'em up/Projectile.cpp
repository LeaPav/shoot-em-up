#include "Projectile.h"

Projectile::Projectile(float x, float y, float speedX, float speedY, ProjectileType type) : velocity(speedX, speedY), isOutOfScreen(false), type(type)
{
	this->initProjectiles();
	this->initTexture();
	this->sprite.setPosition(x, y);
}

Projectile::~Projectile() {}

////////////////////////////////////////maj du projo/////////////////////////////////////

void Projectile::initProjectiles()
{
	switch (this->type) {
	case ProjectileType::PLAYER:
		if (!projoPlayer.loadFromFile("assets\\joueur\\Projo lisse.png"))
			cout << "ERREUR, impossible de charger la texture.";
	case ProjectileType::ENNEMY:
		if (!projoEnnemy.loadFromFile("assets\\Ennemies\\Projo ennemy.png"))
			cout << "ERREUR, impossible de charger la texture.";
	case ProjectileType::BOSS:
		if (!projoBoss.loadFromFile("assets\\boss\\Projo_boss.png"));
	}
	
}

void Projectile::initTexture()
{
	switch (this->type) {
	case ProjectileType::PLAYER:
		this->sprite.setTexture(projoPlayer);
		break;
	case ProjectileType::ENNEMY:
		this->sprite.setTexture(projoEnnemy);
		break;
	case ProjectileType::BOSS:
		this->sprite.setTexture(projoBoss);
		break;
	}
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
	if (sprite.getPosition().x < 0 || sprite.getPosition().x > 1950 || sprite.getPosition().y < 0 || sprite.getPosition().y > 1080) {
		markAsOutOfScreen();
	}
}

void Projectile::markAsOutOfScreen()
{
	this->isOutOfScreen = true;
}

bool Projectile::outOfScreen() const
{
	return this->isOutOfScreen;
}




