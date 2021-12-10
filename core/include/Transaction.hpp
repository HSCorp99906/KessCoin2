#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>
#include "picosha2.h"
#include <fstream>
#include <cstdint>

class Transaction {
	private:
		std::string senderAddr;
		std::string recieverAddr;
		float amount;
		const char* timestamp;
		std::string hash;

		std::string calculateHash();

	public:
		Transaction(std::string senderAddr, std::string recvAddr, float amount);

		std::string get_s_addr();
		std::string get_r_addr();
		float get_amount();
		const char* get_timestamp();
		std::string get_hash();
};


#endif
