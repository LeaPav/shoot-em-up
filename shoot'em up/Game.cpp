#include "Game.h"

Game::Game() : currentState(MENU), isPaused(false), bossSpawn(false), spawnBoss(100), vagueActif(true), spawnBonusPhase(30)
{
	this->initSprite();
	this->initTexture();
	this->initWindow();
	this->initPlayer();
	this->initBoss();
	this->initScore();
	this->initLore();
	this->initBonus();
	this->initBonusState();
	this->initZones();
	this->initSound();
	this->initMusic();


}

Game::~Game()
{
	delete this->window;
	delete this->player;

}

/////////////////////////////////////////maj du Game affichage (Update)/////////////////////////////////////


void Game::update()
{
	Event event;

	while (this->window->pollEvent(event)) {

		if (event.type == Event::Closed)
			this->window->close();
		if (Keyboard::isKeyPressed(Keyboard::J)) {
			this->window->close();
		}
		if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
			if (currentState == GameState::PLAYING) {
				isPaused = true;
				currentState = GameState::PAUSE;
			}
			else if (currentState == GameState::PAUSE) {
				isPaused = false;
				currentState = GameState::PLAYING;
			}
			else if (currentState == GameState::PAUSESETTINGS) {
				currentState = GameState::PAUSE;
			}
		}

	}

	if (player->isDead()) {
		currentState = GameState::GAMEOVER;

	}
	if (boss->isBossDead()) {
		
		
		currentState = GameState::WIN;
	}
	handleMenuState(event);

}



void Game::playerUpdate()
{

	this->player->playerUpdate();
	this->player->udpateHealthBar();
}

void Game::projectileUpdate()
{
	for (auto& projectile : projectilesPlayer) {
		projectile->update();
	}

	for (auto& projectile : projectilesEnnemy) {
		projectile->update();
	}
	for (auto& projectile2 : projectilesBoss) {
		projectile2->update();
	}

}

void Game::ennemyUpdate()
{

	static int timer = 0; //utilisatin de static pour pas qu'il se remette à 0 à chaque appel de la fonction
	const int spawnInterval = 60;
	if (bonusActive[Bonus::SlowEnnemyProjectiles]) {
		for (auto& ennemy : ennemies) {
			ennemy->setRate(ennemy->getShootRate() + 5);
		}
	}
	timer++;
	if (timer >= spawnInterval) {
		this->createEnnemy();
		timer = 0;
	}
	this->shootEnnemy();
}

void Game::updateBoss()
{
	if (this->boss->canSpawn(scoreBoss, spawnBoss)) {
		
		lore = false;
	    if (bosslvl1.getStatus() != bosslvl1.Playing) {
				bosslvl1.play();
		}
		if (lvl1.getStatus() == lvl1.Playing) {
			lvl1.stop();
			lvl1.pause();

		}


		this->boss->update();
		this->boss->udpateHealthBar();
		this->shootingBoss();
	}
}
void Game::updateBonusZones()
{
	for (auto& zoneBonus : bonus) {
		if (zoneBonus.getBounds().intersects(player->getGlobalBounds())) {
			fill(bonusActive.begin(), bonusActive.end(), false);
			Bonus::AllBonus bonusType = zoneBonus.getBonus();
			activateBonus(bonusType);
			bonus.clear();
			vagueActif = true;
		}
		if (bonusTime.getElapsedTime().asMilliseconds() > 10000) {
			bonus.clear();
			vagueActif = true;
		}
	}
}

void Game::activateBonus(Bonus::AllBonus bonusType)
{
	if (bonusActive[bonusType]) return;

	bonusActive[bonusType] = true;

	switch (bonusType) {
	case Bonus::DoubleShooting:
		fireRate = 15;
		break;
	case Bonus::TripleShooting:
		fireRate = 15;
		break;
	case Bonus::TripleShootingDiag:
		fireRate = 15;
		break;
	case Bonus::Shield:
		if (bonusActive[Bonus::OffensiveShield]) {
			deactivateBonus(Bonus::OffensiveShield);
		}
		bonusShieldDef = 5;
		this->player->setupBonusShieldDef();
		break;
	case Bonus::HealthKit:
		if(player->getHealth() < player->getHealthMax())
			player->setHealth(player->getHealth() + bonusKit);
		break;
	case Bonus::OffensiveShield:
		if (bonusActive[Bonus::Shield]) {
			deactivateBonus(Bonus::Shield);
		}
		this->player->setupBonusShieldOff();
		break;
	case Bonus::Speed:
		fireRate = 10;
		break;
	}
}

void Game::deactivateBonus(Bonus::AllBonus bonusType)
{
	if (!bonusActive[bonusType]) return;

	bonusActive[bonusType] = false;
	switch (bonusType) {
	case Bonus::Shield:
		this->player->resetSprite();
		canHaveDamaged = false;
		break;
	case Bonus::OffensiveShield:
		this->player->resetSprite();
		canHaveDamaged = false;
		break;
	case Bonus::Speed:
		fireRate = 15;
		break;
	}
}

void Game::easyLevel()
{
	//canHaveDamaged = true;
	player->setMaxHealth(5);
	pv = 1;
	newPvPassif = pv;
	newPvAggressif = pv;
}

void Game::intermediaireLevel()
{
	//canHaveDamaged = true;
	player->setMaxHealth(3);
	pv = 2;
	newPvPassif = pv;
	newPvAggressif = pv;
}

void Game::hardLevel()
{
	//canHaveDamaged = true;
	player->setMaxHealth(1);
	pv = 3;
	newPvPassif = pv;
	newPvAggressif = pv;
}

void Game::changeHealthPlayerPlus(int hp)
{
	int newHp = player->getHealthMax() + hp;
	player->setMaxHealth(newHp);
}

void Game::changeHealthPlayerMin(int hp)
{
	int newHp = player->getHealthMax() - hp;
	player->setMaxHealth(newHp);

}

void Game::changeSpeedPlayerPlus(int speed)
{
	int newSpeed = player->getSpeed() + speed;
	player->setSpeed(newSpeed);
}

void Game::changeSpeedPlayerMin(int speed)
{
	int newSpeed = player->getSpeed() - speed;
	player->setSpeed(newSpeed);
}

void Game::changeHealthEnnemy1Plus(int hp)
{
	newPvAggressif += hp;
}

