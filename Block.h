#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

class Block; //forward declaration
using BlockID = unsigned int;
using BlockList = std::unordered_map<BlockID, Block>; // maps blocks to an ID number
using BlockMap = std::vector<std::vector<BlockID>>;

// Represents a single block.
class Block {

private:
	unsigned int value_; // the current value on the block
	unsigned int width_, length_; // how much space the block takes
	bool canBeHit_; //whether this block is exposed and available to be hit.
	sf::Vector2i position_; // top left corner of block
public:

	Block(unsigned int initialValue, unsigned int width = 1, unsigned int length = 1);

	unsigned int GetValue() const;
	unsigned int GetWidth() const;
	unsigned int GetLength() const;
	sf::Vector2i GetPosition() const;
	bool CanBeHit() const;

	void SetWidth(unsigned int width);
	void SetLength(unsigned int length);
	void SetPosition(const sf::Vector2i& position);
	void SetPosition(int x, int y);
	
	
	void ToggleHitStatus();
	void MakeHittable();
	void MakeUnHittable();

	void StrikeBlock(unsigned int hammerValue); // block is hit by a hammer
	void DestroyBlock(); // block is destroyed

};



// stores the layout of the blocks
class BlockMapManager {
public:
	BlockMapManager();

	void Draw(sf::RenderWindow& window_); // draws all the blocks
	bool Update(const sf::Vector2i& mousePos);

	// This method analyses the current map and checks all blocks for empty sides.
	void UpdateBlocksHittableStatus();
	void CheckBlock(Block& block); // checks a single block
	/*Logic - when a block is destroyed, in most cases it will expose one or more blocks
	* Any blocks on the map edge are exposed.
	*/

private:
	BlockID IdentifyBlockUnderCursor(const sf::Vector2i& mousePos);

private:
	sf::Font font_;
	BlockList blockList_;
	BlockMap blockMap_;
	
	BlockID selectedBlockID_; // which block is currently targeted
	BlockID hoverBlockID_; // which block the cursor is currently above.
};
