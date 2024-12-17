#include "Win.h"



Win::Win()
{
    initFont();
    initBouton();
}
/////////////////////////////////////////////Initialisation////////////////////////////////////////////
int Win::initFont()
{
    if (!fontWin.loadFromFile("assets/font/fontpause.ttf"));
}

void Win::initBouton()
{
    WinText.setFont(fontWin);
    WinText.setString("WIN");
    WinText.setCharacterSize(100);
    FloatRect WinButtonBounds = WinText.getLocalBounds();
    float x = (1920 / 2.f) - (WinButtonBounds.width / 2.f) - WinButtonBounds.left;
    WinText.setPosition(x, 200);
    WinText.setFillColor(Color(255, 235, 108));

    restartButton.setFont(fontWin);
    restartButton.setString("Rejouer");
    restartButton.setCharacterSize(30);
    FloatRect restartButtonBounds = restartButton.getLocalBounds();
    float xRestart = (1920 / 2.f) - (restartButtonBounds.width / 2.f) - restartButtonBounds.left;
    restartButton.setPosition(xRestart, 500);
    restartButton.setFillColor(Color(172, 27, 4));

    mainMenuButton.setFont(fontWin);
    mainMenuButton.setString("Retour au menu");
    mainMenuButton.setCharacterSize(30);
    FloatRect mainMenuButtonBounds = mainMenuButton.getLocalBounds();
    float xMenu = (1920 / 2.f) - (mainMenuButtonBounds.width / 2.f) - mainMenuButtonBounds.left;
    mainMenuButton.setPosition(xMenu, 600);
    mainMenuButton.setFillColor(Color(172, 27, 4));

    scoreText.setFont(fontWin);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(Color::White);
}
///////////////////////////////////////////Boutons/////////////////////////////////////////////////////
int Win::handleInput(RenderWindow& window, const Event& event)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        if (!isCooldownActive()) {
            Vector2i mousePos = Mouse::getPosition(window);
            if (restartButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                resetCooldown();
                return 1;
            }
            if (mainMenuButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                resetCooldown();
                return 2;
            }
        }
    }
}

void Win::handleMouseHover(const RenderWindow& window)
{
    Vector2i mousePos = Mouse::getPosition(window);

    if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        restartButton.setFillColor(Color(255, 235, 108));
    }
    else {
        restartButton.setFillColor(Color::White);
    }
    if (mainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
        mainMenuButton.setFillColor(Color(255, 235, 108));
    }
    else {
        mainMenuButton.setFillColor(Color::White);
    }

}
//////////////////////////////////////////Affichage////////////////////////////////////////////////
void Win::render(RenderWindow& window)
{
    window.draw(WinText);
    window.draw(scoreText);
    window.draw(restartButton);
    window.draw(mainMenuButton);
}

bool Win::isCooldownActive()
{
    return mouseCooldownClock.getElapsedTime() < mouseCooldown;
}

void Win::resetCooldown()
{
    mouseCooldownClock.restart();
}

void Win::setScore(int score,int killStreak)
{
    score = score + 555 + (50 * killStreak);
    
    scoreText.setString("Score : " + to_string(score));
    FloatRect scoreTextBounds = scoreText.getLocalBounds();
    float x = (1920 / 2.f) - (scoreTextBounds.width / 2.f) - scoreTextBounds.left;
    scoreText.setPosition(x, 350);
}
