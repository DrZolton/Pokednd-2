#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

struct move{
	int level;
	std::string name;
};

class Pokemon{
	public:
		Pokemon();
		void inputFile(std::istream& ins);
		void generate(const int& lvl);
		void outputAll(std::ostream& outs);
		void inputBase();

	private:
		void addMoves(std::istream& ins);

		//Info
		std::string name;
		int index;
		std::string type;
		std::string ability;
		std::string hiddenAbility;
		double height;
		double weight;
		std::string size;

		//Moves
		//void resize();
		move moves[50];
		//int arrSize;
		int numMoves;

		//Base stats
		int hitDie;
		int strength;
		int dexterity;
		int intelligence;
		int constitution;
		int charisma;
		int wisdom;
		int speed;

		//score dependant
		double AC;
		double fortitude;
		double will;
		double HP;

		int level;
};

Pokemon::Pokemon(){
	name = "";
	index = 0;
	type = "";
	ability = "";
	hiddenAbility = "";
	height = 0;
	weight = 0;
	size = "";

	numMoves = 0;

	hitDie = 0;
	strength = 0;
	dexterity = 0;
	intelligence = 0;
	constitution = 0;
	charisma = 0;
	wisdom = 0;
	speed = 0;

	AC = 0;
	fortitude = 0;
	will = 0;
	HP = 0;
	level = 0;
}

void Pokemon::inputFile(std::istream& ins){

}

void Pokemon::generate(const int& lvl){
	level = lvl;

//*******generating HP//
	srand(time(NULL));
	
	if(hitDie == 1)
		HP = 13;
	else if(hitDie == 2)
		HP = 14;
	else if(hitDie == 3)
		HP = 15;
	else
		HP = hitDie;

	for(int i = 1; i < lvl; i++){ //will run (lvl - 1) times

		if(hitDie != 1 && hitDie != 2 && hitDie != 3){ //do not run the "1d12 + x" options

			int newHP = 0;
			while(newHP < (hitDie / 2)){
				//rolls the hit die. rerolls if it is below half the hit die max
				//ex. roll a 1d4
				//    got a 1
				//    reroll because it is below 2
				//    keep going until you get 2 or higher
				newHP = (rand() % hitDie) + 1;
			}
			HP += newHP;
		}

		else if(hitDie == 1 || hitDie == 2 || hitDie == 3){ //run the "1d12 + x" options

			int newHP = 0;
			while(newHP < 6){
				//rolls the hit die. rerolls if it is below half the hit die max of 6
				//ex. roll a 1d12
				//    got a 4
				//    reroll because it is below 6
				//    keep going until you get 6 or higher
				newHP = (rand() % 12) + 1;
			}
			HP += newHP + hitDie;
		}

	}
//********************//

//**AC, Fort, Will***//
	AC = 10 + ( (dexterity - 10) / 2 );
	fortitude = 10 + ( (constitution - 10) / 2 );
	will = 10 + ( (wisdom - 10) / 2 );

}

void Pokemon::outputAll(std::ostream& outs){
	outs << std::endl << name << std::endl
		 << "Index: " << index << std::endl
		 << "Type: " << type << std::endl
		 << "Size: " << size << std::endl
		 << "Level: " << level << std::endl << std::endl

		 << "Strength: " << strength << std::endl
		 << "Dexterity: " << dexterity << std::endl
		 << "Intelligence: " << intelligence << std::endl
		 << "Constitution: " << constitution << std::endl
		 << "Charsima: " << charisma << std::endl
		 << "Wisdom: " << wisdom << std::endl << std::endl

		 << "AC: " << AC << std::endl
		 << "Fortitude: " << fortitude << std::endl
		 << "Will: " << will << std::endl << std::endl

		 << "Movement Speed: " << speed << std::endl << std::endl;

	if(hitDie == 1 || hitDie == 2 || hitDie == 3)
		outs << "Hit Die: 1d12 + " << hitDie << std::endl
			 << "HP: " << HP << std::endl;
	else
		outs << "Hit Die: 1d" << hitDie << std::endl
			 << "HP: " << HP << std::endl << std::endl;

	for(int i = 0; i < numMoves; i++)
		std::cout << moves[i].level << " ---- " << moves[i].name << std::endl;
	std::cout << std::endl;
}

