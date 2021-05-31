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
	activeHammers_.emplace(2, 2); // create a 2-Hammer with 2 health
	hammerInventory_.emplace(2, 5); // create a stock of 5 reserve 2-hammers
	activeHammers_.emplace(3, 3); //  create a 3-hammer with 3 health
	selectedHammer_ = 2; //  select the 2-hammer
	hammerTexture_.loadFromFile("Graphics/Hammer.png");
	hammerSprite_.setTexture(hammerTexture_);
	hammerSprite_.setScale(sf::Vector2f(0.5f, 0.5f));
	

	font_.loadFromFile("Arial.ttf");
}

void HammerManager::AddHammer(HammerValue value) {
	if (value == 0)return;
	//see if hammer already exists. if so, just increase amount.
	auto i = hammerInventory_.find(value);
	if (i == hammerInventory_.end()) {// otherwise, add a new hammer.
		hammerInventory_.emplace(value, 1);
		activeHammers_.emplace(value, 0);
	}
	else {
		++(i->second);
	}
	
}

void HammerManager::UseHammer(HammerValue hammer)
{
	if (activeHammers_.at(hammer) == 0)
		return;
	--activeHammers_.at(hammer);
	if (activeHammers_.at(hammer) == 0) {
		if (hammerInventory_.at(hammer) > 0) {
			--hammerInventory_.at(hammer);
			activeHammers_.at(hammer) = hammer;
		}
		else {
			selectedHammer_ = 0;
		}
	}
	
}

void HammerManager::SelectHammer() {
	selectedHammer_ = hoverHammer_;
	if (activeHammers_.at(selectedHammer_) == 0) {
		if (hammerInventory_.at(selectedHammer_) > 0) {
			activeHammers_.at(selectedHammer_) = selectedHammer_;
			--hammerInventory_.at(selectedHammer_);
		}
		else {
			selectedHammer_ = 0;
		}
	}
}

HammerValue HammerManager::SelectedHammer() const {
	return selectedHammer_;
}

void HammerManager::Draw(sf::RenderWindow& window) {
	float x = 500.0f;
	float y = 100.0f;
	for (auto hammer : hammerInventory_){

		float health = 0.f;
		float value = hammer.first;
		if (activeHammers_.at(hammer.first) != 0 ) {
			health = activeHammers_.at(hammer.first);
		}
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
		txt.setString(std::to_string(hammer.first));
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

bool HammerManager::Update(const sf::Vector2i& mousePos)
{
	hoverHammer_ = IdentifyHammerUnderCursor(mousePos);
	if (hoverHammer_ > 0) {
		return true;
	}
	hoverHammer_ = 0;
	return false;
}

unsigned int HammerManager::IdentifyHammerUnderCursor(const sf::Vector2i& mousePos)
{
	float x = 500.0f;
	float y = 100.0f;
	for (auto hammer : activeHammers_) {

		sf::IntRect bounds(x, y, 50.0f, 50.0f); //TODO: unfudge height/width values
		if (bounds.contains(mousePos)) {
			return hammer.first;
		}
		// Advance draw position for next hammer
		y += 55.0f;
	}
	return 0;
}
