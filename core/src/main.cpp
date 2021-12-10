#include <iostream>
#include "../include/Blockchain.hpp"
#include "../include/Block.hpp"
#include "../include/Transaction.hpp"


int main() {
	// Just a test currently.
	Transaction t1("000", "000", 0.00);
	Transaction t2("000", "000", 0.00);
	
	// Test transactions being added to transaction list.
	std::vector<Transaction> transactions = {t1, t2};
	std::string ghash = "";

	for (int i = 0; i < 64; ++i) {
		ghash += "0";
	}

	// Test g block.
	Block genesis(transactions, ghash);

	std::cout << genesis.gethash() << std::endl;
}