void Game::changeHealthEnnemy1Min(int hp)
{
	if (newPvAggressif > 1) {
		newPvAggressif -= hp;
	}
}

void Game::changeHealthBossPlus(int hp)
{
	int newHp = boss->getMaxHp() + hp;
	boss->setMaxhp(newHp);
}

void Game::changeHealthBoss1Min(int hp)
{
	int newHp = boss->getMaxHp() - hp;
	boss->setMaxhp(newHp);
}

void Game::changeHealthEnnemy2Plus(int hp)
{
	newPvPassif += hp;
}

void Game::changeSpeedEnnemyPlus(int speed)
{
	for (auto& ennemy : ennemies) {
		int newSpeed = ennemy->getSpeed() + speed;
		ennemy->setSpeed(newSpeed);
	}
}

void Game::changeSpeedEnnemyMin(int speed)
{
	for (auto& ennemy : ennemies) {
		int newSpeed = ennemy->getSpeed() - speed;
		ennemy->setSpeed(newSpeed);
	}
}

void Game::changeHealthEnnemy2Min(int hp)
{
	if (newPvPassif > 1) {
		newPvPassif -= hp;
	}
}

void Game::activatePhaseBoss()
{
	if (vagueActif && scoreBoss < spawnBoss) {
		scoreBoss = spawnBoss;
		vagueActif = false;
	}
}

void Game::deactivatePhaseBoss()
{
	if (!vagueActif) {
		scoreBoss = 0;
		vagueActif = true;
	}
}

void Game::monterSon(int newBruitage)
{
	bruitage += newBruitage;

	boomSound.setVolume(bruitage);
	looseGameSound.setVolume(bruitage);
	projoTirerSound.setVolume(bruitage);
	joueurToucherSound.setVolume(bruitage);
	
}

void Game::monterMusique(int newMusic)
{

	musique += newMusic;
	menu.setVolume(musique);
	lvl1.setVolume(musique);
	bosslvl1.setVolume(musique);
	victoire.setVolume(musique);

}

void Game::baisserSon(int newBruitage)
{
	if (bruitage >= 0) {
		bruitage -= newBruitage;
	}
	boomSound.setVolume(bruitage);
	looseGameSound.setVolume(bruitage);
	projoTirerSound.setVolume(bruitage);
	joueurToucherSound.setVolume(bruitage);
}

void Game::baisserMusique(int newMusic)
{
	if (musique >= 0) {
		musique -= newMusic;
	}
	menu.setVolume(musique);
	lvl1.setVolume(musique);
	bosslvl1.setVolume(musique);
	victoire.setVolume(musique);

}

const bool Game::windowIsOpen()
{
	return this->window->isOpen();
}
void Game::resetBonus()
{
	fill(bonusActive.begin(), bonusActive.end(), false);

	player->resetSprite();
	player->resetSpeed();
	fireRate = 15;
	bonusShotCount = 0;
	bonusShieldDef = 5;
	canHaveDamaged = true;
	
}
void Game::resetGame()
{
	player->reset();
	resetBonus();
	ennemies.clear();
	boss->reset();
	projectilesPlayer.clear();
	projectilesEnnemy.clear();
	projectilesBoss.clear();
	bonus.clear();
	score = 0;
	scoreBonus = 0;
	scoreBoss = 0;
	killStreak = 0;
	vagueActif = true;
	fireRate = 15;
	lore = true;
	curentlyLoose = 0;

	fill(bonusActive.begin(), bonusActive.end(), false);

	textScore.setString("Score : " + to_string(score));
}

///////////////////////////////////////////maj du Game affichage (Render)/////////////////////////////////////////////////

void Game::render()
{
	this->window->clear();
	this->handleMenu();
	this->window->display();

}

void Game::renderMenuPause()
{

	RectangleShape overlayTest(Vector2f(this->videoMode.width, this->videoMode.height));
	overlayTest.setFillColor(Color(0, 0, 0, 125));
	RectangleShape test(Vector2f(200.f, 40.f));

	this->window->draw(overlayTest);
	pauseMenu.renderPauseMenu(*window);

}

void Game::renderSettingsPause()
{

	RectangleShape overlay(Vector2f(this->videoMode.width, this->videoMode.height));
	overlay.setFillColor(Color(0, 0, 0, 125));
	this->window->draw(overlay);
	mainMenu.renderSettingsPauseMenu(*window);
}

void Game::renderGameOver()
{
	RectangleShape overlay(Vector2f(this->videoMode.width, this->videoMode.height));
	overlay.setFillColor(Color(0, 0, 0, 125));
	this->window->draw(overlay);
	gameOver.render(*window);
	gameOver.setScore(score);
}

void Game::renderWin()
{
	RectangleShape overlay(Vector2f(this->videoMode.width, this->videoMode.height));
	overlay.setFillColor(Color(0, 0, 0, 125));
	this->window->draw(overlay);
	win.render(*window);
	win.setScore(score,killStreak);
}


void Game::renderNiveau1()
{
	if (lvl1.getStatus() != lvl1.Playing && scoreBoss <= spawnBoss) {
		lvl1.play();
	}
	if (menu.getStatus() == menu.Playing) {
		menu.stop();
		menu.pause();

	}
	this->window->draw(basSens1);
	this->window->draw(basSens2);
	this->window->draw(basInvers1);
	this->window->draw(basInvers2);
	this->window->draw(hautSens1);
	this->window->draw(hautSens2);
	this->window->draw(hautInvers1);
	this->window->draw(hautInvers2);
	if (lore == true) {
		RectangleShape overlore(Vector2f(1625, 600));
		overlore.setPosition(225, 75);
		overlore.setFillColor(Color(0, 0, 0, 125));
		this->window->draw(overlore);
		this->window->draw(textLore);
	}
}

void Game::entityRender()
{
	
	this->player->render(*this->window);
	
	this->player->renderHealthBar(*this->window);

	for (auto& ennemy : ennemies) {
		ennemy->render(*this->window);
	}
}

void Game::projectileRender()
{
	for (auto& projectile : projectilesPlayer) {
		projectile->render(*this->window);
	}

	for (auto& projectile2 : projectilesEnnemy) {
		projectile2->render(*this->window);
	}
	for (auto& projectile3 : projectilesBoss) {
		projectile3->render(*this->window);
	}
}

