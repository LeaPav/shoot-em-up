#include "Player.h"


void Player::initSprite()
{

	recPlayer.setSize(Vector2f(100.f, 100.f));
	recPlayer.setFillColor(Color::Red);
	recPlayer.setPosition(10,10);

	if (!this->vaisseau.loadFromFile("assets/vaisseau_5.png")) {
		cout << "ERREUR";
	}

}

void Player::initTexture()
{
	this->sprite.setTexture(vaisseau);
	this->sprite.setPosition(10, 10);
}

Player::Player()
{
	initSprite();
	initTexture();
}

void Player::movement(int dx, int dy)
{
	recPlayer.setPosition(x, y);
}

void Player::setPosition(const float x, const float y)
{

}

const Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

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

void Player::playerMovement()
{
	playerCollisions();
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		sprite.move(8.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		sprite.move(-12.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		sprite.move(0.f, -8.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		sprite.move(0.f, 8.f);
	}
	
}


void Player::playerUpdate()
{
	playerCollisions();
}

void Player::render(RenderTarget& target)
{
	playerMovement();
	target.draw(this->sprite);
}
