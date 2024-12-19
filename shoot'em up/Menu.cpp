#include "Menu.h"

Menu::Menu() : indexButtonSelected(0)
{
	initBackground();
	initLevel1();
	initLevel2();
	initSpritePlayer();
	initSpriteEnnemies();
	initSpriteBoss();
	initTextureButton();
	initEditorButton();
	initFont();
	initButton();
	initOptionsButton();
	initCommandsButton();
	initDifficultyButton();
	initLevelButton();
}

/////////////////////////////////////////maj du Game Over/////////////////////////////////////

int Menu::initFont() //chargement font
{
	if (!fontMainMenu.loadFromFile("assets/font/menu.ttf")) {
		return -1;
	}

	if (!fontPauseMenu.loadFromFile("assets/font/fontpause.ttf")) {
		return -1;
	}
}

int Menu::initBackground() //chargement image
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

void Menu::initSpritePlayer()
{
	if (!player.loadFromFile("assets/vaisseau_5.png")) {
		cout << "Erreur";
	}
	spritePlayer.setTexture(player);
	spritePlayer.setPosition(Vector2f(100.f, 70.f));
}

void Menu::initSpriteEnnemies()
{
	if (!ennemy1.loadFromFile("assets/Ennemies/canon.png")) {
		cout << "Erreur";
	}

	if (!ennemy2.loadFromFile("assets/Ennemies/robot passif.png")) {
		cout << "Erreur";
	}
	spriteEnnemy1.setTexture(ennemy1);
	spriteEnnemy1.setPosition(Vector2f(120.f, 350.f));

	spriteEnnemy2.setTexture(ennemy2);
	spriteEnnemy2.setPosition(Vector2f(120.f, 480.f));

	ennemy1Groupe1.setTexture(ennemy1);
	ennemy1Groupe1.setPosition(Vector2f(1200.f, 325.f));

	ennemy2Groupe1.setTexture(ennemy1);
	ennemy2Groupe1.setPosition(Vector2f(1275.f, 250.f));

	ennemy3Groupe1.setTexture(ennemy1);
	ennemy3Groupe1.setPosition(Vector2f(1275.f, 400.f));

	ennemy1Groupe2.setTexture(ennemy2);
	ennemy1Groupe2.setPosition(Vector2f(1750.f, 10.f));

	ennemy2Groupe2.setTexture(ennemy2);
	ennemy2Groupe2.setPosition(Vector2f(1750.f, 85.f));

	ennemy3Groupe2.setTexture(ennemy2);
	ennemy3Groupe2.setPosition(Vector2f(1750.f, 160.f));

	ennemy4Groupe2.setTexture(ennemy2);
	ennemy4Groupe2.setPosition(Vector2f(1750.f, 450.f));

	ennemy5Groupe2.setTexture(ennemy2);
	ennemy5Groupe2.setPosition(Vector2f(1750.f, 525.f));

	ennemy6Groupe2.setTexture(ennemy2);
	ennemy6Groupe2.setPosition(Vector2f(1750.f, 600.f));

	ennemy7Groupe2.setTexture(ennemy2);
	ennemy7Groupe2.setPosition(Vector2f(1750.f, 675.f));

	ennemy8Groupe2.setTexture(ennemy2);
	ennemy8Groupe2.setPosition(Vector2f(1750.f, 750.f));

	ennemy4Groupe1.setTexture(ennemy1);
	ennemy4Groupe1.setPosition(Vector2f(1200.f, 800.f));

	ennemy5Groupe1.setTexture(ennemy1);
	ennemy5Groupe1.setPosition(Vector2f(1275.f, 715.f));

	ennemy6Groupe1.setTexture(ennemy1);
	ennemy6Groupe1.setPosition(Vector2f(1275.f, 875.f));

	ennemy7Groupe1.setTexture(ennemy1);
	ennemy7Groupe1.setPosition(Vector2f(1350.f, 650.f));

	ennemy8Groupe1.setTexture(ennemy1);
	ennemy8Groupe1.setPosition(Vector2f(1350.f, 950.f));

}

void Menu::initSpriteBoss()
{
	if (!boss.loadFromFile("assets/boss/Boss_sans_shield.png")) {
		cout << "Erreur";
	}
	spriteBoss.setTexture(boss);
	spriteBoss.setPosition(Vector2f(100.f, 700.f));
}