void Game::renderBoss()
{
	this->boss->render(*this->window);
	if (scoreBoss >= spawnBoss) {
		this->boss->renderHealthBar(*this->window);
	}
}


void Game::renderBonusZones()
{
	for (auto& zone : bonus) {
		zone.render(*this->window);
	}
}

////////////////////////////////////////////////////////////////////etat du jeu////////////////////////////////////////////////////////////////

void Game::handleMenu() //les etats du jeu
{
	if (currentState == GameState::MENU) {
		mainMenu.render(*window);
	}
	if (currentState == GameState::PLAYING) {
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->renderBoss();
		this->projectileRender();
		this->renderBonusZones();
		this->window->draw(textScore);
	}
	if (currentState == GameState::PAUSE) {
		pauseMenu.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->renderBoss();
		this->projectileRender();
		this->window->draw(textScore);
		this->renderMenuPause();
	}
	if (currentState == GameState::OPTIONS) {
		mainMenu.handleMouseHover(*window);
		mainMenu.renderOptions(*window);
	}
	if (currentState == GameState::EDITOR) {
		mainMenu.handleMouseHover(*window);
		mainMenu.renderEditor(*window);
	}
	if (currentState == GameState::COMMANDS) {
		mainMenu.renderCommands(*window);
	}
	if (currentState == GameState::GAMEOVER) {
		

		if (looseGameSound.getStatus() != looseGameSound.Playing && curentlyLoose < 1) {
			looseGameSound.play();
			curentlyLoose += 1;
		}
		if (lvl1.getStatus() == lvl1.Playing) {
			lvl1.stop();
			lvl1.pause();
		}
		if (bosslvl1.getStatus() == bosslvl1.Playing) {
			bosslvl1.stop();
			bosslvl1.pause();
		}

		gameOver.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->renderBoss();
		this->projectileRender();
		this->window->draw(textScore);
		this->renderGameOver();
	}
	if (currentState == GameState::WIN) {

		if (victoire.getStatus() != victoire.Playing) {
			victoire.play();
		}
		if (lvl1.getStatus() == lvl1.Playing) {
			lvl1.stop();
			lvl1.pause();
		}
		if (bosslvl1.getStatus() == bosslvl1.Playing) {
			bosslvl1.stop();
			bosslvl1.pause();
		}

		win.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->renderBoss();
		this->projectileRender();
		this->window->draw(textScore);
		this->renderWin();
	}

	if (currentState == GameState::DIFFICULTY) {
		mainMenu.handleMouseHover(*window);
		mainMenu.renderDifficulty(*window);
	}
	if (currentState == GameState::LEVEL) {
		mainMenu.handleMouseHover(*window);
		mainMenu.renderLevel(*window);
  }
	if (currentState == GameState::SETTINGS) {
		mainMenu.handleMouseHover(*window);
		mainMenu.renderSettingsMenu(*window);
	}
	if (currentState == GameState::PAUSESETTINGS) {
		mainMenu.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->renderBoss();
		this->projectileRender();
		this->window->draw(textScore);
		this->renderSettingsPause();
	}
}

