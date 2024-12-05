#include "Projectiles.h"
#include "Player.h"
#include "stdafx.h"

Projectiles::Projectiles(int a, int b) : x(a), y(b) {}

int Projectiles::getX() {
	return x;
}
int Projectiles::getY() {
	return y;
}
void Projectiles::setX(int newX) {
	x = newX;
}
void Projectiles::setY(int newY) {
	y = newY;
}

Projectiles::~Projectiles() {
	cout << "le projectioles est détruit" << endl;
}





void JoueurProjo::tirerSimple() {

	initSpriteProjo();

	while (x < 500) {  //ptet geter

		setX(x + 1);
		if (x > 400) {
			
			//ennemies.setlife(life - 1);
			//delete JoueurProjo;
		}
	}
}





void JoueurProjo::initSpriteProjo()
{
	recProjo.setSize(Vector2f(150.f, 20.f));
	recProjo.setFillColor(Color::Yellow);
	recProjo.setPosition(x, y);
	
}




void JoueurProjo::renderProjo(RenderTarget& target)
{
}
