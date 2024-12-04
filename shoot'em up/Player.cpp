#include "Player.h"

void Player::initSprite()
{

	recPlayer.setSize(Vector2f(100.f, 50.f));
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
	}
}

void Player::render(RenderTarget& target)
{
	target.draw(recPlayer);
}
