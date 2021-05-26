#include "Game.h"

Game::Game() : window_("Hammer Prime prototype", sf::Vector2u(800, 600))
{
	clock_.restart();
	srand(time(nullptr));
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
	window_.Update();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window_.GetRenderWindow());
	blockManager_.Update(mousePos);
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