#include <iostream>
#include "pokemon.h"
#include "list.h"

int main(){

	Pokemon test;
/*	test.inputStats(std::cin);
	test.generate(10);
	test.outputAll(std::cout);
*/
	char choice;
	bool done = false;
	while(!done){

		std::cin >> choice;
		switch(choice){
			case 'q':
				done = true;
				break;
			case 'g':
				/*test.inputFile(std::cin);

				std::cout << "Enter level\n";
				int tmp;
				std::cin >> tmp;
				test.generate(tmp);

				test.outputAll(std::cout);*/
				break;
			case 'i':
				test.inputBase();

				std::cout << "Enter level\n";
				int tmp;
				std::cin >> tmp;
				test.generate(tmp);

				test.outputAll(std::cout);
				break;
		}
	}

	return 0;
}