void Menu::initTextureButton()
{
	if (!playerButtonRight.loadFromFile("assets/menu/fleche_droite.png")) {
		cout << "Erreur";
	}

	if (!playerButtonLeft.loadFromFile("assets/menu/fleche_gauche.png")) {
		cout << "Erreur";
	}

}

int Menu::initLevel1()
{
	if (!textureLevel1.loadFromFile("assets/choix level/niv_1_500.png")); {
		return -1;
	}

}

int Menu::initLevel2()
{
	
	if (!textureLevel2.loadFromFile("assets/choix level/500_250_niveau_2.jpg")); {
		return -1;
	}
	
}



//////////////////////////////////////////////////bouton//////////////////////////////////////////

void Menu::initButton()
{
	
	playButtonRect.setSize(Vector2f(510.f, 95.f));
	playButtonRect.setFillColor(Color(165, 191, 208));
	playButtonRect.setPosition(705.f ,290.f);

	playButton.setFont(this->fontMainMenu);
	playButton.setString("Jouer");
	playButton.setCharacterSize(40);
	playButton.setPosition(880.f, 310.f);


	optionsButtonRect.setSize(Vector2f(510.f, 95.f));
	optionsButtonRect.setFillColor(Color(165, 191, 208));
	optionsButtonRect.setPosition(705.f, 442.f);

	optionsButton.setFont(this->fontMainMenu);
	optionsButton.setString("Options");
	optionsButton.setCharacterSize(40);
	optionsButton.setFillColor(Color::White);
	optionsButton.setPosition(870.f, 465.f);


	editorButtonRect.setSize(Vector2f(510.f, 95.f));
	editorButtonRect.setFillColor(Color(165, 191, 208));
	editorButtonRect.setPosition(705.f, 585.f);

	editorButton.setFont(this->fontMainMenu);
	editorButton.setString("Editeur de niveau");
	editorButton.setCharacterSize(40);
	editorButton.setFillColor(Color::White);
	editorButton.setPosition(735.f, 605.f);


	quitButtonRect.setSize(Vector2f(510.f, 95.f));
	quitButtonRect.setFillColor(Color(165, 191, 208));
	quitButtonRect.setPosition(705.f, 735.f);

	quitButton.setFont(this->fontMainMenu);
	quitButton.setString("Quitter");
	quitButton.setCharacterSize(40);
	quitButton.setFillColor(Color::White);
	quitButton.setPosition(870.f, 755.f);
}
void Menu::initOptionsButton()
{
	commandsButtonRect.setSize(Vector2f(510.f, 95.f));
	commandsButtonRect.setFillColor(Color(165, 191, 208));
	commandsButtonRect.setPosition(705.f, 290.f);

	commandsButton.setFont(this->fontMainMenu);
	commandsButton.setString("Commandes");
	commandsButton.setCharacterSize(40);
	commandsButton.setPosition(830.f, 305.f);


	settingsButtonRect.setSize(Vector2f(510.f, 95.f));
	settingsButtonRect.setFillColor(Color(165, 191, 208));
	settingsButtonRect.setPosition(705.f, 442.f);

	settingsButton.setFont(this->fontMainMenu);
	settingsButton.setString("Son");
	settingsButton.setCharacterSize(40);
	settingsButton.setPosition(900.f, 460.f);


	difficultyButtonRect.setSize(Vector2f(510.f, 95.f));
	difficultyButtonRect.setFillColor(Color(165, 191, 208));
	difficultyButtonRect.setPosition(705.f, 585.f);

	difficultyButton.setFont(this->fontMainMenu);
	difficultyButton.setString("Difficulté");
	difficultyButton.setCharacterSize(40);
	difficultyButton.setPosition(840.f, 605.f);


	returnButtonRect.setSize(Vector2f(350.f, 75.f));
	returnButtonRect.setFillColor(Color(165, 191, 208));
	returnButtonRect.setPosition(1550.f, 980.f);

	returnButton.setFont(this->fontMainMenu);
	returnButton.setString("Retour");
	returnButton.setCharacterSize(40);
	returnButton.setPosition(1650.f, 990.f);

	/////////////////////////menu pause////////////////////////////

	resumeButton.setFont(fontPauseMenu);
	resumeButton.setCharacterSize(28);
	resumeButton.setString("Reprendre");

	FloatRect resumeButtonBounds = resumeButton.getLocalBounds();
	float xResume = (1920 / 2.f) - (resumeButtonBounds.width / 2.f) - resumeButtonBounds.left;
	resumeButton.setPosition(xResume, 400);
	

	settingsPauseButton.setFont(fontPauseMenu);
	settingsPauseButton.setCharacterSize(28);
	settingsPauseButton.setString("Paramètres");

	FloatRect settingsButtonBounds = settingsPauseButton.getLocalBounds();
	float xSettings = (1920 / 2.f) - (settingsButtonBounds.width / 2.f) - settingsButtonBounds.left;
	settingsPauseButton.setPosition(xSettings, 500);

	returnToMainMenuButton.setFont(fontPauseMenu);
	returnToMainMenuButton.setCharacterSize(28);
	returnToMainMenuButton.setString("Retour au menu");

	FloatRect returnToMainMenuButtonBounds = returnToMainMenuButton.getLocalBounds();
	float xReturn = (1920 / 2.f) - (returnToMainMenuButtonBounds.width / 2.f) - returnToMainMenuButtonBounds.left;
	returnToMainMenuButton.setPosition(xReturn, 600);

	pause.setFont(fontPauseMenu);
	pause.setCharacterSize(80);
	pause.setString("PAUSE");
	pause.setFillColor(Color(255, 235, 108));

	FloatRect pauseBounds = pause.getLocalBounds();
	float xpause = (1920 / 2.f) - (pauseBounds.width / 2.f) - pauseBounds.left;
	pause.setPosition(xpause, 100);

}

