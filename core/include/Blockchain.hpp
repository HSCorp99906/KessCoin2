#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "BlockNode.hpp"
#include "Block.hpp"
#include "Transaction.hpp"
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
#include <sstream>


#define REWARD_AMOUNT 150


class Blockchain {
	private:
		BlockNode* head_node;
		BlockNode* temp_node;
		BlockNode* current_node;
		std::vector<Transaction> pending_transactions;
		uint32_t height;
		std::string lastHash;
		
		Block* genesis;

		bool tempStorageActive;
		Block* tempStorage;

		void add_block(Block* blk);

	public:
		Blockchain();
		~Blockchain();

		void mine_pending_transactions();
		
		void increment_height();
		void add_pending_transactions(std::vector<Transaction> t);

		void delete_temp_storage();

		Block get_prev_block();
};


#endif
