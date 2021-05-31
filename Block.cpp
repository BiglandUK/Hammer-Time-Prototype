#include "Block.h"

// Block
Block::Block(unsigned int initialValue, unsigned int width, unsigned int height)
	: value_(initialValue), width_(width), height_(height), canBeHit_(false)
{}

unsigned int Block::GetValue() const { return value_; }
unsigned int Block::GetHeight() const { return height_; }
unsigned int Block::GetWidth() const { return width_; }
sf::Vector2i Block::GetPosition() const { return position_; }
bool Block::CanBeHit() const { return canBeHit_; }

void Block::SetValue(unsigned int value) { value_ = value; }
void Block::SetHeight(unsigned int height) { height_ = height; }
void Block::SetWidth(unsigned int width) { width_ = width; }
void Block::SetSize(unsigned int width, unsigned int height) { SetWidth(width); SetHeight(height); }
void Block::SetPosition(const sf::Vector2i& position){ SetPosition(position.x, position.y); }
void Block::SetPosition(int x, int y){ position_.x = x; position_.y = y; }

void Block::ToggleHitStatus() { canBeHit_ = !canBeHit_; }
void Block::MakeHittable() { canBeHit_ = true; }
void Block::MakeUnHittable() { canBeHit_ = false; }

void Block::StrikeBlock(unsigned int hammerValue) {
	value_ /= hammerValue;
}

//static method
bool Block::IsPrime(unsigned int number) {
	if (number == 2) // special case.
		return true;
	for (auto i = 2; i < sqrtl(number) + 1; ++i) {
		if (number % i == 0)
			return false;
	}
	return true;
}

// BlockMapManager
BlockMapManager::BlockMapManager()
:hoverBlockID_(0), selectedBlockID_(0)
{
	font_.loadFromFile("arial.ttf");

	// Create empty 5×5 map
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));

	// create list of blocks
	int x = 0;
	int y = 0;
	AddBlockToList(4, 10, x, y);
	selectedBlockID_ = 10;
	AddBlockToList(8, 11, x, y);
	AddBlockToList(4, 12, x, y);
	AddBlockToList(8, 13, x, y);
	AddBlockToList(4, 14, x, y);
	AddBlockToList(32,15, x, y);
	AddBlockToList(6, 16, x, y); 
	AddBlockToList(9, 17, x, y);
	AddBlockToList(12,18, x, y); 
	AddBlockToList(16,19, x, y); 
	AddBlockToList(4, 20, x, y); 
	AddBlockToList(9, 21, x, y);
	AddBlockToList(100,22, x, y); 
	AddBlockToList(9, 23, x, y); 
	AddBlockToList(4, 24, x, y); 
	AddBlockToList(15,25, x, y); 
	AddBlockToList(12,26, x, y); 
	AddBlockToList(9, 27, x, y); 
	AddBlockToList(6, 28, x, y); 
	AddBlockToList(16, 29, x, y); 
	AddBlockToList(4, 30, x, y); 
	AddBlockToList(8, 31, x, y); 
	AddBlockToList(4, 32, x, y); 
	AddBlockToList(8, 33, x, y); 
	//IDs 0-9 reserved
	// 0 = no block

}

void BlockMapManager::AddBlockToList(unsigned int value, BlockID id, int& posX, int& posY) {
	Block b{ value };
	unsigned int width{ 1 };
	unsigned int height{ 1 };
	if (value > 99) { width = 2; }
	b.SetSize(width, height);
	b.SetPosition(posX, posY);
	// add to blocklist
	blockList_.emplace(id, b); 
	// add to blockmap; TODO: check there's nothing there already
	for (auto i = posX; i < posX + width; ++i) {
		for (auto j = posY; j < posY + height; ++j) {
			blockMap_[i][j] = id;
		}
	}

	// determine next position TODO: cater for objects with height greater than 1
	posX += width;
	if (posX >= 5) {
		posX = 0;
		posY += 1;
	}
}

sf::Vector2i BlockMapManager::FindSpaceInMap(unsigned int width, unsigned int height) {
	for (int i = 0; i < 5-(width-1); ++i) {
		for (int j = 0; j < 5-(height-1); ++j) {
			if (blockMap_[i][j] > 0)
				continue;
			else
				return sf::Vector2i(i, j);
		}
	}
	return sf::Vector2i(5, 5); //failed to find space
}

