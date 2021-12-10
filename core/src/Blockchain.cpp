#include "../include/Blockchain.hpp"

Blockchain::Blockchain() {
	this -> current_node = new BlockNode;
	this -> head_node = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
	this -> height = 0;
}


Blockchain::~Blockchain() {
	BlockNode* curNode = this -> head_node;
	BlockNode* nextNode;

	while (curNode != NULL) {
		nextNode = curNode -> next;
		delete curNode;
		curNode = nextNode;
	}
}


void Blockchain::add_block(Block* blk) {
	this -> current_node = new BlockNode;
	this -> current_node -> block = blk;
	this -> current_node -> prev = this -> temp_node;
	this -> temp_node -> next = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
}


Block Blockchain::get_prev_block() {
	uint32_t currentHeight = 0;
	BlockNode* curNode = this -> head_node;

	while (currentHeight != this -> height) {
		curNode = curNode -> next;

		if (currentHeight == this -> height - 1) {
			break;
		}

		if (curNode == NULL) {
			break;
		}

		++currentHeight;
	}

	return *curNode -> block;
}


void Blockchain::mine_pending_transactions() {
	Block newBlock(this -> pending_transactions, this -> get_prev_block().gethash(), this -> height);
	newBlock.mine(2);  // 2 for now.
}