void Menu::initEditorButton()
{
	lifePlayer.setFont(this->fontMainMenu);
	lifePlayer.setCharacterSize(22);
	lifePlayer.setString("Vie");
	lifePlayer.setPosition(300.f, 55.f);

	speedPlayer.setFont(this->fontMainMenu);
	speedPlayer.setCharacterSize(22);
	speedPlayer.setString("Vitesse");
	speedPlayer.setPosition(280.f, 145.f);

	lifeEnnemy1.setFont(this->fontMainMenu);
	lifeEnnemy1.setCharacterSize(22);
	lifeEnnemy1.setString("Vie");
	lifeEnnemy1.setPosition(300.f, 370.f);

	speedEnnemy.setFont(this->fontMainMenu);
	speedEnnemy.setCharacterSize(22);
	speedEnnemy.setString("Vitesse");
	speedEnnemy.setPosition(280.f, 430.f);

	lifeEnnemy2.setFont(this->fontMainMenu);
	lifeEnnemy2.setCharacterSize(22);
	lifeEnnemy2.setString("Vie");
	lifeEnnemy2.setPosition(300.f, 500.f);

	playerHealthPlus1.setSize(Vector2f(25.f, 25.f));
	playerHealthPlus1.setPosition(700.f, 60.f);
	playerHealthPlus1.setTexture(&playerButtonRight);

	playerHealthPlus2.setSize(Vector2f(25.f, 25.f));
	playerHealthPlus2.setPosition(700.f, 150.f);
	playerHealthPlus2.setTexture(&playerButtonRight);

	playerHealthMin1.setSize(Vector2f(25.f, 25.f));
	playerHealthMin1.setPosition(400.f, 60.f);
	playerHealthMin1.setTexture(&playerButtonLeft);

	playerHealthMin2.setSize(Vector2f(25.f, 25.f));
	playerHealthMin2.setPosition(400.f, 150.f);
	playerHealthMin2.setTexture(&playerButtonLeft);

	ennemyHealthPlus1.setSize(Vector2f(25.f, 25.f));
	ennemyHealthPlus1.setPosition(700.f, 365.f);
	ennemyHealthPlus1.setTexture(&playerButtonRight);

	ennemyHealthPlus2.setSize(Vector2f(25.f, 25.f));
	ennemyHealthPlus2.setPosition(700.f, 500.f);
	ennemyHealthPlus2.setTexture(&playerButtonRight);

	ennemyHealthPlus3.setSize(Vector2f(25.f, 25.f));
	ennemyHealthPlus3.setPosition(700.f, 430.f);
	ennemyHealthPlus3.setTexture(&playerButtonRight);

	ennemyHealthMin1.setSize(Vector2f(25.f, 25.f));
	ennemyHealthMin1.setPosition(400.f, 365.f);
	ennemyHealthMin1.setTexture(&playerButtonLeft);

	ennemyHealthMin2.setSize(Vector2f(25.f, 25.f));
	ennemyHealthMin2.setPosition(400.f, 500.f);
	ennemyHealthMin2.setTexture(&playerButtonLeft);

	ennemyHealthMin3.setSize(Vector2f(25.f, 25.f));
	ennemyHealthMin3.setPosition(400.f, 430.f);
	ennemyHealthMin3.setTexture(&playerButtonLeft);
}


