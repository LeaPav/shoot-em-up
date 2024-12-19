#pragma once
#include "stdafx.h"
class Win
{
private:
	Font fontWin;
	Text scoreText;
	Text WinText;
	Text restartButton;
	Text mainMenuButton;

	int initFont();
	void initBouton();

	Clock mouseCooldownClock;
	const Time mouseCooldown = milliseconds(150);
public:
	Win();

	int handleInput(RenderWindow& window, const Event& event);
	void handleMouseHover(const RenderWindow& window);
	void render(RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
	void setScore(int score, int killStreak);
};

