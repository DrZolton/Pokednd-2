#include <iostream>
#include <fstream>
#include "pokemon.h"
#include "list.h"

int main(){

Pokemon test;

	std::cout << "\nWelcome to the PokeDnD creation kit v.2\n";

	std::ifstream fileInput;
	fileInput.open("pokedex.txt");
	if(fileInput.fail()){
		std::cout << "unable to open file\nclosing program\n";
		return 0;
	}

	std::cout << "loading...";
	test.inputFile(fileInput);
	fileInput.close();
	std::cout << "done\n\n";

//test.outputBase();

	char choice;
	bool done = false;
	while(!done){

		std::cout << "q: quit\n"
				  << "s: save\n"
				  << "a: add new pokemon\n"
				  << "g: generate random pokemon\n\n>";

		std::cin >> choice;
		switch(choice){
			case 'q':{
				done = true;
				break;
			}
			case 'g':{
				std::cout << "Enter level\n";
				int tmp;
				std::cin >> tmp;
				if(test.generate(tmp) == -1) break;

				test.outputAll();
				break;
			}
			case 'i':{
				if(test.inputBase() == -1) break;

				test.outputBase();
				break;
			}
			case 's':{
				std::cout << "Saving\n";
				std::ofstream fileOutput;
				fileOutput.open("pokedex.txt");
				if(fileOutput.fail()) std::cout << "unable to open file\n";
				test.outputFile(fileOutput);
				fileOutput.close();
				break;
			}
			case 'o':{
				test.outputBase();
				break;
			}
		}
	}

	return 0;
}
