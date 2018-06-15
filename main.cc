#include <sstream>
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

//temporary
/*std::cout << "preparing to modify ability scores\n\n";
pokedex.temporary1();*/

	char choice;
	bool done = false;
	while(!done){

		std::cout << "q: quit\n"
				  << "s: save\n"
				  << "a: add new pokemon\n"
				  << "g: generate a pokemon with random stats\n"
				  << "f: search for a pokemon by name\n"
				  << "d: delete a pokemon\n"
				  << "o: output all\n\n > ";

		std::cin >> choice;
		std::cout << std::endl;
		switch(choice){
			case 'q':{
				std::string input;

				std::cout << "You may have unsaved data\nAre you sure you wish to quit? (y/n)\n\n > ";
				std::cin >> input;
				std::cout << std::endl;

				if(input == "y"){
					std::cout << "Closing program\n\n";
					done = true;
					break;
				}
				else if(input == "n"){
					std::cout << "Not closing program\n\n";
					break;
				}
				else{
					std::cout << "Invalid choice\n\n";
					break;
				}

			}
			case 'g':{
				std::string target;
				std::cout << "Enter the name of the Pokemon you wish to generate\n\n > ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, target);
				//std::cin >> target;
				std::cout << std::endl;

				Pokemon canvas;
				if(pokedex.findName(target, canvas) == -1){
					std::cout << "Pokemon not found\n\n";
					break;
				}

				int lvl;
				std::cout << "Enter level\n\n > ";
				std::cin >> lvl;
				std::cout << std::endl;

				if(canvas.generate(lvl) == -1) break;
				canvas.outputAll();

				char save;
				std::cout << "Would you like to save this pokemon to a file? (y/n)\n\n > ";
				std::cin >> save;
				std::cout << std::endl;
				if(save == 'y' || save == 'Y'){
					std::ofstream saveFile;
					std::stringstream ss;
					ss << lvl;
					std::string saveName = target + "Lvl" + ss.str() + ".tmp";
					saveFile.open(saveName.c_str());
					if(saveFile.fail()){
						std::cout << "\nunable to save file\n\n";
						break;
					}
					canvas.outputBase(saveFile);
					std::cout << "saved " << target << "\n\n";
				}
				else if(save == 'n' || save == 'N')
					std::cout << "not saving " << target << "\n\n";
				else
					std::cout << "invalid choice\n\n";

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
			case 'f':{
				std::string target;
				Pokemon canvas;

				std::cout << "Enter the name of the Pokemon you want to find\n\n > ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, target);
				//std::cin >> target;
				std::cout << std::endl;

				if(pokedex.findName(target, canvas) == -1){
					std::cout << "Pokemon not found\n\n";
					break;
				}
				canvas.outputBase(std::cout);
				break;
			}
			case 'd':{
				std::string target;

				std::cout << "Enter the name of the Pokemon you want deleted\n\n > ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				getline(std::cin, target);
				//std::cin >> target;
				std::cout << std::endl;

				if(pokedex.deletePokemon(target) == -1)
					std::cout << "Pokemon not found, cannot delete\n\n";
				break;
			}
			case 'o':{
				pokedex.consoleOutputBase();
				std::cout << "Total Pokemon in Pokedex: " << pokedex.size() << std::endl << std::endl;
				break;
			}
			default:{
				std::cout << "Invalid choice\n\n";
//				break;
			}
                        //sometimes the choice is a string meant as a console command or the name of a pokemon
                        //to prevent each character of the choice being read cin will be cleared
			while( !std::cin.eof() && std::cin.get() != '\n' );
		}
	}

	return 0;
}
