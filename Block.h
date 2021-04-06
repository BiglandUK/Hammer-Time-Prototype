#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>

// Represents a single block.
class Block {

private:
	unsigned int value_; // the current value on the block
	unsigned int width_, length_; // how much space the block takes

public:

	Block(unsigned int initialValue, unsigned int width = 1, unsigned int length = 1);

	unsigned int GetValue() const;
	unsigned int GetWidth() const;
	unsigned int GetLength() const;

	void SetWidth(unsigned int width);
	void SetLength(unsigned int length);

	void StrikeBlock(unsigned int hammerValue); // block is hit by a hammer
	void DestroyBlock(); // block is destroyed

};

using BlockID = unsigned int;
using BlockList = std::unordered_map<BlockID, Block>; // matches blocks to an ID number
using BlockMap = std::vector<std::vector<BlockID>>;

// stores the layout of the blocks
class BlockMapManager {
public:
	BlockMapManager();

	void Draw(sf::RenderWindow& window_);

private:
	sf::Font font_;
	int map_[5][5];
	BlockList blockList_;
	BlockMap blockMap_;
};