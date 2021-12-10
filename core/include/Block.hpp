#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <cstdint>
#include <vector>
#include <string>
#include "Transaction.hpp"
#include "picosha2.h"


class Block {
	private:
		uint32_t index;
		std::vector<Transaction> transactions;
		const char* timestamp;
		std::string hash;
		std::string prev_hash;

		std::string calculate_hash();

	public:
		Block(std::vector<Transaction> t, std::string prev_hash);
};


#endif