void Menu::initCommandsButton() //bouton retour 
{
	returnButtonRect.setSize(Vector2f(350.f, 75.f));
	returnButtonRect.setFillColor(Color(165, 191, 208));
	returnButtonRect.setPosition(1550.f, 980.f);

}

void Menu::initDifficultyButton()
{
	easyButtonRect.setSize(Vector2f(510.f, 95.f));
	easyButtonRect.setFillColor(Color(165, 191, 208));
	easyButtonRect.setPosition(705.f, 290.f);

	easyButton.setFont(this->fontMainMenu);
	easyButton.setString("Débutant");
	easyButton.setCharacterSize(40);
	easyButton.setPosition(830.f, 305.f);

	normalButtonRect.setSize(Vector2f(510.f, 95.f));
	normalButtonRect.setFillColor(Color(165, 191, 208));
	normalButtonRect.setPosition(705.f, 442.f);

	hardButton.setFont(this->fontMainMenu);
	hardButton.setString("Intermediaire");
	hardButton.setCharacterSize(40);
	hardButton.setPosition(820.f, 460.f);


	hardCoreRect.setSize(Vector2f(510.f, 95.f));
	hardCoreRect.setFillColor(Color(165, 191, 208));
	hardCoreRect.setPosition(705.f, 585.f);

	hardCoreButton.setFont(this->fontMainMenu);
	hardCoreButton.setString("Joueur Pro");
	hardCoreButton.setCharacterSize(40);
	hardCoreButton.setPosition(840.f, 605.f);
}

void Menu::initLevelButton()
{
	dlcLevel2.setFont(this->fontMainMenu);
	dlcLevel2.setString("1,99$");
	dlcLevel2.setCharacterSize(35);
	dlcLevel2.setPosition(Vector2f(890.f, 500.f));
	
	level1Rect.setSize(Vector2f(500.f, 250.f));
	level1Rect.setPosition(Vector2f(50.f, 400.f));
	level1Rect.setTexture(&textureLevel1);
	level1Rect.setOutlineThickness(5);
	level1Rect.setOutlineColor(Color::White);

	level1.setFont(this->fontMainMenu);
	level1.setString("Niveau 1");
	level1.setCharacterSize(35);
	level1.setPosition(200.f, 675.f);

	level2Rect.setSize(Vector2f(500.f, 250.f));
	level2Rect.setPosition(Vector2f(700.f, 400.f));
	level2Rect.setTexture(&textureLevel2);
	level2Rect.setOutlineThickness(5);
	level2Rect.setOutlineColor(Color::White);

	level2.setFont(this->fontMainMenu);
	level2.setString("Niveau 2");
	level2.setCharacterSize(35);
	level2.setPosition(850.f, 675.f);

	level3Rect.setSize(Vector2f(500.f, 250.f));
	level3Rect.setPosition(Vector2f(1350.f, 400.f));
	level3Rect.setFillColor(Color::Black);
	level3Rect.setOutlineThickness(5);
	level3Rect.setOutlineColor(Color::White);

	level3.setFont(this->fontMainMenu);
	level3.setString("Prochainement");
	level3.setCharacterSize(35);
	level3.setPosition(1450.f, 675.f);
}

///////////////////////////////////////clique souris//////////////////////////////////////////

int Menu::handleInputMainMenu(RenderWindow& window, const Event& event) //changement des etat du jeu 
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

bool Menu::isCooldownActive() // cooldown pour les clique bouton
{
	return mouseCooldownClock.getElapsedTime() < mouseCooldown;
}

void Menu::resetCooldown() //reset du clique 
{
	mouseCooldownClock.restart();
}

int Menu::handleInputMenuOptions(RenderWindow& window, const Event& event) //changement des etat du jeu dans le menu option
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
				resetCooldown();
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