void Game::handleMenuState(Event& event) // gere les etat du jeu
{
	if (currentState == GameState::MENU) {
		if (lvl1.getStatus() == lvl1.Playing) {
			lvl1.stop();
			lvl1.pause();
		}
		if (bosslvl1.getStatus() == bosslvl1.Playing) {
			bosslvl1.stop();
			bosslvl1.pause();
		}
		if (looseGameSound.getStatus() == looseGameSound.Playing) {
			looseGameSound.stop();
			looseGameSound.pause();
		}
		if (victoire.getStatus() == victoire.Playing) {
			victoire.stop();
			victoire.pause();
		}
		if (menu.getStatus() != menu.Playing) {
			menu.play();
			menu.setPlayingOffset(sf::seconds(60));
		}
		
		mainMenu.handleMouseHover(*window);
		int action = mainMenu.handleInputMainMenu(*window, event);

		switch (action) {
		case 1: currentState = GameState::LEVEL;
			break;
		case 2: currentState = GameState::OPTIONS;
			break;
		case 3: currentState = GameState::EDITOR;
			break;
		case 4:
			this->window->close();
			break;
		}
	}
	if (currentState == GameState::PLAYING) {
		if (scoreBoss >= spawnBoss) {
			this->updateBoss();
		}
		this->ennemyUpdate();
		this->playerUpdate();
		this->updateBonusZones();
		this->projectileUpdate();
		this->checkCollisions();
		this->shoot();
		this->fonduNiveau1();
	}
	if (currentState == GameState::PAUSE) {
		pauseMenu.handleMouseHover(*window);
		int mouseAction = pauseMenu.handleInputPauseMenu(*window, event);

		switch (mouseAction) {
		case 1:
			currentState = GameState::PLAYING;
			break;
		case 2: currentState = GameState::PAUSESETTINGS;
			break;
		case 3: currentState = GameState::MENU;
			resetGame();
			mainMenu.resetCooldown();
			break;
		}

	}
	if (currentState == GameState::GAMEOVER) {
		gameOver.handleMouseHover(*window);
		int actionGameOver = gameOver.handleInput(*window, event);
		this->player->udpateHealthBar();
		this->boss->udpateHealthBar();
		switch (actionGameOver) {
		case 1: currentState = GameState::PLAYING;
			resetGame();
			break;
		case 2: currentState = GameState::MENU;
			resetGame();
			mainMenu.resetCooldown();
			break;
		}
	}
	if (currentState == GameState::WIN) {
		win.handleMouseHover(*window);
		int actionWin = win.handleInput(*window, event);
		this->player->udpateHealthBar();
		this->boss->udpateHealthBar();
		switch (actionWin) {
		case 1: currentState = GameState::PLAYING;
			resetGame();
			break;
		case 2: currentState = GameState::MENU;
			resetGame();
			mainMenu.resetCooldown();
			break;
		}
	}
	if (currentState == GameState::OPTIONS) {
		mainMenu.handleMouseHover(*window);
		int optionsAction = mainMenu.handleInputMenuOptions(*window, event);

		switch (optionsAction) {
		case 1: currentState = GameState::COMMANDS;
			break;
    case 2: 
			currentState = GameState::SETTINGS;
			  break;
		case 3: currentState = GameState::DIFFICULTY;
        break;
		case 4: currentState = GameState::MENU;
			break;
		}
	}
	if (currentState == GameState::COMMANDS) {
		mainMenu.handleMouseHover(*window);
		int actionCommands = mainMenu.handleInputMenuOptions(*window, event);

		switch (actionCommands) {
		case 4: currentState = GameState::OPTIONS;
			break;
		}
	}
	if (currentState == GameState::DIFFICULTY) {
		mainMenu.handleMouseHover(*window);
		int difficultyAction = mainMenu.handleInputDifficulty(*window, event);
		switch (difficultyAction) {
		case 1: 
			easyLevel();
			currentState = GameState::OPTIONS;
			break;
		case 2:
			intermediaireLevel();
			currentState = GameState::OPTIONS;
			break;
		case 3:
			hardLevel();
			currentState = GameState::OPTIONS;
			break;
		case 4: currentState = GameState::OPTIONS;
			break;
		}
	}
	if (currentState == GameState::LEVEL) {
		mainMenu.handleMouseHover(*window);
		int levelAction = mainMenu.handleInputLevel(*window, event);
		switch(levelAction) {
		case 1:
			currentState = GameState::PLAYING;
			break;
		case 4:
			currentState = GameState::MENU;
			break;
		}
	}
	if (currentState == GameState::EDITOR) {
		mainMenu.updateEditorTexts(player, newPvAggressif, newPvPassif, player->getSpeed(), boss);

		mainMenu.handleMouseHover(*window);
		int editorAction = mainMenu.handleInputEditor(*window, event);
		switch (editorAction) {
		case 1:
			changeHealthPlayerPlus(1);
			break;
		case 2:
			changeHealthPlayerMin(1);
			break;
		case 3:
			changeSpeedPlayerPlus(1);
			break;
		case 4:
			changeSpeedPlayerMin(1);
			break;
		case 5:
			changeHealthEnnemy1Plus(1);
			break;
		case 6:
			changeHealthEnnemy1Min(1);
			break;
		case 7:
			changeHealthEnnemy2Plus(1);
			break;
		case 8:
			changeHealthEnnemy2Min(1);
			break;
		case 9:
			changeSpeedEnnemyPlus(1);
			break;
		case 10:
			changeSpeedEnnemyMin(1);
			break;
		case 11:
			activatePhaseBoss();
			break;
		case 12:
			deactivatePhaseBoss();
			break;
		case 13:
			changeHealthBossPlus(1);
			break;
		case 14:
			changeHealthBoss1Min(1);
			break;
		case 15:
			currentState = GameState::MENU;
			break;
		}
	}
	if (currentState == GameState::SETTINGS) {
		mainMenu.updateSettingsTexts(bruitage, musique);

		mainMenu.handleMouseHover(*window);
		int settingsAction = mainMenu.handleInputSettingsMenu(*window, event);
		switch (settingsAction) {
		case 1:
			monterMusique(1);
			break;
		case 2:
			baisserMusique(1);
			break;
		case 3:
			monterSon(1);
			break;
		case 4: 
			baisserSon(1);
			break;
		case 6: currentState = GameState::OPTIONS;
			break;
		}
	}
	if (currentState == GameState::PAUSESETTINGS) {
		mainMenu.updateSettingsTexts(bruitage, musique);
		mainMenu.handleMouseHover(*window);
		int settingsAction = mainMenu.handleInputSettingsMenu(*window, event);
		switch (settingsAction) {
		case 1:
			monterMusique(1);
			break;
		case 2:
			baisserMusique(1);
			break;
		case 3:
			monterSon(1);
			break;
		case 4:
			baisserSon(1);
			break;
		case 6: currentState = GameState::OPTIONS;
			break;
		}
	}
}
/////////////////////////////////////////maj du Game fenetre (niveau in game) /////////////////////////////////////

int Game::initSprite() //fond du niveau
{	
	if (!bas_Sens1.loadFromFile("assets\\Fond_1\\ocean_final_sens_normal-1622-1080_bas.png")) 
		return -1; 

	if (!bas_invers1.loadFromFile("assets\\Fond_1\\ocean_final_sens_inverse_1622_1080_bas.png")) 
		return -1; 
	
	if (!bas_Sens2.loadFromFile("assets\\Fond_1\\ocean_final_sens_normal-1622-1080_bas.png")) 
		return -1; 
	
	if (!bas_invers2.loadFromFile("assets\\Fond_1\\ocean_final_sens_inverse_1622_1080_bas.png")) 
		return -1; 
	
	if (!haut_sens1.loadFromFile("assets\\Fond_1\\ocean_final_sens_normal-1622-1080_haut.png")) 
		return -1; 
	
	if (!haut_invers1.loadFromFile("assets\\Fond_1\\ocean_final_sens_inverse_1622_1080_haut.png")) 
		return -1; 
		
	if (!haut_sens2.loadFromFile("assets\\Fond_1\\ocean_final_sens_normal-1622-1080_haut.png")) 
		return -1; 
		
	if (!haut_invers2.loadFromFile("assets\\Fond_1\\ocean_final_sens_inverse_1622_1080_haut.png")) 
		return -1; 
	
}

void Game::initTexture() //metre texture sur les sprite
{
	basSens1.setTexture(bas_Sens1);					
	basInvers1.setTexture(bas_invers1);
	basSens2.setTexture(bas_Sens2);
	basInvers2.setTexture(bas_invers2);
	hautSens1.setTexture(haut_sens1);
	hautInvers1.setTexture(haut_invers1);
	hautSens2.setTexture(haut_sens2);
	hautInvers2.setTexture(haut_invers2);

	/////////////////////////////initialisation des position//////////////////////////////////////////////

	basSens1.setPosition(Vector2f(0.f, 626.f));
	basInvers1.setPosition(Vector2f(1622.f, 626.f));
	basSens2.setPosition(Vector2f(3244.f, 626.f));
	basInvers2.setPosition(Vector2f(4866.f, 626.f));


	hautSens1.setPosition(Vector2f(0.f, 0.f));
	hautInvers1.setPosition(Vector2f(1622.f, 0.f));
	hautSens2.setPosition(Vector2f(3244.f, 0.f));
	hautInvers2.setPosition(Vector2f(4866.f, 0.f));
}

