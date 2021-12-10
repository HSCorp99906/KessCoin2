#include "../include/Blockchain.hpp"

Blockchain::Blockchain() {
	this -> current_node = new BlockNode;
	this -> head_node = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
	
	std::ifstream blockno;
	blockno.open("../info/blockinfo/blockno");

	uint32_t blknoint;
	std::string blknostr;
	std::getline(blockno, blknostr);

	std::stringstream ss;
	ss << blknostr;
	ss >> blknoint;

	blockno.close();

	this -> height = blknoint;


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


void Blockchain::increment_height() {
	std::ofstream of;
	of.open("../info/blockinfo/blockno");
	of << ++this -> height;
	of.close();
}


void Blockchain::mine_pending_transactions() {
	Block* newBlock = new Block(this -> pending_transactions, this -> lastHash, this -> height);
	newBlock -> mine(4);  // 2 for now.
	this -> add_block(newBlock);
	std::cout << "********** BLOCK ADDED TO BLOCKCHAIN **********" << std::endl;
	std::cout << "Hash: " << newBlock -> gethash() << std::endl;
	std::cout << "Previous Hash: " << newBlock -> get_prev_hash() << std::endl;
	std::cout << "Timestamp: " << newBlock -> get_timestamp() << std::endl;
	std::cout << "***********************************************" << std::endl;
	this -> lastHash = newBlock -> gethash();
}