void Pokemon::inputBase(){

	std::cout << "Name: ";
	std::cin >> name;

	std::cout << "Index: ";
	std::cin >> index;

	std::cout << "Type: ";
	std::cin >> type;

	std::cout << "Ability: ";
	std::cin >> ability;

	std::cout << "Hidden Ability: ";
	std::cin >> hiddenAbility;

	std::cout << "Height: ";
	std::cin >> height;

	std::cout << "Weight: ";
	std::cin >> weight;

	if(height < 6) size = "Fine";
	else if(height < 12) size = "Dimunitive";
	else if(height < 24) size = "Tiny";
	else if(height < 48) size = "Small";
	else if(height < 96) size = "Medium";
	else if(height < 192) size = "Large";
	else if(height < 384) size = "Huge";
	else if(height < 768) size = "Gargantuan";
	else size = "Colossal";

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	double data;

	//calculating Hit Die
	std::cout << "\nHP: ";
	std::cin >> data;
	if(data < 40)
		hitDie = 4; //1d4
	else if(data < 60)
		hitDie = 6; //1d6
	else if(data < 80)
		hitDie = 8; //1d8
	else if(data < 100)
		hitDie = 10; //1d10
	else if(data < 120)
		hitDie = 12; //1d12
	else if(data < 160)
		hitDie = 1; //1d12 + 1
	else if(data < 200)
		hitDie = 2; //1d12 + 2
	else
		hitDie = 3; //1d12 + 3

	//calculating Strength
	std::cout << "Attack: ";
	std::cin >> data;
	strength = ( (data + 15) / 7.5 ) + 0.5;

	//calculating Dexterity
	std::cout << "Defense: ";
	std::cin >> data;
	dexterity = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Intelligence
	std::cout << "Special Attack: ";
	std::cin >> data;
	intelligence = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Constitution
	std::cout << "Special Defense: ";
	std::cin >> data;
	constitution = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Charisma
	charisma = (strength + intelligence) / 2;

	//calculating Wisdom
	wisdom = (dexterity + constitution) / 2;

	//calculating Movement Speed
	std::cout << "Speed: ";
	std::cin >> data;
	speed = ( (data + 1.5) / 13.5 ) + 0.5;
	if(speed == 0) speed = 1; //minimum 1 speed

	std::cout << "Insert Moves:\n";
	addMoves(std::cin);
	

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/*void Pokemon::resize(){
	arrSize += 5;
	
}*/

void Pokemon::addMoves(std::istream& ins){
	//if(numMoves == arrSize) resize();

	bool done = false;
	while(!done){
		ins >> moves[numMoves].level;
		if(moves[numMoves].level == 0) done = true;
		if(!done){

			if(ins == std::cin){
				if(moves[numMoves].level < 4) moves[numMoves].level = 1;
				else if(moves[numMoves].level < 6) moves[numMoves].level = 2;
				else if(moves[numMoves].level < 9) moves[numMoves].level = 3;
				else if(moves[numMoves].level < 11) moves[numMoves].level = 4;
				else if(moves[numMoves].level < 14) moves[numMoves].level = 5;
				else if(moves[numMoves].level < 16) moves[numMoves].level = 6;
				else if(moves[numMoves].level < 19) moves[numMoves].level = 7;
				else if(moves[numMoves].level < 21) moves[numMoves].level = 8;
				else if(moves[numMoves].level < 24) moves[numMoves].level = 9;
				else if(moves[numMoves].level < 26) moves[numMoves].level = 10;
				else if(moves[numMoves].level < 29) moves[numMoves].level = 11;
				else if(moves[numMoves].level < 31) moves[numMoves].level = 12;
				else if(moves[numMoves].level < 34) moves[numMoves].level = 13;
				else if(moves[numMoves].level < 36) moves[numMoves].level = 14;
				else if(moves[numMoves].level < 39) moves[numMoves].level = 15;
				else if(moves[numMoves].level < 41) moves[numMoves].level = 16;
				else if(moves[numMoves].level < 44) moves[numMoves].level = 17;
				else if(moves[numMoves].level < 46) moves[numMoves].level = 18;
				else if(moves[numMoves].level < 49) moves[numMoves].level = 19;
				else if(moves[numMoves].level < 51) moves[numMoves].level = 20;
				else if(moves[numMoves].level < 56) moves[numMoves].level = 21;
				else if(moves[numMoves].level < 61) moves[numMoves].level = 22;
				else if(moves[numMoves].level < 66) moves[numMoves].level = 23;
				else if(moves[numMoves].level < 71) moves[numMoves].level = 24;
				else if(moves[numMoves].level < 76) moves[numMoves].level = 25;
				else if(moves[numMoves].level < 81) moves[numMoves].level = 26;
				else if(moves[numMoves].level < 86) moves[numMoves].level = 27;
				else if(moves[numMoves].level < 91) moves[numMoves].level = 28;
				else if(moves[numMoves].level < 96) moves[numMoves].level = 29;
				else if(moves[numMoves].level < 101) moves[numMoves].level = 30;
			}

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			getline(ins, moves[numMoves].name);
			numMoves++;
		}
	}

}

#endif