void Game::fonduNiveau1()
{
	float depop = 1622.f;

	if (basSens1.getPosition().x <= -depop) {
		basSens1.setPosition(basInvers2.getPosition().x + depop, basSens1.getPosition().y);
	}
	if (basInvers1.getPosition().x <= -depop) {
		basInvers1.setPosition(basSens1.getPosition().x + depop, basInvers1.getPosition().y);
	}
	if (basSens2.getPosition().x <= -depop) {
		basSens2.setPosition(basInvers1.getPosition().x + depop, basSens2.getPosition().y);
	}
	if (basInvers2.getPosition().x <= -depop) {
		basInvers2.setPosition(basSens2.getPosition().x + depop, basSens2.getPosition().y);
	}


	if (hautSens1.getPosition().x <= -depop) {
		hautSens1.setPosition(hautInvers2.getPosition().x + depop, hautSens1.getPosition().y);
	}
	if (hautInvers1.getPosition().x <= -depop) {
		hautInvers1.setPosition(hautSens1.getPosition().x + depop, hautInvers1.getPosition().y);
	}
	if (hautSens2.getPosition().x <= -depop) {
		hautSens2.setPosition(hautInvers1.getPosition().x + depop, hautSens2.getPosition().y);
	}
	if (hautInvers2.getPosition().x <= -depop) {
		hautInvers2.setPosition(hautSens2.getPosition().x + depop, hautInvers2.getPosition().y);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////

	basSens1.move(Vector2f(-10, 0.f));
	basSens2.move(Vector2f(-10, 0.f));
	basInvers1.move(Vector2f(-10, 0.f));
	basInvers2.move(Vector2f(-10, 0.f));
	hautSens1.move(Vector2f(-3, 0.f));
	hautSens2.move(Vector2f(-3, 0.f));
	hautInvers1.move(Vector2f(-3, 0.f));
	hautInvers2.move(Vector2f(-3, 0.f));

}

void Game::initWindow() //création fenetre
{
	this->videoMode.width = mapWidth;
	this->videoMode.height = mapHeight;
	this->window = new RenderWindow(videoMode, "StarWater", Style::Fullscreen);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);
}

void Game::initScore() //création score
{
	if (!font.loadFromFile("assets/font/fontpause.ttf")) {
		cout << "ERREUR";
	}
	textScore.setFont(font);
	textScore.setPosition(0, 0);
	textScore.setCharacterSize(50);
	textScore.setFillColor(Color::Red);
	textScore.setString("Score: " + to_string(score));
}

void Game::initLore() 
{
	
		if (!loresque.loadFromFile("assets/font/menu.ttf")) {
			cout << "ERREUR";
		}
		textLore.setFont(loresque);
		textLore.setPosition(250, 100);
		textLore.setCharacterSize(25);
		textLore.setFillColor(Color::Black);
		textLore.setString("En tant que benevoles de la federation des defenseurs de l'espace\net pourfendeurs de pirates de l'espace, eliminez les pirates de l'espace qui ont envahi 4546B\net immergez vous dans cette planete afin de trouver le droide des pirates de l'espace\n\n\nApres tout, il n'y a pas de bon ou mauvais pirate de l'espace, c'est avant tout une vocation,\nune maniere de vivre. Certes, ils sont en proie au danger, mais peut-etre qu'ils trouvent leur volonte\nde vivre dans cette mechancete gratuite qui leur procure leur bonheur au detriment\nd'autrui. Mais qui sommes-nous pour les blamer apres les multiples erreurs qu'a pu commettre\nla Federation des defenseurs de l'espace, peut-etre bien que certains pirates sont d'anciens\npartisans mais qu'ils se sont sentis trahis par cette federation et ont cherche leur bonheur\nailleurs, mais finalement ont-ils raison ? Ont-ils fait le bon choix ? Sont-ils prets a entendre raison ?\nEh bien non, et c'est pour cela que vous intervenez afin de couper le mal a sa racine\navant qu'il ne cause plus de degats a cette planete de vacances que vous aimez tant.\n\n\n                                             appuyez sur espace pour commencer");
}

void Game::initSound() {  //bruitage

	if (!boom.loadFromFile("assets/Son/Bruitage/boom.mp3"))
		cout << "erreur boom";
	if (!looseGame.loadFromFile("assets/Son/Bruitage/loose_game.mp3"))
		cout << "erreur loose game";
	if (!projoTirer.loadFromFile("assets/Son/Bruitage/ProjoTirer.mp3"))
		cout << "erreur projotirer";
	if (!joueurToucher.loadFromFile("assets/Son/Bruitage/toucher_J.mp3"))
		cout << "erreur trouvher j";

	boomSound.setBuffer(boom);
	looseGameSound.setBuffer(looseGame);
	projoTirerSound.setBuffer(projoTirer);
	joueurToucherSound.setBuffer(joueurToucher);
	

	boomSound.setVolume(bruitage);
	looseGameSound.setVolume(bruitage);
	projoTirerSound.setVolume(bruitage);
	joueurToucherSound.setVolume(bruitage);
}


void Game::initMusic() { //musique

	if (!menu.openFromFile("assets/Son/Musique/son menu.mp3"))
		cout << "erreur menu";
	if (!lvl1.openFromFile("assets/Son/Musique/Level1Sing.mp3"))
		cout << "erreur lvl1";
	if (!bosslvl1.openFromFile("assets/Son/Musique/BoosFight.mp3"))
		cout << "erreur boss lvl1";
	if (!victoire.openFromFile("assets/Son/Musique/Victory.mp3"))
		cout << "erreur victoire";

	menu.setVolume(musique);
	lvl1.setVolume(musique);
	bosslvl1.setVolume(musique);
	victoire.setVolume(musique);

}

////////////////////////////////////////////////Initialisation bonus////////////////////////////////////////////////////

void Game::initBonus()
{
	bonusTexture[Bonus::DoubleShooting].loadFromFile("assets/bonus/bonus_2_projo.png");
	bonusTexture[Bonus::TripleShooting].loadFromFile("assets/bonus/bonus_3_tir.png");
	bonusTexture[Bonus::TripleShootingDiag].loadFromFile("assets/bonus/bonus_3_diag.png");
	bonusTexture[Bonus::Shield].loadFromFile("assets/bonus/bonus_protection.png");
	bonusTexture[Bonus::HealthKit].loadFromFile("assets/bonus/bonus_soin.png");
	bonusTexture[Bonus::SlowEnnemyProjectiles].loadFromFile("assets/bonus/bonus_anti-speed.png");
	bonusTexture[Bonus::OffensiveShield].loadFromFile("assets/bonus/bonus_protection_renvoie.png");
	bonusTexture[Bonus::Speed].loadFromFile("assets/bonus/bonus_speed.png");
}
void Game::initZones()
{
	bonusZones.push_back(Vector2f(1000.f, 200.f));
	bonusZones.push_back(Vector2f(1000.f, 500.f));
	bonusZones.push_back(Vector2f(1000.f, 800.f));
	
}

