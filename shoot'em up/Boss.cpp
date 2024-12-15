#include "Boss.h"

void Boss::initSprite()
{/*
    if (!this->boss.loadFromFile("test.png"))
    return -1;*/

    recBoss.setSize(Vector2f(350.f, 250.f));
    recBoss.setPosition(2000.f, 100.f);

    recRobot1.setSize(Vector2f(100.f, 100.f));
    recRobot1.setFillColor(Color::Red);
    recRobot2.setFillColor(Color::Blue);
    recRobot2.setSize(Vector2f(100.f, 100.f));
    robotHp1 = 30;
    robotHp2 = 30;
 
}

void Boss::initTexture()
{
    sprite.setTexture(boss);

}

Boss::Boss() : hp(100), isActive(false), shootSpeed(3.f), velocity(Vector2f(-5.f, 2.f)), phase(1)
{
    this->initSprite();
   // initTexture();
 
}

void Boss::takeDamage(int damage)
{
    if (this->isActive) {
        hp -= damage;
    }
    cout << "Hp boss: " << hp << endl;
    if (hp <= 0) {
        isActive = false;
    }
}

void Boss::movement(int x, int y)
{
   // int compteur = rand() % 4;
    static Vector2f direction(-5.f, 3.f);
    static int frameCounter = 0;
    float speed = 5.f;

    if (recBoss.getPosition().x > 1500) {
        recBoss.move(-speed, 0.f);
    }
    else {
        recBoss.move(direction);
        if (recBoss.getPosition().x < 1000 || recBoss.getPosition().x + recBoss.getSize().x > 1900) {
            direction.x = -direction.x; 
        }
        if (recBoss.getPosition().y < 0 || recBoss.getPosition().y + recBoss.getSize().y > 830) {
            direction.y = -direction.y; 
        }

        frameCounter++;
        if (frameCounter > 120) { 
            direction.x = (rand() % 2 == 0) ? speed : -speed; 
            direction.y = (rand() % 2 == 0) ? speed : -speed; 
            frameCounter = 0; 
        }
    }
    if (phase == 2) {
        recRobot1.setPosition(recBoss.getPosition().x, recBoss.getPosition().y - 110);
        recRobot2.setPosition(recBoss.getPosition().x, recBoss.getPosition().y + recBoss.getSize().y + 10);
    }
 
}

const Vector2f Boss::getPosition() const
{
    return this->recBoss.getPosition();
}

int Boss::getHp()
{
    return hp;
}

void Boss::render(RenderTarget& target)
{
    target.draw(this->recBoss);
    
    for (const auto& projectile : projectiles) {
        target.draw(projectile);
    }
    if (phase == 2) {
        target.draw(this->recRobot1);
        target.draw(this->recRobot2);
    }
    
}

FloatRect Boss::getGlobalBounds() const
{
    return this->recBoss.getGlobalBounds();
}

void Boss::update()
{
    movement(x, y);

    if (hp <= 50 && phase == 1) {
        phase = 2;
    }
    if (robotHp1 <= 0 && robotHp2 <= 0 && phase == 2) {
        phase = 3;
        shootSpeed = 1.0f;
        velocity.x *= 1.5;
        velocity.y *= 1.5;
    }
    
    if (phase == 2) {
        handleRobots();
    }
}

bool Boss::canSpawn(int bossScore)
{
    if (bossScore >= 5) {
        isActive = true;
        return true;
   }
    return false;
}

bool Boss::isBossActive() const
{
    return isActive;
}

bool Boss::isBossDead() const
{
    return hp <= 0;
}

void Boss::reset()
{
    this->recBoss.setPosition(2000.f, 100.f);
    hp = 100;
}

void Boss::handleRobots()
{
    if (robotHp1 <= 0) recRobot1.setSize(Vector2f(0, 0));
    if (robotHp2 <= 0) recRobot2.setSize(Vector2f(0, 0));
}

void Boss::handleBoss()
{
    recBoss.setSize(Vector2f(0, 0));
}

void Boss::shooting()
{
   
    if (shootClock.getElapsedTime().asSeconds() > shootSpeed) {
        if (phase == 1 || phase == 3) {

        RectangleShape projectile;
        projectile.setSize(Vector2f(60.f, 20.f));
        projectile.setFillColor(Color::Red);
        projectile.setPosition(recBoss.getPosition().x, recBoss.getPosition().y + recBoss.getSize().y / 2);
        projectiles.push_back(projectile);
    }
        if (phase == 2) {
            RectangleShape robotProjectile1, robotProjectile2;
            robotProjectile1.setSize(Vector2f(60.f, 20.f));
            robotProjectile2.setSize(Vector2f(60.f, 20.f));
            robotProjectile1.setFillColor(Color::Red);
            robotProjectile2.setFillColor(Color::Red);

            robotProjectile1.setPosition(recRobot1.getPosition().x, recRobot1.getPosition().y + recRobot1.getSize().y / 2);
            robotProjectile2.setPosition(recRobot2.getPosition().x, recRobot2.getPosition().y + recRobot1.getSize().y / 2);
            projectiles.push_back(robotProjectile1);
            projectiles.push_back(robotProjectile2);
        }
        shootClock.restart();
    }
    for (auto& projectile : projectiles) {
        projectile.move(-10.f, 0.f);
    }
}

bool Boss::shouldShoot() const
{
    return shootClock.getElapsedTime().asSeconds() > shootSpeed;
}

int Boss::getPhase() const
{
    return phase;
}

Vector2f Boss::getRobot1Position() const
{
    return recRobot1.getPosition();
}

Vector2f Boss::getRobot2Position() const
{
    return recRobot2.getPosition();
}

Vector2f Boss::getRobotSize() const
{
    return recRobot1.getSize();
}

void Boss::restartShootClock()
{
    shootClock.restart();
}

bool Boss::isRobot1Active() const
{
    return robotHp1 > 0;
}

bool Boss::isRobot2Active() const
{
    return robotHp2 > 0;
}

FloatRect Boss::getRobot1Bounds() const
{
    return recRobot1.getGlobalBounds();
}

FloatRect Boss::getRobot2Bounds() const
{
    return recRobot2.getGlobalBounds();
}

void Boss::damageRobot1(int damage)
{
    robotHp1 -= damage;
    cout << "Robot1 hp : " << robotHp1 << endl;
    if (robotHp1 <= 0) {
        robotHp1 = 0;
    }
}

void Boss::damageRobot2(int damage)
{
    robotHp2 -= damage;
    cout << "Robot2 hp : " << robotHp2 << endl;
    if (robotHp2 <= 0) {
        robotHp2 = 0;
    }
}

bool Boss::isRobot1Dead()
{
    return robotHp1 <= 0;
}

bool Boss::isRobot2Dead()
{
    return robotHp2 <= 0;
}
