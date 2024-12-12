#include "Game.h"

int Game::initSprite()
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

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTexture()
{
	basSens1.setTexture(bas_Sens1);					//metre texture sur les sprite
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

void Game::initWindow()
{
	this->videoMode.width = mapWidth;
	this->videoMode.height = mapHeight;
	this->window = new RenderWindow(videoMode, "StarWater", Style::Fullscreen);
	this->window->setVerticalSyncEnabled(true);
	this->window->setFramerateLimit(60);
}

void Game::initScore()
{
	if (!font.loadFromFile("assets/font/test.ttf")) {
		cout << "ERREUR";
	}
	textScore.setFont(font);
	textScore.setPosition(0, 0);
	textScore.setCharacterSize(30);
	textScore.setFillColor(Color::Green);
	textScore.setString(to_string(score));
}


void Game::createEnnemy()
{
	
	MovementType randomType = static_cast<MovementType>(rand() % 3);

	Ennemy* newEnnemy = new Ennemy(randomType, 1, 0, 30, false); // mouvement, life, cooldown, firerate, passif
	newEnnemy->setPosition(1920, rand() % this->videoMode.height);
	if (newEnnemy->destroy()) {
		delete newEnnemy;
	}
	ennemies.push_back(newEnnemy);
}

void Game::createProjectiles(float x, float y)
{
	Projectile* newProjectile = new Projectile(x, y, 15.f, 0.f);
	projectilesPlayer.push_back(newProjectile);
}

void Game::createProjectilesEnnemy(float x, float y)
{
	Projectile* newProjectile = new Projectile(x, y, -15.f, 0.f);
	projectilesEnnemy.push_back(newProjectile);

	//cout << "Projectile créé à (" << x << ", " << y << ")" << endl;
}

void Game::entityRender()
{
	this->player->render(*this->window);
	this->player->renderHealthBar(*this->window);

	for (auto& ennemy : ennemies) {
		ennemy->render(*this->window);
	}
}

Game::Game() : currentState(MENU), isPaused(false)
{
	this->initSprite();
	this->initTexture();
	this->initWindow();
	this->initPlayer();
	this->initScore();
	score = 0;
}

Game::~Game()
{
	delete this->window;
	delete this->player;

}

const bool Game::windowIsOpen()
{
	return this->window->isOpen();
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

}

void Game::ennemyUpdate()
{

	static int timer = 0; //utilisatin de static pour pas qu'il se remette à 0 à chaque appel de la fonction
	const int spawnInterval = 60;

	timer++;
	if (timer >= spawnInterval) {
		this->createEnnemy();
		timer = 0;
	}
	this->shootEnnemy();
}

void Game::projectileRender()
{
	for (auto& projectile : projectilesPlayer) {
		projectile->render(*this->window);
	}

	for (auto& projectile2 : projectilesEnnemy) {
		projectile2->render(*this->window);
	}
}

void Game::checkCollisions()
{
	vector<Projectile*> projectilesToRemove;
	vector<Ennemy*> ennemiesToRemove;

	for (auto& projectile : projectilesPlayer) {
		for (auto& ennemy : ennemies) {
			if (projectile->getGlobalBounds().intersects(ennemy->getGlobalBounds())) {	
				ennemy->damage(1);
				projectile->markAsOutOfScreen();

				if (ennemy->isDead()) {
					score++;
					textScore.setString(to_string(score));
					ennemiesToRemove.push_back(ennemy);
				}
			}
		}
	}

	for (auto& projectile : projectilesEnnemy) {
		if (player->getGlobalBounds().intersects(projectile->getGlobalBounds())) {
			player->damage(1);
			projectile->markAsOutOfScreen();
		}
	}
	
	for (auto& ennemy : ennemies) {
		if (ennemy->getGlobalBounds().intersects(player->getGlobalBounds())) {
			ennemy -> damage(1);
			player->damage(1);
		}
	}

	for (auto& projectile : projectilesToRemove) {
		projectilesPlayer.erase(remove(projectilesPlayer.begin(), projectilesPlayer.end(), projectile), projectilesPlayer.end());
		delete projectile; 
	}
	for (auto& ennemy : ennemiesToRemove) {
		ennemies.erase(remove(ennemies.begin(), ennemies.end(), ennemy), ennemies.end());
		delete ennemy; 
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

	projectilesEnnemy.erase(remove_if(projectilesEnnemy.begin(), projectilesEnnemy.end(), [](Projectile* p) {
		if (p->outOfScreen()) {
			//cout << "Suppression d'un projectile ennemi" << endl;
			delete p;
			return true;
		}
		return false;
		}),
		projectilesEnnemy.end()
	);
	ennemies.erase(remove_if(ennemies.begin(), ennemies.end(), [](Ennemy* e) {
		if (e->destroy() || e->isDead()) {
			delete e;
			return true;
		}
		return false;
		}),
		ennemies.end()
	);
}

void Game::shoot()
{
	static int cooldownShoot = 0;
	const int fireRate = 15;

	if (Keyboard::isKeyPressed(Keyboard::F) && cooldownShoot <= 0) {
		float playerX = this->player->getPosition().x + 80.f;
		float playerY = this->player->getPosition().y + 40.f;
		createProjectiles(playerX, playerY);
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

void Game::handleMenuState(Event& event)
{
	if (currentState == GameState::MENU) {
		player->reset();
		mainMenu.handleMouseHover(*window);
		int action = mainMenu.handleInputMainMenu(*window, event);
		player->reset();
	

		switch (action) {
		case 1: currentState = GameState::PLAYING;
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
			this->playerUpdate();
			this->ennemyUpdate();
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
		switch (actionGameOver) {
		case 1: currentState = GameState::PLAYING;
			resetGame();
			break;
		case 2: currentState = GameState::MENU;
			resetGame();
			mainMenu.resetCooldown();
			//player->reset();
			break;
		}
	}
	if (currentState == GameState::OPTIONS) {
		mainMenu.handleMouseHover(*window);
		int optionsAction = mainMenu.handleInputMenuOptions(*window, event);

		switch (optionsAction) {
		case 1: currentState = GameState::COMMANDS;
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
}

void Game::handleMenu()
{
	if (currentState == GameState::MENU) {
		mainMenu.render(*window);
	}
	if (currentState == GameState::PLAYING) {
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->projectileRender();
		this->window->draw(textScore);
	}
	if (currentState == GameState::PAUSE) {
		pauseMenu.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
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
		gameOver.handleMouseHover(*window);
		this->renderNiveau1();
		this->window->draw(this->spriteMap);
		this->entityRender();
		this->projectileRender();
		this->window->draw(textScore);
		this->renderGameOver();
	}
}

void Game::renderMenuPause()
{
//	pauseMenu.handleMouseHover(*window);


	RectangleShape overlayTest(Vector2f(this->videoMode.width, this->videoMode.height));
	overlayTest.setFillColor(Color(0, 0, 0, 125));
	//his->window->draw(overlayTest);
	RectangleShape test(Vector2f(200.f, 40.f));
	//this->window->draw(test);

	this->window->draw(overlayTest);
	pauseMenu.renderPauseMenu(*window);

}

void Game::renderGameOver()
{
	RectangleShape overlay(Vector2f(this->videoMode.width, this->videoMode.height));
	overlay.setFillColor(Color(0, 0, 0, 125));
	this->window->draw(overlay);
	gameOver.render(*window);
}

void Game::update()
{
	Event event;
	//handleMenuState(event);
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
		}

	}

	if (player->isDead()) {
		currentState = GameState::GAMEOVER;
		
	}
	handleMenuState(event);
	
}

void Game::render()
{
	this->window->clear();
	this->handleMenu();
	this->window ->display();

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

void Game::renderNiveau1()
{
	this->window->draw(basSens1);
	this->window->draw(basSens2);
	this->window->draw(basInvers1);
	this->window->draw(basInvers2);
	this->window->draw(hautSens1);
	this->window->draw(hautSens2);
	this->window->draw(hautInvers1);
	this->window->draw(hautInvers2);
}

void Game::resetGame()
{
	player->reset();
	ennemies.clear();
	projectilesPlayer.clear();
	projectilesEnnemy.clear();
	score = 0;
	textScore.setString(to_string(score));
}


