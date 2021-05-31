#pragma once
#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Window {
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();

	bool IsDone();
	bool IsFullscreen();
	bool IsFocussed();

	void ToggleFullscreen();
	void Close();
	void LostFocus();
	void GainedFocus();
	void Destroy();

	sf::RenderWindow& GetRenderWindow();
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();



private:
	void Setup(const std::string& title, const sf::Vector2u& size);
	void Create();

	sf::RenderWindow window_;
	sf::Vector2u windowSize_;
	std::string windowTitle_;


	bool isDone_;
	bool isFullscreen_;
	bool isFocussed_;
};