#include "Game.h"

int Game::initSprite()
{
	if (!this->texture.loadFromFile("test.png"));
	return -1;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initTexture()
{
	this->spriteMap.setTexture(this->texture);
	this->spriteMap.setPosition(0, 0);
}

void Game::initWindow()
{
	this->videoMode.width = mapWidth;
	this->videoMode.height = mapHeight;
	this->window = new RenderWindow(this->videoMode, "StarWater", Style::Fullscreen);
	this->window->setFramerateLimit(60);
}

void Game::initScore()
{
	if (!font.loadFromFile("assets/test.ttf")) {
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
	
	MovementType randomType = static_cast<MovementType>(rand() % 2);
	Ennemy* newEnnemy = new Ennemy(randomType);
	newEnnemy->setPosition(1920, rand() % this->videoMode.height);
	if (newEnnemy->destroy()) {
		delete newEnnemy;
	}
	ennemies.push_back(newEnnemy);
}

void Game::createProjectiles(float x, float y)
{
	Projectile* newProjectile = new Projectile(x, y, 15.f, 0.f);
	projectiles.push_back(newProjectile);
}

void Game::entityRender()
{
	this->player->render(*this->window);

	for (auto& ennemy : ennemies) {
		ennemy->render(*this->window);
	}
}

Game::Game()
{
	//this->initSprite();
	//this->initTexture();
	this->initWindow();
	this->initPlayer();
	this->initScore();
}

Game::~Game()
{
	delete this->window;

}

const bool Game::windowIsOpen()
{
	return this->window->isOpen();
}

void Game::playerUpdate()
{
	this->player->playerUpdate();
}

void Game::projectileUpdate()
{
	for (auto& projectile : projectiles) {
		projectile->update();
	}
}

void Game::ennemyUpdate()
{

	static int timer = 0; //utilisatin de static pour pas qu'il se remette à 0 à chaque appel de la fonction
	const int spawnInterval = 60;

	for (auto& ennemy : ennemies) {
		ennemy->update();
	}

	timer++;
	if (timer >= spawnInterval) {
		this->createEnnemy();
		timer = 0;
	}
}

void Game::projectileRender()
{
	for (auto& projectile : projectiles) {
		projectile->render(*this->window);
	}
}

void Game::checkCollisions()
{
	vector<Projectile*> projectilesToRemove;
	vector<Ennemy*> ennemiesToRemove;

	for (auto& projectile : projectiles) {
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

	for (auto& ennemy : ennemies) {
		if (ennemy->getGlobalBounds().intersects(player->getGlobalBounds())) {
			player->damage(1);
			ennemiesToRemove.push_back(ennemy);
		}
	}

	for (auto& projectile : projectilesToRemove) {
		projectiles.erase(remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
		delete projectile; 
	}
	for (auto& ennemy : ennemiesToRemove) {
		ennemies.erase(remove(ennemies.begin(), ennemies.end(), ennemy), ennemies.end());
		delete ennemy; 
	}

	projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [](Projectile* p) {
		if (p->outOfScreen()) {
			delete p;
			return true;
		}
		return false;
		}),
		projectiles.end()
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


void Game::update()
{
	Event event;

	while (this->window->pollEvent(event)) {
		if (event.type == Event::Closed)
			this->window->close();
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			this->window->close();
		}
	}

	this->playerUpdate();
	this->projectileUpdate();
	this->ennemyUpdate();
	this->checkCollisions();

	if (player->isDead()) {
		cout << "Game over";
		this->window->close();
		return;
	}
	this->shoot();

}

void Game::render()
{
	this->window->clear();
	this->entityRender();
	this->projectileRender();

	this->window->draw(textScore);
	this->window ->display();

}
