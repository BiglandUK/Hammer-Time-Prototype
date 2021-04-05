#pragma once
#include <iostream>
#include <SFML\System\Time.hpp>
#include "Window.h"

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

};