int Menu::handleInputDifficulty(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (easyButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (normalButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (hardCoreRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
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

int Menu::handleInputEditor(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (playerHealthPlus1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (playerHealthMin1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (playerHealthPlus2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 3;
			}
			if (playerHealthMin2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 4;
			}
			if (ennemyHealthPlus1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 5;
			}
			if (ennemyHealthMin1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 6;
			}
			if (ennemyHealthPlus2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 7;
			}
			if (ennemyHealthMin2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 8;
			}
			if (ennemyHealthPlus3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 9;
			}
			if (ennemyHealthMin3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 10;
			}
			if (returnButtonRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 11;
			}
		}
	}
	return 0;
}

int Menu::handleInputLevel(RenderWindow& window, const Event& event)
{
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
		if (!isCooldownActive()) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (level1Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 1;
			}
			if (level2Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
				return 2;
			}
			if (level3Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
				resetCooldown();
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

int Menu::handleInputPauseMenu(RenderWindow& window, const Event& event) //changement des etat du jeu dans le menu pause
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

///////////////////////////////////////////////affichage//////////////////////////////////////////////

void Menu::render(RenderWindow& window) //menu principale
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

void Menu::renderOptions(RenderWindow& window) // menu option 
{
	window.draw(optionsBackground);
	window.draw(commandsButtonRect);
	window.draw(settingsButtonRect);
	window.draw(difficultyButtonRect);
	window.draw(returnButtonRect);
	
	window.draw(commandsButton);
	window.draw(settingsButton);
	window.draw(difficultyButton);
	window.draw(returnButton);
}

void Menu::renderEditor(RenderWindow& window) // menu éditeur
{
	window.draw(optionsBackground);
	window.draw(spritePlayer);
	window.draw(spriteEnnemy1);
	window.draw(spriteEnnemy2);
	window.draw(ennemy1Groupe2);
	window.draw(ennemy2Groupe2);
	window.draw(ennemy3Groupe2);
	window.draw(ennemy4Groupe2);
	window.draw(ennemy5Groupe2);
	window.draw(ennemy6Groupe2);
	window.draw(ennemy7Groupe2);
	window.draw(ennemy8Groupe2);

	window.draw(ennemy1Groupe1);
	window.draw(ennemy2Groupe1);
	window.draw(ennemy3Groupe1);
	window.draw(ennemy4Groupe1);
	window.draw(ennemy5Groupe1);
	window.draw(ennemy6Groupe1);
	window.draw(ennemy7Groupe1);
	window.draw(ennemy8Groupe1);
	
	window.draw(spriteBoss);
	window.draw(returnButtonRect);
	window.draw(returnButton);

	window.draw(playerHealthPlus1);
	window.draw(playerHealthMin1);

	window.draw(playerHealthPlus2);
	window.draw(playerHealthMin2);

	window.draw(ennemyHealthPlus1);
	window.draw(ennemyHealthMin1);
	window.draw(ennemyHealthPlus2);
	window.draw(ennemyHealthMin2);
	window.draw(ennemyHealthPlus3);
	window.draw(ennemyHealthMin3);

	//affichage du text
	window.draw(lifePlayer);
	window.draw(speedPlayer);
	window.draw(speedEnnemy);
	window.draw(lifeEnnemy1);
	window.draw(lifeEnnemy2);
}

void Menu::renderCommands(RenderWindow& window) // menu commande
{
	window.draw(optionsBackground);
	Text text;
	text.setFont(fontMainMenu);
	text.setCharacterSize(40);
	text.setFillColor(Color::White);
	text.setPosition(700, 200);
	text.setString(" Z : Aller vers le haut \n\n Q : Aller vers la gauche \n\n S : Aller vers le bas \n\n D : Aller vers la droite \n\n Espace : Tirer \n\n Echap : Quitter");
	window.draw(text);

	window.draw(returnButtonRect);
	window.draw(returnButton);
}

void Menu::renderDifficulty(RenderWindow& window)
{
	window.draw(optionsBackground);
	window.draw(easyButtonRect);
	window.draw(normalButtonRect);
	window.draw(hardCoreRect);
	window.draw(returnButtonRect);

	window.draw(easyButton);
	window.draw(hardButton);
	window.draw(hardCoreButton);
	window.draw(returnButton);

}

void Menu::renderPauseMenu(RenderWindow& window) //menu pause
{
	window.draw(pause);
	window.draw(resumeButton);
	window.draw(settingsPauseButton);
	window.draw(returnToMainMenuButton);
}

void Menu::renderLevel(RenderWindow& window)
{
	window.draw(optionsBackground);
	window.draw(level1Rect);
	window.draw(level1);
	
	window.draw(level2Rect);
	window.draw(level2);
	window.draw(dlcLevel2);

	window.draw(level3Rect);
	window.draw(level3);
	window.draw(returnButtonRect);
	window.draw(returnButton);

}

void Menu::renderSettingsPauseMenu(RenderWindow& window) //menu paramètre menu pause
{

}


void Menu::setBackground(const string& backgroundImage) // changer de fond si besoin
{
}

/////////////////////////////////////////surbrillance///////////////////////////////////////////////////////////

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
	if (easyButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		easyButtonRect.setFillColor(Color(222, 231, 237));
		easyButton.setFillColor(Color(165, 191, 208));
	}
	else {
		easyButtonRect.setFillColor(Color(165, 191, 208));
		easyButton.setFillColor(Color::White);
	}
	if (normalButtonRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		normalButtonRect.setFillColor(Color(222, 231, 237));
		hardButton.setFillColor(Color(165, 191, 208));
	}
	else {
		normalButtonRect.setFillColor(Color(165, 191, 208));
		hardButton.setFillColor(Color::White);
	}
	if (level1Rect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		level1Rect.setFillColor(Color(179, 179, 179));
	}
	else {
		level1Rect.setFillColor(Color::White);
	}
	if (level2Rect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		level2Rect.setFillColor(Color(179, 179, 179));
	}
	else {
		level2Rect.setFillColor(Color(99, 99, 99));
	}
	if (level3Rect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		level3Rect.setFillColor(Color(51, 51, 51));
	}
	else {
		level3Rect.setFillColor(Color::Black);
	}
	if (hardCoreRect.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		hardCoreRect.setFillColor(Color(222, 231, 237));
		hardCoreButton.setFillColor(Color(165, 191, 208));
	}
	else {
		hardCoreRect.setFillColor(Color(165, 191, 208));
		hardCoreButton.setFillColor(Color::White);
	}
	if (resumeButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		resumeButton.setFillColor(Color(251, 239, 165));
	}
	else {
		resumeButton.setFillColor(Color::White);
	}
	if (settingsPauseButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		settingsPauseButton.setFillColor(Color(251, 239, 165));
	}
	else {
		settingsPauseButton.setFillColor(Color::White);
	}
	if (returnToMainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		returnToMainMenuButton.setFillColor(Color(251, 239, 165));
	}
	else {
		returnToMainMenuButton.setFillColor(Color::White);
	}
	if (playerHealthMin1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		playerHealthMin1.setFillColor(Color(189, 189, 189));
	}
	else {
		playerHealthMin1.setFillColor(Color::White);
	}
	if (playerHealthMin2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		playerHealthMin2.setFillColor(Color(189, 189, 189));
	}
	else {
		playerHealthMin2.setFillColor(Color::White);
	}
	if (playerHealthPlus1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		playerHealthPlus1.setFillColor(Color(189, 189, 189));
	}
	else {
		playerHealthPlus1.setFillColor(Color::White);
	}
	if (playerHealthPlus2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		playerHealthPlus2.setFillColor(Color(189, 189, 189));
	}
	else {
		playerHealthPlus2.setFillColor(Color::White);
	}
	if (ennemyHealthPlus1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthPlus1.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthPlus1.setFillColor(Color::White);
	}
	if (ennemyHealthPlus2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthPlus2.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthPlus2.setFillColor(Color::White);
	}
	if (ennemyHealthPlus3.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthPlus3.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthPlus3.setFillColor(Color::White);
	}
	if (ennemyHealthMin1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthMin1.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthMin1.setFillColor(Color::White);
	}
	if (ennemyHealthMin2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthMin2.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthMin2.setFillColor(Color::White);
	}
	if (ennemyHealthMin3.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
		ennemyHealthMin3.setFillColor(Color(189, 189, 189));
	}
	else {
		ennemyHealthMin3.setFillColor(Color::White);
	}

}





