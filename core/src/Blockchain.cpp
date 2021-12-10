#include "../include/Blockchain.hpp"

Blockchain::Blockchain() {
	this -> current_node = new BlockNode;
	this -> head_node = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
	this -> height = 0;
	this -> lastHash = "";

	for (int i = 0; i < 64; ++i) {
		this -> lastHash += '0';
	}
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


void Blockchain::add_pending_transactions(std::vector<Transaction> t) {
	this -> pending_transactions = t;
}


void Blockchain::mine_pending_transactions() {
	std::string hash = "00000";
	std::vector<Transaction> t = {};
	Block newBlock(t, this -> lastHash, this -> height);
	// newBlock.mine(2);  // 2 for now.
}
