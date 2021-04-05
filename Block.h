#pragma once


// Represents a single block.
class Block {

private:
	unsigned int value_; // the current value on the block
	unsigned int id_; // identifier
	unsigned int width_, length_; // how much space the block takes

public:

	Block(unsigned int intialValue);

	void StrikeBlock(unsigned int hammerValue); // block is hit by a hammer
	void DestroyBlock(); // block is destroyed

};


// stores the layout of the blocks
class BlockMapManager {
private:
	
};