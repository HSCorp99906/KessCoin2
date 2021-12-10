#include "../include/Block.hpp"


Block::Block(std::vector<Transaction> t, std::string prev_hash) {
	this -> transactions = t;
	this -> prev_hash = prev_hash;

	/* 
	* Index is not defined yet.
	* I'll figure that out later.
	*/

	this -> hash = this -> calculate_hash();
	time_t now = time(0);
	this -> timestamp = ctime(&now);
}


std::string Block::calculate_hash() {
	std::string header_bin = std::to_string(this -> index);
	header_bin += this -> timestamp;
	header_bin += this -> prev_hash;

	for (int i = 0; i < this -> transactions.size(); ++i) {
		header_bin += this -> transactions[i].get_s_addr();
		header_bin += this -> transactions[i].get_r_addr();
		header_bin += std::to_string(this -> transactions[i].get_amount());
		header_bin += this -> transactions[i].get_timestamp();
		header_bin += this -> transactions[i].get_hash();
	}

	std::string hash;

	picosha2::hash256_hex_string(header_bin, hash);

	return hash;
}


std::string Block::gethash() {
	return this -> hash;
}
