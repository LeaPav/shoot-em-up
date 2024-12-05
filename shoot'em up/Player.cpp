#include "Player.h"

void Player::initSprite()
{

	recPlayer.setSize(Vector2f(100.f, 100.f));
	recPlayer.setFillColor(Color::Red);
	recPlayer.setPosition(10,10);

}

void Player::initTexture()
{

}

Player::Player()
{
	initSprite();
}

void Player::movement(int dx, int dy)
{
	recPlayer.setPosition(x, y);
}

void Player::setPosition(const float x, const float y)
{

}

void Player::playerCollisions()
{
	FloatRect playerBounds = recPlayer.getGlobalBounds();

	//Collisions avec la droite
	if (playerBounds.getPosition().x + playerBounds.width > 1920) {
		recPlayer.setPosition(1920 - playerBounds.width, playerBounds.getPosition().y);
	}

	//Collisions avec la gauche
	if (playerBounds.getPosition().x < 0) {
		recPlayer.setPosition(0, playerBounds.getPosition().y);
	}
	//Collisions avec le haut
	if (playerBounds.getPosition().y < 0) {
		recPlayer.setPosition(playerBounds.getPosition().x, 0);
	}

	// Collisions avec le bas
	if (playerBounds.getPosition().y + playerBounds.height > 1080) {
		recPlayer.setPosition(playerBounds.getPosition().x, 1080 - playerBounds.height);
	}
}

void Player::playerMovement()
{
	playerCollisions();
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		recPlayer.move(8.f, 0.f);
	}

	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		recPlayer.move(-12.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		recPlayer.move(0.f, -12.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		recPlayer.move(0.f, 12.f);
	}
}


void Player::playerUpdate()
{
	playerCollisions();
}

void Player::render(RenderTarget& target)
{
	playerMovement();
	target.draw(recPlayer);
}
