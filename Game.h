#pragma once
#include <iostream>
#include <SFML\System\Time.hpp>
#include "Window.h"
#include "Block.h"
#include "Hammer.h"

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();

	Window& GetWindow();

private:
	void RestartClock();
	

	sf::Clock clock_;
	sf::Time elapsedTime_;
	Window window_;

	BlockMapManager blockManager_;
	HammerManager hammerManager_;

};