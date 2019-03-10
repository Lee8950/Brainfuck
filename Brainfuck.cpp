#include "pch.h"
#include <iostream>
using namespace std;


int main(int argc,char **argv)
{
	std::vector<std::string> Arguments;
	ecl::Brainfuckvm bfkvm;
	std::ifstream BFKSRCADD;
	std::ofstream WRTOBJADD;
	std::string OBJADD;
	std::string BFKRUNTIME;
	std::string CODE;
	char _____BUF[260];
	_getcwd(_____BUF, 260);
	BFKRUNTIME = _____BUF;

	if (argc > 1) {
		bfkvm.togglemode();
		OBJADD = argv[1];
		BFKSRCADD.open(OBJADD);
		while(getline(BFKSRCADD, CODE))
		for (int i = 0; i < CODE.length(); i++) {
			bfkvm.read(CODE[i]);
		}
	}
	else {
		bfkvm.togglemode();
		getline(std::cin, CODE);
		//CODE = ">,[>,]<[.<]";
		for (int i = 0; i < CODE.length(); i++) {
			bfkvm.read(CODE[i]);
		}
	}
	
	cout << endl;
	system("pause");

	return 0;
}