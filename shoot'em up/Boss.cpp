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

Boss::Boss() /*: hp(100), isActive(false), shootSpeed(2.f)*/
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
    if (recBoss.getPosition().x > 1400) {
        recBoss.move(-10.f, 0.f);
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
