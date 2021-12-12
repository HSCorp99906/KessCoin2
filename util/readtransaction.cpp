#include <iostream>
#include <fstream>


int main() {
	system("touch newtransaction && > newtransaction");
	std::ofstream out;
	out.open("newtransaction");
	out << system("wget -qO- kesscoin.com/newtransaction");
	out.close();
}
