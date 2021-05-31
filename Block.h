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
	unsigned int width_, height_; // how much space the block takes
	bool canBeHit_; //whether this block is exposed and available to be hit.
	sf::Vector2i position_; // top left corner of block
public:

	Block(unsigned int initialValue, unsigned int width = 1, unsigned int height = 1);

	unsigned int GetValue() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
	sf::Vector2i GetPosition() const;
	bool CanBeHit() const;

	void SetValue(unsigned int value);

	void SetWidth(unsigned int width);
	void SetHeight(unsigned int height);
	void SetSize(unsigned int width, unsigned int height);

	void SetPosition(const sf::Vector2i& position);
	void SetPosition(int x, int y);
	
	
	void ToggleHitStatus();
	void MakeHittable();
	void MakeUnHittable();

	void StrikeBlock(unsigned int hammerValue); // block is hit by a hammer
	void DestroyBlock(); // block is destroyed

	// check if a number is prime.
	static bool IsPrime(unsigned int number);
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
	* Any blocks on the map edge are already exposed.
	*/

	// Player is selecting a block.
	void SelectBlock(const sf::Vector2i& mousePos);

	// Player is hitting a block - returns new value of block, or 0 if hit fail
	unsigned int HitBlock(unsigned int hammerValue);



private:
	BlockID IdentifyBlockUnderCursor(const sf::Vector2i& mousePos);

	// Determines block size and position and adds to BlockList.
	void AddBlockToList(unsigned int value, BlockID id, int& posX, int& posY);

	//Searches for the first available space in the map for the desired block size
	// returns max map size if none found.
	sf::Vector2i FindSpaceInMap(unsigned int width, unsigned int height);


private:
	sf::Font font_;
	BlockList blockList_;
	BlockMap blockMap_;
	
	BlockID selectedBlockID_; // which block is currently targeted
	BlockID hoverBlockID_; // which block the cursor is currently above.

	const float UNITBLOCKWIDTH = 30.0f;
	const float UNITBLOCKHEIGHT = 30.0f;
	const float VERTICALGAP = 5.0f;
	const float HORIZONTALGAP = 5.0f;
	const float MAPSTARTX = 100.0f;
	const float MAPSTARTY = 100.0f;
};
