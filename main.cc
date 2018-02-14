#include <iostream>
#include "stats.h"

int main(){

	Pokemon test;
	test.inputStats(std::cin);
	test.generate(10);
	test.outputAll(std::cout);

	return 0;
}
