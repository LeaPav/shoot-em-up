#include "Menu.h"

Menu::Menu() : indexButtonSelected(0)
{
	initBackground();
	initFont();
	initButton();
	initOptionsButton();
	initCommandsButton();
}

int Menu::initFont()
{
	if (!fontMainMenu.loadFromFile("assets/font/test.ttf")) {
		return -1;
	}

	if (!fontPauseMenu.loadFromFile("assets/font/fontpause.ttf")) {
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

	playButton.setFont(this->fontMainMenu);
	playButton.setString("JOUER");
	playButton.setCharacterSize(50);
	playButton.setPosition(870.f, 300.f);

	optionsButton.setFont(this->fontMainMenu);
	optionsButton.setString("OPTIONS");
	optionsButton.setCharacterSize(50);
	optionsButton.setFillColor(Color::White);
	optionsButton.setPosition(860.f, 455.f);

	editorButton.setFont(this->fontMainMenu);
	editorButton.setString("EDITEUR DE NIVEAU");
	editorButton.setCharacterSize(50);
	editorButton.setFillColor(Color::White);
	editorButton.setPosition(765.f, 600.f);

	quitButton.setFont(this->fontMainMenu);
	quitButton.setString("QUITTER");
	quitButton.setCharacterSize(50);
	quitButton.setFillColor(Color::White);
	quitButton.setPosition(870.f, 755.f);
}
void Menu::initOptionsButton()
{
	commandsButtonRect.setSize(Vector2f(510.f, 95.f));
	commandsButtonRect.setFillColor(Color(165, 191, 208));
	commandsButtonRect.setPosition(705.f, 290.f);

	settingsButtonRect.setSize(Vector2f(510.f, 95.f));
	settingsButtonRect.setFillColor(Color(165, 191, 208));
	settingsButtonRect.setPosition(705.f, 442.f);

	difficultyButtonRect.setSize(Vector2f(510.f, 95.f));
	difficultyButtonRect.setFillColor(Color(165, 191, 208));
	difficultyButtonRect.setPosition(705.f, 585.f);

	returnButtonRect.setSize(Vector2f(350.f, 75.f));
	returnButtonRect.setFillColor(Color(165, 191, 208));
	returnButtonRect.setPosition(1550.f, 980.f);

	commandsButton.setFont(this->fontMainMenu);
	commandsButton.setString("COMMANDES");
	commandsButton.setCharacterSize(50);
	commandsButton.setPosition(870.f, 300.f);

	settingsButton.setFont(this->fontMainMenu);
	settingsButton.setString("PARAMÈTRES");
	settingsButton.setCharacterSize(50);
	settingsButton.setPosition(870.f, 455.f);

	difficultyButton.setFont(this->fontMainMenu);
	difficultyButton.setString("DIFFICULTÉ");
	difficultyButton.setCharacterSize(50);
	difficultyButton.setPosition(870.f, 600.f);

	returnButton.setFont(this->fontMainMenu);
	returnButton.setString("RETOUR");
	returnButton.setCharacterSize(50);
	returnButton.setPosition(1650.f, 985.f);

	resumeButton.setFont(fontPauseMenu);
	resumeButton.setPosition(870, 400);
	resumeButton.setCharacterSize(28);
	resumeButton.setString("Reprendre");

	settingsPauseButton.setFont(fontPauseMenu);
	settingsPauseButton.setPosition(870, 500);
	settingsPauseButton.setCharacterSize(28);
	settingsPauseButton.setString("Paramètres");

	returnToMainMenuButton.setFont(fontPauseMenu);
	returnToMainMenuButton.setPosition(870, 600);
	returnToMainMenuButton.setCharacterSize(28);
	returnToMainMenuButton.setString("Retour au menu");

}
void Menu::initCommandsButton()
{
	returnButtonRect.setSize(Vector2f(350.f, 75.f));
	returnButtonRect.setFillColor(Color(165, 191, 208));
	returnButtonRect.setPosition(1550.f, 980.f);

	returnButton.setFont(this->fontMainMenu);
	returnButton.setString("RETOUR");
	returnButton.setCharacterSize(50);
	returnButton.setPosition(1650.f, 985.f);
}
int Menu::handleInputMainMenu(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);

			if (playButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (optionsButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (editorButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 3;
			}
			if (quitButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 4;
			}
		}
		

	}
	return 0;
}
int Menu::handleInputMenuOptions(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (commandsButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (settingsButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (difficultyButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				return 3;
			}
			if (returnButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 4;
			}
		}
	}
	return 0;
}
int Menu::handleInputPauseMenu(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (settingsPauseButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (returnToMainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 3;
			}
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
	window.draw(commandsButtonRect);
	window.draw(settingsButtonRect);
	window.draw(difficultyButtonRect);
	window.draw(returnButtonRect);
	
	window.draw(commandsButton);
	window.draw(settingsButton);
	window.draw(difficultyButton);
	window.draw(this->returnButton);
}

void Menu::renderEditor(RenderWindow& window)
{
	window.draw(optionsBackground);
}

void Menu::renderCommands(RenderWindow& window)
{
	window.draw(optionsBackground);
	Text text;
	text.setFont(fontMainMenu);
	text.setCharacterSize(40);
	text.setFillColor(Color::White);
	text.setPosition(750, 200);
	text.setString(" Z : Aller vers le haut. \n\n Q : Aller vers la gauche. \n\n S : Aller vers le bas. \n\n D : Aller vers la droite. \n\n F : Tirer. \n\n Echap : Quitter");
	window.draw(text);

	window.draw(returnButtonRect);
	window.draw(returnButton);
}

void Menu::renderPauseMenu(RenderWindow& window)
{
	window.draw(resumeButton);
	window.draw(settingsPauseButton);
	window.draw(returnToMainMenuButton);
}

void Menu::renderSettingsPauseMenu(RenderWindow& window)
{

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

	if (commandsButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		commandsButtonRect.setFillColor(Color(222, 231, 237));
		commandsButton.setFillColor(Color(165, 191, 208));
	}
	else {
		commandsButtonRect.setFillColor(Color(165, 191, 208));
		commandsButton.setFillColor(Color::White);
	}
	if (settingsButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		settingsButtonRect.setFillColor(Color(222, 231, 237));
		settingsButton.setFillColor(Color(165, 191, 208));
	}
	else {
		settingsButtonRect.setFillColor(Color(165, 191, 208));
		settingsButton.setFillColor(Color::White);
	}
	if (difficultyButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		difficultyButtonRect.setFillColor(Color(222, 231, 237));
		difficultyButton.setFillColor(Color(165, 191, 208));
	}
	else {
		difficultyButtonRect.setFillColor(Color(165, 191, 208));
		difficultyButton.setFillColor(Color::White);
	}
	if (returnButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		returnButtonRect.setFillColor(Color(222, 231, 237));
		returnButton.setFillColor(Color(165, 191, 208));
	}
	else {
		returnButtonRect.setFillColor(Color(165, 191, 208));
		returnButton.setFillColor(Color::White);
	}
	if (resumeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		resumeButton.setFillColor(Color(218, 218, 218));
	}
	else {
		resumeButton.setFillColor(Color::White);
	}
	if (settingsPauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		settingsPauseButton.setFillColor(Color(218, 218, 218));
	}
	else {
		settingsPauseButton.setFillColor(Color::White);
	}
	if (returnToMainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		returnToMainMenuButton.setFillColor(Color(218, 218, 218));
	}
	else {
		returnToMainMenuButton.setFillColor(Color::White);
	}
}

bool Menu::isCooldownActive()
{
	return mouseCooldownClock.getElapsedTime() < mouseCooldown;
}

void Menu::resetCooldown()
{
	mouseCooldownClock.restart();
}

