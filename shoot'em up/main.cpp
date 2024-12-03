#include "stdafx.h"
#include "Game.h"
 
int main() {

	Game game;


	cout << "Hello World";

	while (game.windowIsOpen()) {

		game.update();
		game.render();

	}
	//RenderWindow window(VideoMode(500, 500), "Fenêtre SFML");

	return 0;
	
}
//test