void Game::initBonusState()
{
	bonusActive.resize(totalBonus, false);
}

void Game::spawnBonus()
{
	ennemies.clear();
	projectilesEnnemy.clear();
	srand(time(0));
	bonusZones.clear();

	int randBonus1 = rand() % 8;
	int randBonus2 = rand() % 8;
	int randBonus3 = rand() % 8;

	while (randBonus1 == randBonus2) {
		randBonus2 = rand() % 8;
	}
	while (randBonus1 == randBonus3 || randBonus2 == randBonus3) {
		randBonus3 = rand() % 8;
	}

	bonus.emplace_back(static_cast<Bonus::AllBonus>(randBonus1), bonusTexture[randBonus1], bonusZones[0]);
	bonus.emplace_back(static_cast<Bonus::AllBonus>(randBonus2), bonusTexture[randBonus2], bonusZones[1]);
	bonus.emplace_back(static_cast<Bonus::AllBonus>(randBonus3), bonusTexture[randBonus3], bonusZones[2]);
	
	bonusTime.restart();
	
}
/////////////////////////////////////////////////maj du game entity/////////////////////////////////////////////////////

void Game::initPlayer() // création du J
{
	this->player = new Player(15);
}

void Game::initBoss()
{
	this->boss = new Boss();
}

void Game::createEnnemy() //créateur des ennemies + vagues
{
	int distance = 2020;
	int random = rand() % 4;

	bool peacefull = false;
	
	
	
	if (scoreBonus >= spawnBonusPhase && lore == false) {
		vagueActif = false;
		spawnBonus();
		deactivateBonus(Bonus::Speed);
		scoreBonus = 0;

	}

	

	if (scoreBoss < spawnBoss && vagueActif && lore == false) {


		while (random == 3 && scoreBoss < 20) {
			random = rand() % 3;
		}
		while (random == 2 && scoreBoss < 40) {
			random = rand() % 2;
		}
		

		if (random == 0) {   //pyramide par 3 tir

			MovementType randomType = static_cast<MovementType>(rand() % 2);

			int largeur = rand() % this->videoMode.height;

			if (randomType == STRAIGHT_FAST) {
				peacefull = true;
			}

			Ennemy* newEnnemy1 = new Ennemy(randomType, newPvAggressif, 10, 90, peacefull); // mouvement, life, cooldown, firerate, passif, texture
			newEnnemy1->setPosition(distance, largeur);
			if (newEnnemy1->destroy()) {
				delete newEnnemy1;
			}
			ennemies.push_back(newEnnemy1);

			Ennemy* newEnnemy2 = new Ennemy(randomType, newPvAggressif, 10, 90, peacefull); // mouvement, life, cooldown, firerate, passif
			newEnnemy2->setPosition(distance + 75, largeur + 75);
			if (newEnnemy2->destroy()) {
				delete newEnnemy2;
			}
			ennemies.push_back(newEnnemy2);

			Ennemy* newEnnemy3 = new Ennemy(randomType, newPvAggressif, 10, 90, peacefull); // mouvement, life, cooldown, firerate, passif
			newEnnemy3->setPosition(distance + 75, largeur - 75);
			if (newEnnemy3->destroy()) {
				delete newEnnemy3;
			}
			ennemies.push_back(newEnnemy3);
		}
		if (random == 1) { //mur par 3 passif

			MovementType randomType = static_cast<MovementType>(rand() % 4);

			int largeur = rand() % this->videoMode.height;

			Ennemy* newEnnemy1 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
			newEnnemy1->setPosition(distance, largeur);
			if (newEnnemy1->destroy()) {
				delete newEnnemy1;
			}
			ennemies.push_back(newEnnemy1);

			Ennemy* newEnnemy2 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
			newEnnemy2->setPosition(distance, largeur + 80);
			if (newEnnemy2->destroy()) {
				delete newEnnemy2;
			}
			ennemies.push_back(newEnnemy2);

			Ennemy* newEnnemy3 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
			newEnnemy3->setPosition(distance, largeur - 80);
			if (newEnnemy3->destroy()) {
				delete newEnnemy3;
			}
			ennemies.push_back(newEnnemy3);
		}
		if (random == 2 && scoreBoss >= 40) { // pyramide par 5 tir

				int largeur = rand() % this->videoMode.height;

				Ennemy* newEnnemy1 = new Ennemy(STRAIGHT, newPvAggressif, 0, 90, peacefull); // mouvement, life, cooldown, firerate, passif
				newEnnemy1->setPosition(distance, largeur);
				if (newEnnemy1->destroy()) {
					delete newEnnemy1;
				}
				ennemies.push_back(newEnnemy1);

				Ennemy* newEnnemy2 = new Ennemy(STRAIGHT, newPvAggressif, 0, 90, peacefull); // mouvement, life, cooldown, firerate, passif
				newEnnemy2->setPosition(distance + 75, largeur + 75);
				if (newEnnemy2->destroy()) {
					delete newEnnemy2;
				}
				ennemies.push_back(newEnnemy2);

				Ennemy* newEnnemy3 = new Ennemy(STRAIGHT, newPvAggressif, 0, 90, peacefull); // mouvement, life, cooldown, firerate, passif
				newEnnemy3->setPosition(distance + 75, largeur - 75);
				if (newEnnemy3->destroy()) {
					delete newEnnemy3;
				}
				ennemies.push_back(newEnnemy3);

				Ennemy* newEnnemy4 = new Ennemy(STRAIGHT, newPvAggressif, 0, 90, peacefull); // mouvement, life, cooldown, firerate, passif
				newEnnemy4->setPosition(distance + 150, largeur + 150);
				if (newEnnemy4->destroy()) {
					delete newEnnemy4;
				}
				ennemies.push_back(newEnnemy4);

				Ennemy* newEnnemy5 = new Ennemy(STRAIGHT, newPvAggressif, 0, 90, peacefull); // mouvement, life, cooldown, firerate, passif
				newEnnemy5->setPosition(distance + 150, largeur - 150);
				if (newEnnemy5->destroy()) {
					delete newEnnemy5;
				}
				ennemies.push_back(newEnnemy5);



		}
		if (random == 3 && scoreBoss >= 20) { //mur par 5

				MovementType randomType = static_cast<MovementType>(rand() % 4);

				if (scoreBoss <= 30) {
					randomType = STRAIGHT;
				}

				int largeur = rand() % this->videoMode.height;

				Ennemy* newEnnemy1 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
				newEnnemy1->setPosition(distance, largeur);
				if (newEnnemy1->destroy()) {
					delete newEnnemy1;
				}
				ennemies.push_back(newEnnemy1);

				Ennemy* newEnnemy2 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
				newEnnemy2->setPosition(distance, largeur + 80);
				if (newEnnemy2->destroy()) {
					delete newEnnemy2;
				}
				ennemies.push_back(newEnnemy2);

				Ennemy* newEnnemy3 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
				newEnnemy3->setPosition(distance, largeur - 80);
				if (newEnnemy3->destroy()) {
					delete newEnnemy3;
				}
				ennemies.push_back(newEnnemy3);

				Ennemy* newEnnemy4 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
				newEnnemy4->setPosition(distance, largeur - 160);
				if (newEnnemy4->destroy()) {
					delete newEnnemy4;
				}
				ennemies.push_back(newEnnemy4);

				Ennemy* newEnnemy5 = new Ennemy(randomType, newPvPassif, 0, 90, true, 2); // mouvement, life, cooldown, firerate, passif
				newEnnemy5->setPosition(distance, largeur + 160);
				if (newEnnemy5->destroy()) {
					delete newEnnemy5;
				}
				ennemies.push_back(newEnnemy5);
		}
		
	}
}


