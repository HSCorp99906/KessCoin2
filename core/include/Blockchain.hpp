#ifndef BLOCKCHAIN_HPP
#define BLOCKCHAIN_HPP

#include "BlockNode.hpp"
#include "Block.hpp"
#include "Transaction.hpp"
#include <vector>
#include <cstdint>
#include <string>

#define REWARD_AMOUNT 150


class Blockchain {
	private:
		BlockNode* head_node;
		BlockNode* temp_node;
		BlockNode* current_node;
		std::vector<Transaction> pending_transactions;
		uint32_t height;
		std::string lastHash;

	public:
		Blockchain();
		~Blockchain();

		void mine_pending_transactions();
		void add_block(Block* blk);

		void add_pending_transactions(std::vector<Transaction> t);

		Block get_prev_block();
};


#endif
