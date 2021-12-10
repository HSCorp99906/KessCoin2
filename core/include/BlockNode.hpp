#ifndef BLOCKNODE_HPP
#define BLOCKNODE_HPP

#include "Block.hpp"


struct BlockNode {
    Block* block;
    BlockNode* next;
	BlockNode* prev;
};


#endif