/////////////////////////////////////////projo////////////////////////////////////////

void Game::createProjectilesPlayer(float x, float y)
{
	lore = false;
	Projectile* newProjectile = new Projectile(x, y, 15.f, 0.f, Projectile::ProjectileType::PLAYER);
	projectilesPlayer.push_back(newProjectile);

}

void Game::createProjectilesPlayerDiag(float x, float y, float xDiag, float yDiag)
{
	Projectile* newProjectile = new Projectile(x, y, xDiag,yDiag, Projectile::ProjectileType::PLAYER);
	projectilesPlayer.push_back(newProjectile);
}

void Game::createProjectilesEnnemy(float x, float y)
{
	Projectile* newProjectile = new Projectile(x, y, -15.f, 0.f, Projectile::ProjectileType::ENNEMY);
	projectilesEnnemy.push_back(newProjectile);
}

void Game::createProjectilesBoss(float x, float y)
{
	Projectile* newProjectile = new Projectile(x, y, -15.f, 0.f, Projectile::ProjectileType::BOSS);
	projectilesBoss.push_back(newProjectile);
}

//////////////////////////////////////////colision////////////////////////////////////////////////////////

void Game::checkCollisions()
{
	vector<Projectile*> projectilesToRemove;
	vector<Ennemy*> ennemiesToRemove;

	for (auto& projectile : projectilesPlayer) {
		for (auto& ennemy : ennemies) {
			if (projectile->getGlobalBounds().intersects(ennemy->getGlobalBounds()) && ennemy->verifSpawnEnnemy()) {	
				ennemy->damage(1);
				projectile->markAsOutOfScreen();
				curentlyboom = 0;

				if (ennemy->isDead()) {

					scoreBonus++;
					killStreak++;
					int multiplicateur = 1 + (1*killStreak);
					score = score + multiplicateur;
					scoreBoss++;
					
					textScore.setString("Score: " + to_string(score));

					if (boomSound.getStatus() != boomSound.Playing ) {
						boomSound.setPlayingOffset(seconds(0.5));
						boomSound.play();
						
					}
					
					ennemiesToRemove.push_back(ennemy);
				}
			}
		}
	}
	if (player->getGlobalBounds().intersects(boss->getGlobalBounds())) {
		player->damage(100);
	}
	for (auto& projectile : projectilesEnnemy) {
		if (player->getGlobalBounds().intersects(projectile->getGlobalBounds())) {

			if (bonusActive[Bonus::Shield]) {
				canHaveDamaged = false;
				if (bonusShieldDef > 0) {
					bonusShieldDef--;
					cout << bonusShieldDef << endl;
				}
				if (bonusShieldDef == 0) {
					deactivateBonus(Bonus::Shield);
				}
			}
			else if (bonusActive[Bonus::OffensiveShield]) {
				deactivateBonus(Bonus::OffensiveShield);
			}
			if (canHaveDamaged) {
				if (joueurToucherSound.getStatus() != joueurToucherSound.Playing) {
					joueurToucherSound.setPlayingOffset(seconds(0));
					joueurToucherSound.play();
				}
				player->damage(1);
			}
			projectile->markAsOutOfScreen();
		}
	}
	
	for (auto& ennemy : ennemies) {
		if (ennemy->getGlobalBounds().intersects(player->getGlobalBounds())) {
			if (joueurToucherSound.getStatus() != joueurToucherSound.Playing) {
				joueurToucherSound.setPlayingOffset(seconds(0));
				joueurToucherSound.play();
			}
			ennemy->damage(10);
			if (checkCollisionsBonus(player, ennemy)) {
				timeCheckCollision.restart();
				break;
			}
			else if (canHaveDamaged) {
				if (tpsTouch.getElapsedTime().asMilliseconds() > 201) {
					killStreak = 0;
					cout << "Degats" << endl;
					player->damage(1);
					tpsTouch.restart();
				}
			}
			if (timeCheckCollision.getElapsedTime().asMilliseconds() > 100) {
				canHaveDamaged = true;
			}
		}
	}


	for (auto& projectile : projectilesBoss) {
		if (player->getGlobalBounds().intersects(projectile->getGlobalBounds())) {
			canHaveDamaged = true;
			if (bonusActive[Bonus::Shield]) {
				canHaveDamaged = false;
				if (bonusShieldDef > 0) {
					bonusShieldDef--;
				}
				if (bonusShieldDef == 0) {
					timeCheckCollision.restart();
					deactivateBonus(Bonus::Shield);
				}
			}
			else if (bonusActive[Bonus::OffensiveShield]) {
				timeCheckCollision.restart();
				deactivateBonus(Bonus::OffensiveShield);
			}

			if (canHaveDamaged) {
				player->damage(2);
			}
			projectile->markAsOutOfScreen();
		}
		if (timeCheckCollision.getElapsedTime().asMilliseconds() > 100) {
			canHaveDamaged = true;
		}
	}

	for (auto& projectile : projectilesPlayer) {
		if (projectile->getGlobalBounds().intersects(boss->getGlobalBounds())) {
			if (boss->verifSpawnBoss()) {
				if (boss->getPhase() == 1 || boss->getPhase() == 3) {
					boss->takeDamage(1);
				}
			}
			projectile->markAsOutOfScreen();
		}
		if (projectile->getGlobalBounds().intersects(boss->getRobot1Bounds())) {
			boss->damageRobot1(1);
			projectile->markAsOutOfScreen();
		}
		if (projectile->getGlobalBounds().intersects(boss->getRobot2Bounds())) {
			boss->damageRobot2(1);
			projectile->markAsOutOfScreen();
		}
	}
	
	projectilesPlayer.erase(remove_if(projectilesPlayer.begin(), projectilesPlayer.end(), [](Projectile* p) {
		if (p->outOfScreen()) {
			delete p;
			return true;
		}
		return false;
		}),
		projectilesPlayer.end()
	);
	projectilesBoss.erase(remove_if(projectilesBoss.begin(), projectilesBoss.end(), [](Projectile* p) {
		if (p->outOfScreen()) {
			delete p;
			return true;
		}
		return false;
		}),
		projectilesBoss.end()
	);
	projectilesEnnemy.erase(remove_if(projectilesEnnemy.begin(), projectilesEnnemy.end(), [](Projectile* p) {
		if (p->outOfScreen()) {
			delete p;
			return true;
		}
		return false;
		}),
		projectilesEnnemy.end()
	);
	ennemies.erase(remove_if(ennemies.begin(), ennemies.end(), [](Ennemy* e) {

			if (e->tpsdead.getElapsedTime().asMilliseconds() < 100) {

				
		    	e->explosion();

				
			}
		
		else {
			if (e->destroy() || e->isDead()) {
				delete e;
				return true;
			}
		}
		return false;
		}),
		ennemies.end()
	);
}

