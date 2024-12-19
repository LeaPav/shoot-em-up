#include "Player.h"

Player::Player(int rate) : fireRate(rate)   //création joueur
{
	this->initHealthBar();
	this->initSprite();
	this->initTexture();
}

/////////////////////////////////////////maj du joueur/////////////////////////////////////

void Player::initSprite()     //chargement du corps du joueur
{

	/*recPlayer.setSize(Vector2f(100.f, 100.f));
	recPlayer.setFillColor(Color::Red);
	recPlayer.setPosition(10,10);*/

	if (!this->vaisseau.loadFromFile("assets/vaisseau_5.png")) {
		cout << "ERREUR";
	}
	if (!this->vaisseauBouclierDef.loadFromFile("assets/joueur/jouer_proteger.png")) {
		cout << "Erreur";
	}
	if (!this->vaisseauBouclierOff.loadFromFile("assets/joueur/jouer_proteger_pique.png")) {
		cout << "Erreur";
	}

}

void Player::initTexture()   //pose la texture sur le sprite et set up la position
{
	this->sprite.setTexture(vaisseau);
	this->sprite.setPosition(10, 540);
}

void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}

void Player::playerUpdate()
{
	playerCollisions();
	playerMovement();
}

///////////////////////////////life///////////////////////////////////////////////

void Player::initHealthBar()   // santé et barre de vie
{
	this->hp = this->maxHp;
	this->healthBar.setSize(Vector2f(200.f, 20.f));
	this->healthBar.setFillColor(Color(102, 255, 102));

	this->backgroundHealthBar.setSize(Vector2f(200.f, 20.f));
	this->backgroundHealthBar.setFillColor(Color(117, 117, 117));
}

void Player::udpateHealthBar()
{
	float healthPercentage = static_cast<float>(this->hp) / static_cast<float>(this->maxHp);
	this->healthBar.setSize(Vector2f(200.f * healthPercentage, 20.f));
}

void Player::renderHealthBar(RenderTarget& target)
{
	this->backgroundHealthBar.setPosition(10.f, 1050.f);
	this->healthBar.setPosition(10.f, 1050.f);

	target.draw(this->backgroundHealthBar);
	target.draw(this->healthBar);

}

void Player::reset()
{
	hp = maxHp;
	sprite.setPosition(10, 540);
}

void Player::resetSprite()
{
	sprite.setTexture(vaisseau);
}

float Player::resetSpeed()
{
	return speed = 12.f;
}

void Player::setupBonusShieldDef()
{
	this->sprite.setTexture(vaisseauBouclierDef);
}

void Player::setupBonusShieldOff()
{
	this->sprite.setTexture(vaisseauBouclierOff);
}

/////////////////////geter/////////////////////////////////////////////////////

const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();

}

void Player::setHealth(int newHp)
{
	if (newHp > maxHp) {
		hp = maxHp;
	}
	else {
		hp = newHp;
	}
	this->udpateHealthBar();
}

void Player::setMaxHealth(int newMaxHp)
{
	maxHp = newMaxHp;
	hp = maxHp;
}

void Player::setSpeed(float newSpeed)
{
	speed = newSpeed;
}

void Player::setRate(int newRate)
{
	fireRate = newRate;
}

float Player::getSpeed() const
{
	return speed;
}

int Player::getHealth() const
{
	return this->hp;
}
int Player::getHealthMax() const
{
	return this->maxHp;
}
int Player::getShootRate() const
{
	return fireRate;
}
///////////////////////////collision////////////////////////////////////////////////

void Player::playerCollisions()
{
	FloatRect playerBounds = sprite.getGlobalBounds();

	//Collisions avec la droite
	if (playerBounds.getPosition().x + playerBounds.width > 1920) {
		sprite.setPosition(1920 - playerBounds.width, playerBounds.getPosition().y);
	}

	//Collisions avec la gauche
	if (playerBounds.getPosition().x < 0) {
		sprite.setPosition(0, playerBounds.getPosition().y);
	}
	//Collisions avec le haut
	if (playerBounds.getPosition().y < 0) {
		sprite.setPosition(playerBounds.getPosition().x, 0);
	}

	// Collisions avec le bas
	if (playerBounds.getPosition().y + playerBounds.height > 1080) {
		sprite.setPosition(playerBounds.getPosition().x, 1080 - playerBounds.height);
	}
}

////////////////////////////////////////////deplacement/////////////////////////////////////

void Player::movement(int dx, int dy)   //set up pour mouvement
{
	recPlayer.setPosition(x, y);
}

void Player::playerMovement()
{
	playerCollisions();
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		sprite.move(speed-4.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		sprite.move(-speed, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		sprite.move(0.f, -speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		sprite.move(0.f, speed);
	}
	
}

///////////////////////degats///////////////////////////////////////////////

void Player::damage(int damages)
{
	this->hp -= damages;
	if (this->hp < 0)
		this->hp = 0;
}

bool Player::isDead() const
{
	return this->hp <= 0;
}

