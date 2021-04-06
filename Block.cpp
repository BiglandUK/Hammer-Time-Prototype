#include "Block.h"

// Block
Block::Block(unsigned int initialValue, unsigned int width, unsigned int length)
	: value_(initialValue), width_(width), length_(length)
{}

unsigned int Block::GetValue() const { return value_; }
unsigned int Block::GetLength() const { return length_; }
unsigned int Block::GetWidth() const { return width_; }

void Block::SetLength(unsigned int length) { length_ = length; }
void Block::SetWidth(unsigned int width) { width_ = width; }

// BlockMapManager
BlockMapManager::BlockMapManager() {
	font_.loadFromFile("arial.ttf");

	// Create empty 5×5 map
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));
	blockMap_.push_back(std::vector<BlockID>(5, 0));

	// create list of blocks
	blockList_.emplace(10, Block(4));
	blockList_.emplace(11, Block(8));
	blockList_.emplace(12, Block(16));
	blockList_.emplace(13, Block(420));
	blockList_.emplace(14, Block(1024,2,2));
	blockList_.emplace(15, Block(36));
	blockList_.emplace(16, Block(9));

	//Place blocks on map
	blockMap_[0][0] = 10;
	blockMap_[0][1] = 11;
	blockMap_[0][2] = 12;
	blockMap_[0][3] = 13;
	blockMap_[3][0] = 15;
	blockMap_[3][1] = 14;
	blockMap_[3][2] = 1; // denotes this part of the map is part of a larger block
	blockMap_[4][1] = 1;
	blockMap_[4][2] = 1;
	blockMap_[4][3] = 16;
}

void BlockMapManager::Draw(sf::RenderWindow& window) {
	float bWidth = 50.0f;
	float bLength = 25.0f;
	float bHorizontalGap = 5.0f;
	float bVerticalGap = 5.0f;
	sf::Text text;
	text.setFont(font_);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(22);

	sf::RectangleShape block(sf::Vector2f(bWidth, bLength));
	block.setFillColor(sf::Color(182, 192, 0));
	float x = 100.0f;
	float y = 100.0f;
	block.setPosition(x, y);
	for (int j = 0; j < 5; ++j) {
		x = 100.0f;
		y += (bLength + 5.0f); // blocks have a 5.0 pixel gap between them
		for (int i = 0; i < 5; ++i)
		{
			x += (bWidth + 5.0f); // blocks have a 5.0 pixel gap between them
			block.setPosition(x, y);
			
			// get the id from the map and look up the block in the block list.
			auto itr = blockList_.find(blockMap_[j][i]);
			
			// If there isn't one (that part of the map is empty), don't draw anything.
			if (itr == blockList_.end())
				continue;

			// Set size
			unsigned int w = itr->second.GetWidth();
			unsigned int l = itr->second.GetLength();
			float blockWidth = bWidth * w + ((w-1)*bHorizontalGap);
			float blockLength = bLength * l + ((l - 1) * bVerticalGap);
			block.setSize(sf::Vector2f(blockWidth, blockLength));

			std::string blockValue = std::to_string(itr->second.GetValue()); // get the block's value
			text.setString(blockValue);
			// centre the text on the block
			sf::FloatRect textBounds = text.getGlobalBounds();
			float widthOffset = (blockWidth - textBounds.width) / 2.0f;
			float heightOffset = (blockLength - textBounds.height-10.0f)/2.0f; // the 10.0f here is fudge value.
			text.setPosition(x + widthOffset, y+heightOffset);

			// Render block and value
			window.draw(block);
			window.draw(text);

		}
	}
}