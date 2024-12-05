#pragma once
#include "Projectiles.h"


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
	cout << "le projectiles est detruit" << endl;
}



JoueurProjo::JoueurProjo(int a, int b) : Projectiles(a, b) {
	initSpriteProjo();
}

void JoueurProjo::tirerSimple() {				//actuve le tir du projo


	initSpriteProjo();
	

	
}



void JoueurProjo::initSpriteProjo()				//crée le rectangle visuel
{
	recProjo.setSize(Vector2f(150.f, 20.f));
	recProjo.setFillColor(Color::Yellow);
	recProjo.setPosition(x, y);
	
}




void JoueurProjo::renderProjo(RenderTarget& target)    //dessiner le rectangle
{
	target.draw(recProjo);
}
