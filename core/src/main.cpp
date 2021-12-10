#include <unistd.h>
#include <signal.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <iostream>
#include "../include/Blockchain.hpp"
#include "../include/Block.hpp"
#include "../include/Transaction.hpp"


#define MAX_TRANSACTION_PER_BLOCK 3


Blockchain* kcBlockchain;

void die(int dummy) {
	delete kcBlockchain;
	exit(0);
}


Block clog_block(std::string prevhash, uint32_t height, std::vector<Transaction> transactions) { 
	// Create and log block.
	Block newblock = Block(transactions, prevhash, height);

	std::cout << "************* MTPB REACHED, BLOCK CREATED. *************" << std::endl;
	std::cout << "Height: " << height << std::endl;
	std::cout << "Hash: " << newblock.gethash() << std::endl;
	std::cout << "Prev Hash: " << newblock.get_prev_hash() << std::endl;
	std::cout << "Timestamp: " << newblock.get_timestamp() << std::endl;
	std::cout << "********************************************************" << std::endl;

	char filepath[55];
	char command[55];

	sprintf(command, "touch ../info/blockinfo/blocks/block-%d.log", height);
	system(command);

	sprintf(filepath, "touch ../info/blockinfo/blocks/block-%d.log", height);
	std::ofstream blocklog;
	blocklog.open(filepath);

	blocklog << "Height: " << height << "\n";
	blocklog << "Hash: " << newblock.gethash() << "\n";
	blocklog << "Prev Hash: " << newblock.get_prev_hash() << "\n";
	blocklog << "Timestamp: " << newblock.get_timestamp() << "\n";
	blocklog.close();

	return newblock;

}



int main() {
	signal(SIGINT, die);
	kcBlockchain = new Blockchain; 
	uint64_t transactionindex = 0;

	/* 
	* We have dynamically allocated 
	* the blockchain so when we hit
	* CTRL C we can de-allocate it
	* before exiting the program.
	*/

	std::vector<Transaction> transactions;

	while (true) {
		if (access("../info/newtransaction", F_OK) == 0) {
			/*
			* If a transaction file 
			* exists then we have a 
			* new transaction and we
			* we open it up.
			*/
			std::ifstream tinfo;
			tinfo.open("../info/newtransaction");

			std::string to_addr;
			std::string from_addr;
			std::string amountstr;

			float amount;
			std::getline(tinfo, to_addr);
			std::getline(tinfo, from_addr);
			std::getline(tinfo, amountstr);
			std::stringstream ss;
			ss << amountstr;
			ss >> amount;

			tinfo.close();
			Transaction t(from_addr, to_addr, amount);
			transactions.push_back(t);

			std::cout << "********** TRANSACTION CREATED **********" << std::endl;
			std::cout << "Amount: " << t.get_amount() << std::endl;
			std::cout << "To Address: " << t.get_r_addr() << std::endl;
			std::cout << "From Address: " << t.get_s_addr() << std::endl;
			std::cout << "Hash: " << t.get_hash() << std::endl;
			std::cout << "***************************************" << std::endl;

			if (transactions.size() == MAX_TRANSACTION_PER_BLOCK) {
				std::ifstream blkno;
				blkno.open("../info/blockinfo/blockno");

				std::string blknostr;
				uint32_t blocknoint;

				std::getline(blkno, blknostr);

				std::stringstream ss1;
				ss1 << blknostr;
				ss1 >> blocknoint;
				blkno.close();  // Closes blkno file stream.

				if (blocknoint == 0) {  // If block number is 0 then this is genesis block.
					std::string gblockprevhash = "";

					for (int i = 0; i < 64; ++i) {
						gblockprevhash += '0';  // Fill hash with 0's.
					}

					Block gblock = clog_block(gblockprevhash, blocknoint, transactions);
				} else {
					// Do nothing for now.
				}
			}

			char command[55];
			sprintf(command, "touch ../info/transactions/transaction-%d.log", transactionindex);
			system(command);
			std::ofstream tfile;

			char filename[50];
			sprintf(filename, "../info/transactions/transaction-%d.log", transactionindex);

			tfile.open(filename, std::ios_base::app);

			tfile << "Amount: " << t.get_amount() << "\n";
			tfile << "To Addr: " << t.get_r_addr() << "\n";
			tfile << "From Addr: " << t.get_s_addr() << "\n";
			tfile << "Hash: " << t.get_hash() << "\n";

			tfile.close();
			system("rm ../info/newtransaction");
			++transactionindex;
		}

		sleep(4);
	}
}
