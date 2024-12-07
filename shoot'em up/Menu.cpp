#include "Menu.h"

Menu::Menu() : indexButtonSelected(0)
{
	initBackground();
	initFont();
	initButton();
}

int Menu::initFont()
{
	if (!font.loadFromFile("assets/test.ttf")) {
		return -1;
	}
}

int Menu::initBackground()
{
	if (!backgroundTexture.loadFromFile("assets/menu/STARWATERmenu.png")) {
		return -1;
	}
	background.setTexture(backgroundTexture);
}

void Menu::initButton()
{
	/*Text button;
	button.setFont(this->font);
	button.setString();
	button.setCharacterSize(30);
	button.setFillColor(Color::White);
	button.setPosition(100.f, 100.f);
	buttons.push_back(button);*/

	playButton.setFont(this->font);
	playButton.setString("JOUER");
	playButton.setCharacterSize(50);
	playButton.setFillColor(Color::White);
	playButton.setPosition(920.f, 320.f);

	optionsButton.setFont(this->font);
	optionsButton.setString("OPTIONS");
	optionsButton.setCharacterSize(30);
	optionsButton.setFillColor(Color::White);
	optionsButton.setPosition(960.f, 495.f);

	editorButton.setFont(this->font);
	editorButton.setString("EDITEUR DE NIVEAU");
	editorButton.setCharacterSize(30);
	editorButton.setFillColor(Color::White);
	editorButton.setPosition(960.f, 640.f);

	quitButton.setFont(this->font);
	quitButton.setString("QUITTER");
	quitButton.setCharacterSize(30);
	quitButton.setFillColor(Color::White);
	quitButton.setPosition(960.f, 790.f);
}
int Menu::handleInput(RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i mousePos = Mouse::getPosition(window);
		if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 1;
		}
		else if (optionsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 2;
		}
		else if (editorButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 3;
		}
		else if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 4;
		}
	}
	return 0;
}
void Menu::render(RenderWindow& window)
{
	window.draw(background);
	window.draw(playButton);
	window.draw(optionsButton);
	window.draw(editorButton);
	window.draw(quitButton);
}

void Menu::renderOptions(RenderWindow& window)
{
}

void Menu::setBackground(const string& backgroundImage)
{
}

int Menu::getSelectedIndex()
{
	return indexButtonSelected;
}
