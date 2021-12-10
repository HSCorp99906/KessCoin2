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

			char command[55];
			sprintf(command, "touch ../info/transactions/transaction-%d", transactionindex);
			system(command);
			std::ofstream tfile;

			char filename[50];
			sprintf(filename, "../info/transactions/transaction-%d", transactionindex);

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
