#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <signal.h>
#include "Transaction.hpp"
#include "picosha2.h"


class Block {
	private:
		uint32_t index;
		std::vector<Transaction> transactions;
		const char* timestamp;
		std::string hash;
		std::string prev_hash;
		uint64_t nonce;
		std::string calculate_hash();
		bool mined;
	public:
		Block(std::vector<Transaction> t, std::string prev_hash, uint32_t height);

		void mine(unsigned int difficulty);
		std::string gethash();
		std::string get_prev_hash();

		const char* get_timestamp();
};


#endif
