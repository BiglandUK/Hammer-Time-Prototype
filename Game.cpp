#include "Game.h"

Game::Game() : window_("Hammer Prime prototype", sf::Vector2u(800, 600))
{
	clock_.restart();
	srand(static_cast<unsigned int>(std::time(0)));

}

Game::~Game() {

}

sf::Time Game::GetElapsed() {
	return clock_.getElapsedTime();
}

void Game::RestartClock() {
	elapsedTime_ = clock_.restart();
}

Window& Game::GetWindow() { return window_; }

void Game::Update() {
	sf::Event event;
	while (window_.GetRenderWindow().pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window_.Close();
		}
		if (event.type == sf::Event::LostFocus) {
			window_.LostFocus();
		}
		else if (event.type == sf::Event::GainedFocus) {
			window_.GainedFocus();
		}
		sf::Vector2i mousePos = sf::Mouse::getPosition(window_.GetRenderWindow());
		bool mouseAmongBlocks = blockManager_.Update(mousePos);
		bool mouseAmongHammers = false;
		if (!mouseAmongBlocks)
			mouseAmongHammers = hammerManager_.Update(mousePos);
		// mouse button released
		if (event.type == sf::Event::MouseButtonReleased) {
			if (event.mouseButton.button == sf::Mouse::Right) {
				if (mouseAmongBlocks) {
					blockManager_.SelectBlock(mousePos);
				}
				else if (mouseAmongHammers) {
					hammerManager_.SelectHammer();
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Left) {
				if (mouseAmongBlocks) {
					// select block
					blockManager_.SelectBlock(mousePos);
					HitBlock();
				}
			}
		}
	}

}

void Game::Render() {
	window_.BeginDraw();
	// Render here
	blockManager_.Draw(window_.GetRenderWindow());
	hammerManager_.Draw(window_.GetRenderWindow());
	window_.EndDraw();
}

void Game::LateUpdate() {
	RestartClock();
}

void Game::HitBlock() {
	// Is there an active hammer?
	HammerValue hv = hammerManager_.SelectedHammer();
	
	if (hv == 0) // no hammer, so quit now.
		return;
	hammerManager_.UseHammer(hv);

	unsigned int result = blockManager_.HitBlock(hv);
	if (Block::IsPrime(result)) {
		hammerManager_.AddHammer(result);
	}
}