bool Game::checkCollisionsBonus(Player* player, Ennemy* ennemy)
{
	if (bonusActive[Bonus::Shield]) {
		deactivateBonus(Bonus::Shield);
		return true;
	}
	if (bonusActive[Bonus::OffensiveShield]) {

		scoreBonus++;
		killStreak++;
		int multiplicateur = 1 + (1 * killStreak);
		score = score + multiplicateur;
		scoreBoss++;

		return true;
	}
	return false;
}

////////////////////////////////degats//////////////////////////////////////////////////////////////////////////////////////////

void Game::shoot()
{
	static int cooldownShoot = 0;


	if (Keyboard::isKeyPressed(Keyboard::Space) && cooldownShoot <= 0) {
		projoTirerSound.play();
		float TopplayerX = this->player->getPosition().x + 73.f;
		float TopplayerY = this->player->getPosition().y + 5.f;
		
		float MidplayerX = this->player->getPosition().x + 80.f;
		float MidplayerY = this->player->getPosition().y + 40.f;

		float LowplayerX = this->player->getPosition().x + 73.f;
		float LowplayerY = this->player->getPosition().y + 75.f;

		if (bonusActive[Bonus::TripleShooting]) {
			createProjectilesPlayer(TopplayerX, TopplayerY);
			createProjectilesPlayer(MidplayerX, MidplayerY);
			createProjectilesPlayer(LowplayerX, LowplayerY);
		}
		else if (bonusActive[Bonus::DoubleShooting]) {
			createProjectilesPlayer(TopplayerX, TopplayerY);
			createProjectilesPlayer(LowplayerX, LowplayerY);
		}
		else if (bonusActive[Bonus::TripleShootingDiag]) {
			createProjectilesPlayer(MidplayerX, MidplayerY);
			createProjectilesPlayerDiag(TopplayerX, TopplayerY, 10.f, -10.f);
			createProjectilesPlayerDiag(LowplayerX, LowplayerY, 10.f, 10.f);

		}
		else if (bonusActive[Bonus::Speed]) {
			createProjectilesPlayer(MidplayerX, MidplayerY);
			activateBonus(Bonus::Speed);
		}
		else {
			fireRate = 15;
			createProjectilesPlayer(MidplayerX, MidplayerY);
		}
		cooldownShoot = fireRate;
	}
	if (cooldownShoot > 0) {
			cooldownShoot--;
	}
}

void Game::shootEnnemy()
{
	for (auto& ennemy : ennemies) {
		ennemy->update();
		ennemy->updateShootCooldown();
		if (ennemy->canShoot() && !ennemy->getPassif()) {
	
			float ennemyX = ennemy->getPosition().x - 37.f;
			float ennemyY = ennemy->getPosition().y + 37.f;
			createProjectilesEnnemy(ennemyX, ennemyY);

			ennemy->resetShootCooldown();
		}
	}
}


void Game::shootingBoss()
{
	static int shootBoss = 0;
	if (boss->shouldShoot() && !boss->isBossDead()) {
		float boss1ProjoX = boss->getPosition().x;
		float boss1ProjoY = boss->getPosition().y+50;

		float boss2ProjoX = boss->getPosition().x;
		float boss2ProjoY = boss->getPosition().y + 200.f;

		
			if (shootBoss == 0) {
				this->createProjectilesBoss(boss1ProjoX, boss1ProjoY);
				shootBoss++;
			}
			else if (shootBoss == 1) {
				this->createProjectilesBoss(boss2ProjoX, boss2ProjoY);
				shootBoss--;
			}
		
		if (boss->getPhase() == 2) {
			float robot1X = boss->getRobot1Position().x;
			float robot1Y = boss->getRobot1Position().y + 50.f;
			this->createProjectilesBoss(robot1X, robot1Y);

			float robot2X = boss->getRobot2Position().x;
			float robot2Y = boss->getRobot2Position().y + 50.f;
			this->createProjectilesBoss(robot2X, robot2Y);
		}
		boss->restartShootClock();
	}
}


