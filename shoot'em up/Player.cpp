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

}

void Player::playerMovement()
{
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		recPlayer.move(8.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q)) {
		recPlayer.move(-12.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z)) {
		recPlayer.move(0.f, -8.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		recPlayer.move(0.f, 8.f);
	}
	
}

void Player::render(RenderTarget& target)
{
	playerMovement();
	target.draw(recPlayer);
}
