#include "Window.h"

Window::Window() {
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& title, const sf::Vector2u& size) {
	Setup(title, size);
}

Window::~Window() { window_.close(); }

void Window::Setup(const std::string& title, const sf::Vector2u& size) {
	windowTitle_ = title;
	windowSize_ = size;
	isFullscreen_ = false;
	isDone_ = false;
	isFocussed_ = true;

	Create();
}

void Window::Create() {
	sf::Uint32 style = sf::Style::Default;
	if (isFullscreen_) { style = sf::Style::Fullscreen; }

	window_.create(sf::VideoMode(windowSize_.x, windowSize_.y, 32), windowTitle_, style);
}

void Window::BeginDraw() {
	window_.clear(sf::Color::White);
}

void Window::EndDraw() { window_.display(); }

void Window::Update() {
	sf::Event event;
	while (window_.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			isDone_ = true;
		}
		if (event.type == sf::Event::LostFocus) {
			isFocussed_ = false;
		}
		else if (event.type == sf::Event::GainedFocus) {
			isFocussed_ = true;
		}
		// mouse button released
        if(event.type == sf::Event::MouseButtonReleased){
			if (event.mouseButton.button == sf::Mouse::Left)
				int f = 0;
		}

	}
}

bool Window::IsDone() { return isDone_; }

bool Window::IsFullscreen(){ return isFullscreen_; }

bool Window::IsFocussed() { return isFocussed_; }

void Window::Destroy() { window_.close(); }

void Window::ToggleFullscreen() {
	isFullscreen_ = !isFullscreen_;
	Destroy();
	Create();
}

void Window::Close() {
	isDone_ = true;
}

void Window::LostFocus() {
	isFocussed_ = false;
}

void Window::GainedFocus() {
	isFocussed_ = true;
}

sf::RenderWindow& Window::GetRenderWindow() {
	return window_;
}

sf::Vector2u Window::GetWindowSize() {
	return windowSize_;
}

sf::FloatRect Window::GetViewSpace() {
	sf::Vector2f viewCentre(window_.getView().getCenter());
	sf::Vector2f viewSize(window_.getView().getSize());
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCentre - viewSizeHalf, viewSize);
	return viewSpace;
}
