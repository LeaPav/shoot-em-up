#include "Boss.h"

void Boss::initSprite()
{/*
    if (!this->boss.loadFromFile("test.png"))
    return -1;*/

    recBoss.setSize(Vector2f(350.f, 250.f));
    recBoss.setPosition(2000.f, 100.f);

    //recRobot.setSize(Vector2f(100.f, 100.f));
    //recRobot.setPosition(675.f, 375.f);
}

void Boss::initTexture()
{
    sprite.setTexture(boss);

}

Boss::Boss() : hp(100), isActive(false), shootSpeed(2.f), velocity(Vector2f(-5.f, 2.f))
{
    this->initSprite();
   // initTexture();
 
}

void Boss::takeDamage(int damage)
{
    hp -= damage;
    if (hp <= 0) {
        isActive = false;
    }
}

void Boss::movement(int x, int y)
{
    if (recBoss.getPosition().x > 1900) {
        recBoss.move(-10.f, 0.f);
    }
    else {
        recBoss.move(velocity);
        if (recBoss.getPosition().x <= 1000 || recBoss.getPosition().x >= 1900) {
            velocity.x = -velocity.x;
        } 
        if (recBoss.getPosition().y <= 0 || recBoss.getPosition().y >= 830) {
            velocity.y = -velocity.y;
        }
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
    target.draw(this->recRobot);
}

FloatRect Boss::getGlobalBounds() const
{
    return this->recBoss.getGlobalBounds();
}

void Boss::update()
{
    movement(x, y);
}

bool Boss::canSpawn(int bossScore)
{
    return bossScore >= 5;
}

void Boss::reset()
{
    this->recBoss.setPosition(2000.f, 100.f);
    hp = 100;
}
