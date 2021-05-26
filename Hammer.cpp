#include "Hammer.h"
#include <string>

Hammer::Hammer(HammerValue value)
	:	value_(value), health_(value)
{}

HammerValue Hammer::GetValue() const {
	return value_;
}

HammerHealth Hammer::GetHealth() const {
	return health_;
}

void Hammer::Strike() {
	--health_;
	if (health_ < 0) health_ = 0;
}

// HammerManager
HammerManager::HammerManager()
{
	activeHammers_.emplace(2, 2);
	hammerInventory_.emplace(2, 5);
	activeHammers_.emplace(3, 3);
	selectedHammer_ = 2;
	hammerTexture_.loadFromFile("Graphics/Hammer.png");
	hammerSprite_.setTexture(hammerTexture_);
	hammerSprite_.setScale(sf::Vector2f(0.5f, 0.5f));
	

	font_.loadFromFile("Arial.ttf");
}

void HammerManager::AddHammer(HammerValue value) {
	//see if hammer already exists. if so, just increase amount.
	// otherwise, add a new hammer.
}

void HammerManager::Draw(sf::RenderWindow& window) {
	float x = 500.0f;
	float y = 100.0f;
	for (auto i = activeHammers_.begin();
		i != activeHammers_.end();
		++i) {

		float health = i->second;
		float value = i->first;
		
		// Display hammer icon
		hammerSprite_.setPosition(x, y);
		uint8_t trans = value == selectedHammer_ ? 255 : 50; // selected hammer shown darker than others
		hammerSprite_.setColor(sf::Color(255, 255, 255, trans));
		window.draw(hammerSprite_);

		// display health gauge on hammer
		sf::RectangleShape rect(sf::Vector2f(50.0f * (health / value), 20.0f));
		rect.setFillColor(sf::Color(0, 255, 0, 100));
		rect.setPosition(x, y + 30.0f);
		window.draw(rect);

		// Display value on the hammer
		sf::Text txt;
		txt.setFont(font_);
		txt.setString(std::to_string(i->first));
		txt.setCharacterSize(30);
		txt.setPosition(x, y);
		txt.setFillColor(sf::Color::Black);
		window.draw(txt);

		// Display reserver hammers
		auto j = hammerInventory_.find(value);
		if (j != hammerInventory_.end()) {
			txt.setString(std::to_string(j->second));
			txt.setCharacterSize(20);
			txt.setPosition(x + 60.0f, y);
			window.draw(txt);
		}

		// Advance draw position for next hammer
		y += 55.0f;
	}
}