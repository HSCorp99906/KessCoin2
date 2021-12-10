#include "../include/Transaction.hpp"


Transaction::Transaction(std::string senderAddr, std::string recvAddr, float amount) {
	static uint64_t index = 0;

	this -> senderAddr = senderAddr;
	this -> recieverAddr = recvAddr;
	this -> amount = amount;

	time_t now = time(0);
	this -> timestamp = ctime(&now);
	this -> hash = this -> calculateHash();
}


std::string Transaction::calculateHash() {
	std::string header_bin = this -> senderAddr;
	header_bin += this -> recieverAddr;
	header_bin += std::to_string(this -> amount);
	header_bin += this -> timestamp;

	std::string hash;

	picosha2::hash256_hex_string(header_bin, hash);

	return hash;
}


std::string Transaction::get_s_addr() {
	return this -> senderAddr;
}


std::string Transaction::get_r_addr() {
	return this -> recieverAddr;
}


float Transaction::get_amount() {
	return this -> amount;
}


const char* Transaction::get_timestamp() {
	return this -> timestamp;
}


std::string Transaction::get_hash() {
	return this -> hash;
}