void BlockMapManager::Draw(sf::RenderWindow& window) {	
	sf::Text text; // text object for displaying the value
	text.setFont(font_);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(22);

	// shape object for the block
	sf::RectangleShape block(sf::Vector2f(UNITBLOCKWIDTH, UNITBLOCKHEIGHT));
	block.setFillColor(sf::Color(182, 192, 0));
	float x = MAPSTARTX;
	float y = MAPSTARTY;

	//Hover & Selected surround
	sf::RectangleShape highlight(sf::Vector2f(UNITBLOCKHEIGHT + 2 * HORIZONTALGAP, UNITBLOCKWIDTH + 2 * VERTICALGAP));

	for (const auto &b : blockList_) {
		sf::Vector2i pos = b.second.GetPosition();
		x = MAPSTARTX + pos.x * (UNITBLOCKWIDTH + HORIZONTALGAP);
		y = MAPSTARTY + pos.y * (UNITBLOCKHEIGHT + VERTICALGAP);
		block.setPosition(x, y);
		int width = b.second.GetWidth() * (UNITBLOCKWIDTH) + (b.second.GetWidth()-1) * HORIZONTALGAP;
		int height = b.second.GetHeight() * (UNITBLOCKHEIGHT)+(b.second.GetHeight() - 1) * VERTICALGAP;;
		block.setSize(sf::Vector2f(width, height));

		std::string blockValue = std::to_string(b.second.GetValue()); // get the block's value
		text.setString(blockValue);
		// centre the text on the block
		sf::FloatRect textBounds = text.getGlobalBounds();
		float widthOffset = (width - textBounds.width) / 2.0f;
		float heightOffset = (height - textBounds.height-10.0f)/2.0f; // the 10.0f here is fudge value.
		text.setPosition(x + widthOffset, y+heightOffset);

		// Render highlight for hover
		if (b.first == hoverBlockID_) {
			highlight.setFillColor(sf::Color(230, 230, 100));
			highlight.setSize(sf::Vector2f(width + 2*HORIZONTALGAP, height + 2*VERTICALGAP));
			highlight.setPosition(x - HORIZONTALGAP, y - VERTICALGAP);
			window.draw(highlight);
		}
		if (b.first == selectedBlockID_) {
			highlight.setFillColor(sf::Color(200, 0, 0, 200));
			highlight.setSize(sf::Vector2f(width + 2 * HORIZONTALGAP, height + 2 * VERTICALGAP));
			highlight.setPosition(x - (HORIZONTALGAP), y - (VERTICALGAP));
			window.draw(highlight);
		}
		// Render block and value
		window.draw(block);
		window.draw(text);
	}
}

bool BlockMapManager::Update(const sf::Vector2i& mousePos) {
	// Find which block is under the mouse cursor
	BlockID hover = IdentifyBlockUnderCursor(mousePos);
	if (hover == 0) {
		hoverBlockID_ = hover;
		return false;
	}
	hoverBlockID_ = hover;
	return true;
}

void BlockMapManager::SelectBlock(const sf::Vector2i& mousePos) {
	BlockID select = IdentifyBlockUnderCursor(mousePos);
	if(select>0)
		selectedBlockID_ = select;
}
	
BlockID BlockMapManager::IdentifyBlockUnderCursor(const sf::Vector2i & mousePos) {
	int x = MAPSTARTX;
	int y = MAPSTARTY;

	for (const auto& b : blockList_) {
		sf::Vector2i pos = b.second.GetPosition();
		x = MAPSTARTX + pos.x * (UNITBLOCKWIDTH + HORIZONTALGAP);
		y = MAPSTARTY + pos.y * (UNITBLOCKHEIGHT + VERTICALGAP);
		int width = b.second.GetWidth() * (UNITBLOCKWIDTH)+(b.second.GetWidth() - 1) * HORIZONTALGAP;
		int height = b.second.GetHeight() * (UNITBLOCKHEIGHT)+(b.second.GetHeight() - 1) * VERTICALGAP;;
		sf::IntRect blockBounds(x, y, width, height);
		if (blockBounds.contains(mousePos)) {
			return b.first;
		}
	}

	return 0;
}

unsigned int BlockMapManager::HitBlock(unsigned int hammerValue) {
	auto& b = blockList_.at(selectedBlockID_);
	unsigned int bv = b.GetValue();
	if (bv % hammerValue != 0) // hammer does not divide into block exactly.
		return 0;

	// divide block value by hammer
	b.StrikeBlock(hammerValue);
	unsigned int newBlockValue = b.GetValue();
	if (Block::IsPrime(b.GetValue())) {
		// block has left a prime.
		b.SetValue(0);
		blockList_.erase(selectedBlockID_);
		return newBlockValue;
	}
	else if (b.GetValue() == 1) { // block reduced to 1.
		//increase coins/score by 1
		b.SetValue(0);
		blockList_.erase(selectedBlockID_);
		return newBlockValue;
	}
	return newBlockValue;

}
