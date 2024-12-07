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
	if (!backgroundTexture.loadFromFile("assets/menu/menuStarWater.png")) {
		return -1;
	}
	if (!optionsTexture.loadFromFile("assets/menu/sky.png")) {
		return -1;
	}
	background.setTexture(backgroundTexture);
	optionsBackground.setTexture(optionsTexture);
}

void Menu::initButton()
{
	
	playButtonRect.setSize(Vector2f(510.f, 95.f));
	playButtonRect.setFillColor(Color(165, 191, 208));
	playButtonRect.setPosition(705.f ,290.f);

	optionsButtonRect.setSize(Vector2f(510.f, 95.f));
	optionsButtonRect.setFillColor(Color(165, 191, 208));
	optionsButtonRect.setPosition(705.f, 442.f);

	editorButtonRect.setSize(Vector2f(510.f, 95.f));
	editorButtonRect.setFillColor(Color(165, 191, 208));
	editorButtonRect.setPosition(705.f, 585.f);

	quitButtonRect.setSize(Vector2f(510.f, 95.f));
	quitButtonRect.setFillColor(Color(165, 191, 208));
	quitButtonRect.setPosition(705.f, 735.f);

	playButton.setFont(this->font);
	playButton.setString("JOUER");
	playButton.setCharacterSize(50);
	playButton.setPosition(870.f, 300.f);

	optionsButton.setFont(this->font);
	optionsButton.setString("OPTIONS");
	optionsButton.setCharacterSize(50);
	optionsButton.setFillColor(Color::White);
	optionsButton.setPosition(860.f, 455.f);

	editorButton.setFont(this->font);
	editorButton.setString("EDITEUR DE NIVEAU");
	editorButton.setCharacterSize(50);
	editorButton.setFillColor(Color::White);
	editorButton.setPosition(765.f, 600.f);

	quitButton.setFont(this->font);
	quitButton.setString("QUITTER");
	quitButton.setCharacterSize(50);
	quitButton.setFillColor(Color::White);
	quitButton.setPosition(870.f, 755.f);
}
int Menu::handleInput(RenderWindow& window)
{
	if (Mouse::isButtonPressed(Mouse::Left)) {
		Vector2i mousePos = Mouse::getPosition(window);
		if (playButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 1;
		}
		else if (optionsButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 2;
		}
		else if (editorButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 3;
		}
		else if (quitButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
			return 4;
		}
	}
	return 0;
}
void Menu::render(RenderWindow& window)
{

	window.draw(background);

	window.draw(playButtonRect);
	window.draw(optionsButtonRect);
	window.draw(editorButtonRect);
	window.draw(quitButtonRect);

	window.draw(playButton);
	window.draw(optionsButton);
	window.draw(editorButton);
	window.draw(quitButton);
}

void Menu::renderOptions(RenderWindow& window)
{
	window.draw(optionsBackground);
}

void Menu::setBackground(const string& backgroundImage)
{
}

void Menu::handleMouseHover(const RenderWindow& window)
{
	Vector2i mousePos = Mouse::getPosition(window);


	if (playButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		playButtonRect.setFillColor(Color(222, 231, 237));
		playButton.setFillColor(Color(165, 191, 208));
	}
	else {
		playButtonRect.setFillColor(Color(165, 191, 208));
		playButton.setFillColor(Color::White);
	}
	if (optionsButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		optionsButtonRect.setFillColor(Color(222, 231, 237));
		optionsButton.setFillColor(Color(165, 191, 208));
	}
	else {
		optionsButtonRect.setFillColor(Color(165, 191, 208));
		optionsButton.setFillColor(Color::White);
	}
	if (editorButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		editorButtonRect.setFillColor(Color(222, 231, 237));
		editorButton.setFillColor(Color(165, 191, 208));
	}
	else {
		editorButtonRect.setFillColor(Color(165, 191, 208));
		editorButton.setFillColor(Color::White);
	}
	if (quitButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		quitButtonRect.setFillColor(Color(222, 231, 237));
		quitButton.setFillColor(Color(165, 191, 208));
	}
	else {
		quitButtonRect.setFillColor(Color(165, 191, 208));
		quitButton.setFillColor(Color::White);
	}
}

int Menu::getSelectedIndex()
{
	return indexButtonSelected;
}
