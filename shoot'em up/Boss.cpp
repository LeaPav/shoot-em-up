#include "Boss.h"

Boss::Boss(float x, float y) : hp(100), isActive(false), shootSpeed(1.f), velocity(Vector2f(-3.5f, 2.f)), phase(1), robotHp1(3), robotHp2(3), speedX(x), speedY(y),
firstMove(true)
{
    this->initSprite();
    this->initTexture();
    this->initHealthBar();

}

//////////////////////////////////initialisation///////////////////////////////////////////////


void Boss::initSprite()
{
    // initilisation des textures du boss
    if (!this->boss.loadFromFile("assets/boss/Boss_sans_shield.png")) {
        cout << "Erreur";
    }

    if (!this->bossPhase2.loadFromFile("assets/boss/Boss_avec_drone_actif_new.gif")) {
        cout << "Erreur";
    }

    if (!this->bossPhaseInterHaut.loadFromFile("assets/boss/Boss_avec_drone_du_bas_actif_new.png")) {
        cout << "Erreur";
    }
    if (!this->bossPhaseInterBas.loadFromFile("assets/boss/Boss_avec_drone_actif_du_haut_new.png")) {
        cout << "Erreur";
    }
    if (!this->bossPresqueMort.loadFromFile("assets/boss/Boss_presque_mort.png")) {
        cout << "Erreur";
    }
    if (!this->robot1.loadFromFile("assets/boss/droide_du_haut.png")) {
        cout << "Erreur";
    }
    if (!this->robot2.loadFromFile("assets/boss/droide_du_bas.png")) {
        cout << "Erreur";
    }

}

void Boss::initTexture()
{
    sprite.setTexture(boss);
    sprite.setPosition(2500.f, 100.f);

    spriteRobot1.setTexture(robot1);
    spriteRobot2.setTexture(robot2);
}


//////////////////////////////////actualisation////////////////////////////////////////////////
 
void Boss::render(RenderTarget& target)
{
    if (hp > 0) {
        target.draw(this->sprite);
   }
  
    for (const auto& projectile : projectiles) {
        target.draw(projectile);
    }
    if (phase == 2) {
        sprite.setTexture(bossPhase2);
        if (robotHp1 > 0) {
            target.draw(this->spriteRobot1);
        }
        else {
            sprite.setTexture(bossPhaseInterHaut);
        }
        if (robotHp2 > 0) {
            target.draw(this->spriteRobot2);
        }
        else {
            sprite.setTexture(bossPhaseInterBas);
        }
    }
    if (phase == 3 && hp > 0) {
        sprite.setTexture(bossPresqueMort);
    }

}



void Boss::update()
{
    movement(x, y);

    if (hp <= 50 && phase == 1) {
        phase = 2;
    }
    if (robotHp1 <= 0 && robotHp2 <= 0 && phase == 2) {
        phase = 3;
        shootSpeed = 0.5f;
        velocity.x *= 2;
        velocity.y *= 2;
    }

    if (phase == 2) {
        handleRobots();
    }
    if (hp <= 0) {
        sprite.setPosition(0, -500);
    }
    if (robotHp1 <= 0) {
        spriteRobot1.setPosition(0, -500);
    }
    if (robotHp2 <= 0) {
        spriteRobot2.setPosition(0, -500);
    }
}

void Boss::reset()
{
    phase = 1;
    isActive = false;
    firstMove = true;
    this->sprite.setTexture(boss);
    this->sprite.setPosition(2500.f, 100.f);
    hp = 100;
    robotHp1 = 3;
    robotHp2 = 3;

    velocity.x = 3.5f;
    velocity.y = 2.f;

}
/////////////////////////////////geter//////////////////////////////////

const Vector2f Boss::getPosition() const
{
    return this->sprite.getPosition();
}

int Boss::getHp()
{
    return hp;
}

FloatRect Boss::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

int Boss::getPhase() const
{
    return phase;
}

Vector2f Boss::getRobot1Position() const
{
    return spriteRobot1.getPosition();
}

Vector2f Boss::getRobot2Position() const
{
    return spriteRobot2.getPosition();
}

FloatRect Boss::getRobot1Bounds() const
{
    return spriteRobot1.getGlobalBounds();
}

FloatRect Boss::getRobot2Bounds() const
{
    return spriteRobot2.getGlobalBounds();
}

////////////////////////////////movement////////////////////////////////

void Boss::movement(int x, int y)
{

  //  static Vector2f direction = velocity;
    static int frameCounter = 0;
    float speed = 3.5f;

    if (firstMove) {
        if (sprite.getPosition().x > 1600) {
            sprite.move(-speed, 0.f);
        }
        else {
            firstMove = false;
        }
    }
    else {
        sprite.move(velocity);
        if (sprite.getPosition().x < 1000 || sprite.getPosition().x  > 1600) {
            velocity.x = -velocity.x;
        }
        if (sprite.getPosition().y < 0 || sprite.getPosition().y  > 860) {
            velocity.y = -velocity.y;
        }
    }
    if (phase == 2) {
        spriteRobot1.setPosition(sprite.getPosition().x + 120, sprite.getPosition().y - 100);
        spriteRobot2.setPosition(sprite.getPosition().x + 120, sprite.getPosition().y + 250);
    }

}

////////////////////////////////damage//////////////////////////////////

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

bool Boss::shouldShoot() const
{
    return shootClock.getElapsedTime().asSeconds() > shootSpeed;
}


void Boss::restartShootClock()
{
    shootClock.restart();
}

////////////////////////////////droide/////////////////////////////////

bool Boss::isRobot1Active() const
{
    return robotHp1 > 0;
}

bool Boss::isRobot2Active() const
{
    return robotHp2 > 0;
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

///////////////////////////////life in game///////////////////////////

bool Boss::canSpawn(int bossScore, int spawnBoss)
{
    if (bossScore >= spawnBoss) {
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

void Boss::initHealthBar()   // santé et barre de vie
{
    this->maxHp = 100;
    this->hp = this->maxHp;
    this->healthBar.setSize(Vector2f(800.f, 20.f));
    this->healthBar.setFillColor(Color(255, 0, 0));

    this->backgroundHealthBar.setSize(Vector2f(800.f, 20.f));
    this->backgroundHealthBar.setFillColor(Color(117, 117, 117));
}

void Boss::udpateHealthBar()
{
    float healthPercentage = static_cast<float>(this->hp) / static_cast<float>(this->maxHp);
    this->healthBar.setSize(Vector2f(800.f * healthPercentage, 20.f));
}

void Boss::renderHealthBar(RenderTarget& target)
{
    this->backgroundHealthBar.setPosition(1100.f, 1050.f);
    this->healthBar.setPosition(1100.f, 1050.f);

    target.draw(this->backgroundHealthBar);
    target.draw(this->healthBar);

}
