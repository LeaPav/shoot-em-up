#include "GameOver.h"

int GameOver::initFont()
{
	if (!fontOver.loadFromFile("assets/font/fontpause.ttf")) {
		cout << "ERREUR";
	}

}

void GameOver::initButton()
{
	gameOverText.setFont(fontOver);
	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(80);

	FloatRect gameOverTextBounds = gameOverText.getLocalBounds();
	float x = (1920 / 2.f) - (gameOverTextBounds.width / 2.f) - gameOverTextBounds.left;
	gameOverText.setPosition(x, 200);
	gameOverText.setFillColor(Color::Red);

	retryButton.setFont(fontOver);
	retryButton.setString("Rejouer");
	retryButton.setCharacterSize(30);

	FloatRect retryButtonBounds = retryButton.getLocalBounds();
	float xRetry = (1920 / 2.f) - (retryButtonBounds.width / 2.f) - retryButtonBounds.left;
	retryButton.setPosition(xRetry, 500);
	retryButton.setFillColor(Color::White);

	mainMenuButton.setFont(fontOver);
	mainMenuButton.setString("Retour au menu");
	mainMenuButton.setCharacterSize(30);

	FloatRect mainMenuButtonBounds = mainMenuButton.getLocalBounds();
	float xMain = (1920 / 2.f) - (mainMenuButtonBounds.width / 2.f) - mainMenuButtonBounds.left;
	mainMenuButton.setPosition(xMain, 600);
	mainMenuButton.setFillColor(Color::White);
}

GameOver::GameOver()
{
	initFont();
	initButton();
}

int GameOver::handleInput(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (retryButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
		}
	}
	return 0;
}

void GameOver::handleMouseHover(const RenderWindow& window)
{
	Vector2i mousePos = Mouse::getPosition(window);

	if (retryButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		retryButton.setFillColor(Color(218, 218, 218));
	}
	else {
		retryButton.setFillColor(Color::White);
	}
	if (mainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		mainMenuButton.setFillColor(Color(218, 218, 218));
	}
	else {
		mainMenuButton.setFillColor(Color::White);
	}
}

void GameOver::render(RenderWindow& window)
{
	window.draw(gameOverText);
	window.draw(retryButton);
	window.draw(mainMenuButton);
}

bool GameOver::isCooldownActive()
{
	return mouseCooldownClock.getElapsedTime() < mouseCooldown;
}

void GameOver::resetCooldown()
{
	mouseCooldownClock.restart();
}
