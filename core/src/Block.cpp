#include "../include/Block.hpp"


Block::Block(std::vector<Transaction> t, std::string prev_hash, uint32_t height) {
	this -> transactions = t;
	this -> prev_hash = prev_hash;

	/* 
	* Index is not defined yet.
	* I'll figure that out later.
	*/

	this -> hash = this -> calculate_hash();
	time_t now = time(0);
	this -> timestamp = ctime(&now);
	this -> index = height;
	this -> nonce = 0;
	this -> mined = false;
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
		header_bin += this -> nonce;
	}

	std::string hash;

	picosha2::hash256_hex_string(header_bin, hash);

	return hash;
}


std::string Block::gethash() {
	return this -> hash;
}


std::string Block::get_prev_hash() {
	return this -> prev_hash;
}


const char* Block::get_timestamp() {
	return this -> timestamp;
}


void Block::mine(unsigned int difficulty) {
	unsigned int arr[difficulty];

	for (int i = 0; i < difficulty; ++i) {
		arr[i] = i;
	}

	std::string hash_puzzle = "";

	for (int i = 0; i < sizeof(arr); ++i) {
		hash_puzzle += std::to_string(arr[i]);		
	}

	while (1) {
		std::string hash_slice = "";
		std::string hash = this -> calculate_hash();

		for (int i = 0; i < difficulty; ++i) {
			hash_slice += hash[i];
		}


		std::cout << "Nonce: " << this -> nonce << std::endl;
		std::cout << "Hash attempt: " << hash << std::endl;
		std::cout << "Hash we want: " << hash_puzzle << ".." << std::endl;

		if (hash_slice == hash_puzzle) {
			std::cout << "Block mined! Nonce: " << this -> nonce << std::endl;
			this -> mined = true;
			break;
		}

		++this -> nonce;
	}
}
