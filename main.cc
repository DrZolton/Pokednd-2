#include <iostream>
#include <fstream>
#include "pokemon.h"
#include "list.h"

int main(){

	Pokemon test;
/*	test.inputStats(std::cin);
	test.generate(10);
	test.outputAll(std::cout);
*/
	std::ifstream fileInput;
	fileInput.open("pokedex.txt");
	if(fileInput.fail()) std::cout << "unable to input file\n";
	test.inputFile(fileInput);
	fileInput.close();
	test.outputBase(std::cout);

	char choice;
	bool done = false;
	while(!done){

		std::cin >> choice;
		switch(choice){
			case 'q':
				done = true;
				break;
			case 'g':
				std::cout << "Enter level\n";
				int tmp;
				std::cin >> tmp;
				test.generate(tmp);

				test.outputAll(std::cout);
				break;
			case 'i':
				test.inputBase();

				test.outputAll(std::cout);
				break;
			case 's':
				std::cout << "Saving\n";
				std::ofstream fileOutput;
				fileOutput.open("pokedex.txt");
				if(fileOutput.fail()) std::cout << "unable to open file\n";
				test.outputFile(fileOutput);
				fileOutput.close();
				break;
		}
	}

	return 0;
}
