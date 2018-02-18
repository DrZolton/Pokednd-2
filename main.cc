#include <iostream>
#include <fstream>
#include "pokemon.h"
#include "list.h"

int main(){

Pokemon test;
list pokedex;

	std::cout << "\nWelcome to the PokeDnD creation kit v.2\n\n";

	std::ifstream fileInput;
	fileInput.open("pokedex.txt");
	if(fileInput.fail()){
		std::cout << "unable to open file\nclosing program\n";
		return 0;
	}

	std::cout << "loading...";
	pokedex.fileInput(fileInput);
	fileInput.close();
	std::cout << "done\n\n";

	char choice;
	bool done = false;
	while(!done){

		std::cout << "q: quit\n"
				  << "s: save\n"
				  << "a: add new pokemon\n"
				  << "g: generate random pokemon\n"
				  << "o: output all\n\n> ";

		std::cin >> choice;
		std::cout << std::endl;
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
			case 'a':{
				Pokemon newPokemon;
				if(newPokemon.inputBase() == -1) break;
				pokedex.add(newPokemon);
				break;
			}
			case 's':{
				std::cout << "Saving...";

				std::ofstream fileOutput;
				fileOutput.open("pokedex.txt");
				if(fileOutput.fail()){
					std::cout << "\nunable to save to file\n";
					break;
				}
				if(pokedex.fileOutput(fileOutput) == -1) break;

				fileOutput.close();
				std::cout << "done\n\n";
				break;
			}
			case 'o':{
				pokedex.consoleOutputBase();
				break;
			}
		}
	}

	return 0;
}
