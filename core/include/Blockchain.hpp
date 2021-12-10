#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "BlockNode.hpp"
#include "Block.hpp"


class Blockchain {
	private:
		BlockNode* head_node;
		BlockNode* temp_node;
		BlockNode* current_node;

	public:
		Blockchain();
		~Blockchain();

		void add_block(Block* blk);
};


#endif
