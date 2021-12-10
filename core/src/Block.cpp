#include "../include/Block.hpp"


Block::Block(std::vector<Transaction> t, std::string prev_hash, uint32_t height) {
	this -> transactions = t;
	this -> prev_hash = prev_hash;

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
		header_bin += std::to_string(this -> nonce);
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


std::string Block::get_timestamp() {
	return this -> timestamp;
}


void Block::mine(unsigned int difficulty) {
	std::string hash_puzzle = "";
	std::cout << "SIZE: " << this -> transactions.size() << std::endl;

	for (int i = 0; i < difficulty; ++i) {
		hash_puzzle += std::to_string(i);
	}

	std::cout << "\n\nPreparing to mine blocks.." << std::endl;
	sleep(2);

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
			std::cout << "\n\nBlock mined! Nonce: " << this -> nonce << std::endl;
			this -> mined = true;
			break;
		}

		++this -> nonce;
	}
}
