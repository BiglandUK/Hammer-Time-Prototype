#include "Block.h"

// Block
Block::Block(unsigned int initialValue, unsigned int width, unsigned int length)
	: value_(initialValue), width_(width), length_(length), canBeHit_(false)
{}

unsigned int Block::GetValue() const { return value_; }
unsigned int Block::GetLength() const { return length_; }
unsigned int Block::GetWidth() const { return width_; }
sf::Vector2i Block::GetPosition() const { return position_; }
bool Block::CanBeHit() const { return canBeHit_; }

void Block::SetLength(unsigned int length) { length_ = length; }
void Block::SetWidth(unsigned int width) { width_ = width; }
void Block::SetPosition(const sf::Vector2i& position){ SetPosition(position.x, position.y); }
void Block::SetPosition(int x, int y){ position_.x = x; position_.y = y; }

void Block::ToggleHitStatus() { canBeHit_ = !canBeHit_; }
void Block::MakeHittable() { canBeHit_ = true; }
void Block::MakeUnHittable() { canBeHit_ = false; }

// BlockMapManager
BlockMapManager::BlockMapManager()
:hoverBlockID_(0)
{
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
	blockList_.emplace(12, Block(4));
	blockList_.emplace(13, Block(8));
	blockList_.emplace(14, Block(4));
	blockList_.emplace(15, Block(32));
	blockList_.emplace(16, Block(6));
	blockList_.emplace(17, Block(9));
	blockList_.emplace(18, Block(12));
	blockList_.emplace(19, Block(16));
	blockList_.emplace(20, Block(4));
	blockList_.emplace(21, Block(9));
	blockList_.emplace(22, Block(24));
	blockList_.emplace(23, Block(9));
	blockList_.emplace(24, Block(4));
	blockList_.emplace(25, Block(32));
	blockList_.emplace(26, Block(12));
	blockList_.emplace(27, Block(9));
	blockList_.emplace(28, Block(6));
	blockList_.emplace(29, Block(16));
	blockList_.emplace(30, Block(4));
	blockList_.emplace(31, Block(8));
	blockList_.emplace(32, Block(4));
	blockList_.emplace(33, Block(8));
	blockList_.emplace(34, Block(4));
	//IDs 0-9 reserved
	// 0 = no block
	// 1 = space taken up by a larger block
	//Place blocks on map
	blockMap_[0][0] = 10;
	blockMap_[0][1] = 11;
	blockMap_[0][2] = 12;
	blockMap_[0][3] = 13;
	blockMap_[0][4] = 14;
	blockMap_[1][0] = 15;
	blockMap_[1][1] = 16;
	blockMap_[1][2] = 17;
	blockMap_[1][3] = 18;
	blockMap_[1][4] = 19;
	blockMap_[2][0] = 20;
	blockMap_[2][1] = 21;
	blockMap_[2][2] = 22;
	blockMap_[2][3] = 23;
	blockMap_[2][4] = 24;
	blockMap_[3][0] = 25;
	blockMap_[3][1] = 26;
	blockMap_[3][2] = 27;
	blockMap_[3][3] = 28;
	blockMap_[3][4] = 29;
	blockMap_[4][0] = 30;
	blockMap_[4][1] = 31;
	blockMap_[4][2] = 32;
	blockMap_[4][3] = 33;
	blockMap_[4][4] = 34;
}

void BlockMapManager::Draw(sf::RenderWindow& window) {
	float bWidth = 50.0f; // standard block length
	float bLength = 25.0f; // block length
	float bHorizontalGap = 5.0f; // gap between blocks
	float bVerticalGap = 5.0f;
	
	sf::Text text; // text object for displaying the value
	text.setFont(font_);
	text.setFillColor(sf::Color::Black);
	text.setOutlineColor(sf::Color::Black);
	text.setCharacterSize(22);

	// shape object for the block
	sf::RectangleShape block(sf::Vector2f(bWidth, bLength));
	block.setFillColor(sf::Color(182, 192, 0));
	float x = 100.0f;
	float y = 100.0f;
	block.setPosition(x, y);

	//Hover surround
	sf::RectangleShape highlight(sf::Vector2f(bWidth + 2 * bHorizontalGap, bLength + 2 * bVerticalGap));
	highlight.setFillColor(sf::Color(230, 230, 100));
	
	for (int j = 0; j < 5; ++j) {
		x = 100.0f;
		y += (bLength + bHorizontalGap);
		for (int i = 0; i < 5; ++i)
		{
			x += (bWidth + bVerticalGap);
			block.setPosition(x, y);
			
			// get the id from the map and look up the block in the block list.
			auto itr = blockList_.find(blockMap_[j][i]);
			
			// If there isn't one (that part of the map is empty), don't draw anything.
			if (itr == blockList_.end())
				continue;
			
			//TODO: set up position better
			//This sets the blocl position really inefficiently (every display frame! - great if blocks moved...)
			itr->SetPosition(x,y);
						
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

			// Render highlight for hover
			if (itr->first == hoverBlockID_) {
				highlight.setPosition(x - bHorizontalGap, y - bVerticalGap);
				window.draw(highlight);
			}

			// Render block and value
			window.draw(block);
			window.draw(text);

		}
	}	
}

bool BlockMapManager::Update(const sf::Vector2i& mousePos) {
	// Find which block is under the mouse cursor
	BlockID hover = IdentifyBlockUnderCursor(mousePos);
	hoverBlockID_ = hover;
	// Is it the same as before?
	// Is it the same as the selected block?
	// Is there one at all?

	return false;
}

	
BlockID BlockMapManager::IdentifyBlockUnderCursor(const sf::Vector2i & mousePos) {
	float x = 100.0f;
	float y = 100.0f;
	float w = 50.0f;
	float l = 25.0f;
	float hGap = 5.0f;
	float vGap = 5.0f;

	for (int j = 0; j < 5; ++j) {
		x = 100.0f;
		y += (l + hGap); // blocks have a 5.0 pixel gap between them
		for (int i = 0; i < 5; ++i)
		{
			x += (w + vGap); // blocks have a 5.0 pixel gap between them
			sf::IntRect blockBounds(x, y, w, l);

			if (blockBounds.contains(mousePos)) {
				// get the id from the map and look up the block in the block list.
				auto itr = blockList_.find(blockMap_[j][i]);
				return itr->first;
			}
		}
	}
	return 0;
}
