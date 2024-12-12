#pragma once
#include "stdafx.h"
class GameOver
{
private:
	Font fontOver;
	Text gameOverText;
	Text retryButton;
	Text mainMenuButton;

	int initFont();
	void initButton();

	Clock mouseCooldownClock;
	const Time mouseCooldown = milliseconds(150);
public:
	GameOver();
	int handleInput(RenderWindow& window, const Event& event);
	void handleMouseHover(const RenderWindow& window);
	void render(RenderWindow& window);

	bool isCooldownActive();
	void resetCooldown();
};

