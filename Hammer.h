#pragma once
#include <map>
#include <SFML/Graphics.hpp>

using HammerHealth = unsigned int;
using HammerValue = unsigned int;

class Hammer {
private:
	HammerValue value_;
	HammerHealth health_;
public:
	Hammer(HammerValue value);
	
	HammerValue GetValue() const;
	HammerHealth GetHealth() const;
	void Strike(); // Hammer is used to hit a block

};

using ActiveHammers = std::map<HammerValue, HammerHealth>;
using HammerInventory = std::map<HammerValue, unsigned int>;

class HammerManager {
private:
	ActiveHammers activeHammers_;
	HammerInventory hammerInventory_;
	HammerValue selectedHammer_; // the hammer currently selected. 0 means no hammer.

	sf::Texture hammerTexture_;
	sf::Sprite hammerSprite_;
	sf::Font font_;

public:
	HammerManager();

	void AddHammer(HammerValue newHammer);
	void UseHammer(HammerValue hammer);
	
	void Draw(sf::RenderWindow& window);
};
