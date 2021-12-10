#include "../include/Blockchain.hpp"

Blockchain::Blockchain() {
	this -> current_node = new BlockNode;
	this -> head_node = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
}


void Blockchain::add_block(Block* blk) {
	this -> current_node = new BlockNode;
	this -> current_node -> block = blk;
	this -> current_node -> prev = this -> temp_node;
	this -> temp_node -> next = this -> current_node;
	this -> temp_node = this -> current_node;
	this -> current_node -> next = NULL;
}
