#include "stdafx.h"
#include "Game.h"
 
int main() {
	srand(time(0));
	Game game;

	while (game.windowIsOpen()) {

		game.update();
		game.render();


	}
	//RenderWindow window(VideoMode(500, 500), "Fenêtre SFML");

	return 0;
	
}
//test