//*********************************************************
//
//	Jacob Ramsey
//	B.S.C.S, Russ College of Engineering, Ohio University
//	jakeramsey202@gmail.com
//	February 18, 2018
//
//	Class: Pokemon.h
//
//	Summary: This class hold all the info for each Pokemon.
//		This includes the info that is static for each
//		species along with info that changes per specific
//		Pokemon.
//
//	Implemented:
//		-read/write file
//		-generate a pokemon given a level
//		-output all info(including instance specific)
//		-read in data from the console for new pokemon
//		-ability score increases to generate function
//		-natures and genders to generate function
//		-pokeball DC checks to generate function
//
//	Planned:
//		-dynamic allocation of move list
//		-copy constructor
//		-item effects to generate function(random item lists)
//		-read in multiple Pokemon from file
//			(current implementation is just one)
//		-non-random generate function
//
//*********************************************************

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
		void outputFile(std::ostream& fout);
		void inputFile(std::istream& fin);
		int generate(const int& lvl); //-1 return value signals errors
		void outputBase();
		void outputAll();
		int inputBase();

		//accessor function
		int getIndex(){return index;}

	private:
		void addMoves(std::istream& ins);

		//Info
		std::string name;
		int index;
		std::string type;
		std::string ability;
		std::string hiddenAbility;
		int height;
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

		//Instance dependant
		double HP;
		int level;
		std::string nature;
		char gender;
		int catchDC;
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

	nature = "";
	gender = 'x';
}

void Pokemon::outputFile(std::ostream& fout){ // "$" signals a new pokemon
	fout << "$\n" << name << std::endl
		 << index << std::endl
		 << type << std::endl
		 << ability << std::endl
		 << hiddenAbility << std::endl
		 << height << std::endl
		 << weight << std::endl
		 << size << std::endl
		 << strength << std::endl
		 << dexterity << std::endl
		 << intelligence << std::endl
		 << constitution << std::endl
		 << charisma << std::endl
		 << wisdom << std::endl
		 << speed << std::endl
		 << hitDie << std::endl;

	for(int i = 0; i < numMoves; i++)
		fout << moves[i].level << std::endl << moves[i].name << std::endl;
	fout << "0\n" << std::endl;

}

void Pokemon::inputFile(std::istream& fin){
	bool found = false;
	std::string input;
	while(!fin.eof() && !found){
		getline(fin, input);
		if(input == "$") found = true;
		//reads until the new Pokemon starts
		//or the end of the file is reached
	}

		getline(fin, name);
		fin >> index;

		fin.clear();
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		getline(fin, type);
		getline(fin, ability);
		getline(fin, hiddenAbility);
		fin >> height >> weight;

		fin.clear();
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		getline(fin, size);
		fin >> strength >> dexterity >> intelligence >> constitution >> charisma >> wisdom;
		fin >> speed >> hitDie;
		addMoves(fin);
}

int Pokemon::generate(const int& lvl){
	level = lvl;
	if(lvl > 30 || lvl < 1){
		std::cout << "ERROR: in GENERATE funtion\n\tinvalid lvl value\n";
		return -1;
	}
	

//*******generating HP//
	srand(time(NULL));
	
	if(hitDie == 1)
		HP = 13;
	else if(hitDie == 2)
		HP = 14;
	else if(hitDie == 3)
		HP = 15;
	else if(hitDie > 3 && hitDie < 13)
		HP = hitDie;
	else{
		std::cout << "ERROR: in GENERATE funtion\n\tinvalid hitDie value\n";
		return -1;
	}

	for(int i = 1; i < lvl; i++){ //will run (lvl - 1) times

		if(hitDie > 3 && hitDie < 13){ //do not run the "1d12 + x" options

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

		else{
			std::cout << "ERROR: in GENERATE funtion\n\tinvalid hitDie value\n";
			return -1;
		}

	}

//*nature and gender*//
	int die;
	die = (rand() % 24);
	if(die == 0){
		nature = "Hardy";
	}
	else if(die == 1){
		nature = "Lonely";
		strength += 2;
		dexterity -=2;
	}	
	else if(die == 2){
		nature = "Brave";
		strength += 2;
		speed -= 1;
		if(speed == 0) speed = 1;
	}
	else if(die == 3){
		nature = "Adamamant";
		strength += 2;
		intelligence -= 2;
	}
	else if(die == 4){
		nature = "Naughty";
		strength += 2;
		constitution -= 2;
	}
	else if(die == 5){
		nature = "Bold";
		dexterity += 2;
		strength -= 2;
	}
	else if(die == 6){
		nature = "Docile";
	}
	else if(die == 7){
		nature = "Relaxed";
		dexterity += 2;
		speed -= 1;
		if(speed == 0) speed = 1;
	}
	else if(die == 8){
		nature = "Impish";
		dexterity += 2;
		intelligence -= 2;
	}
	else if(die == 9){
		nature = "Lax";
		dexterity += 2;
		constitution -= 2;
	}
	else if(die == 10){
		nature = "Timid";
		speed += 1;
		strength -= 2;
	}
	else if(die == 11){
		nature = "Hasty";
		speed += 1;
		dexterity -= 2;
	}
	else if(die == 12){
		nature = "Serious";
	}
	else if(die == 13){
		nature = "Jolly";
		speed += 1;
		intelligence -= 2;
	}
	else if(die == 14){
		nature = "Naive";
		speed += 1;
		constitution -= 2;
	}
	else if(die == 15){
		nature = "Modest";
		intelligence += 2;
		strength -= 2;
	}
	else if(die == 16){
		nature = "Mild";
		intelligence += 2;
		dexterity -= 2;
	}
	else if(die == 17){
		nature = "Quiet";
		intelligence += 2;
		speed -= 1;
		if(speed == 0) speed = 1;
	}
	else if(die == 18){
		nature = "Bashful";
	}
	else if(die == 19){
		nature = "Rash";
		intelligence += 2;
		constitution -= 2;
	}
	else if(die == 20){
		nature = "Calm";
		constitution += 2;
		strength -= 2;
	}
	else if(die == 21){
		nature = "Gentle";
		constitution += 2;
		dexterity -= 2;
	}
	else if(die == 22){
		nature = "Sassy";
		constitution += 2;
		speed -= 1;
		if(speed == 0) speed = 1;
	}
	else if(die == 23){
		nature = "Careful";
		constitution += 2;
		intelligence -= 2;
	}
	else if(die == 24){
		nature = "Quirky";
	}
	else{
		std::cout << "ERROR: in GENERATE funtion\n\tinvalid nature die roll\n";
		return -1;
	}

	die = (rand() % 2);
	if(die == 0) gender = 'M';
	else gender = 'F';

//*ability score increase*//
	if(lvl > 4){
		die = (rand() % 6);
		if(die == 0) strength += 1;
		else if(die == 1) dexterity += 1;
		else if(die == 2) intelligence += 1;
		else if(die == 3) constitution += 1;
		else if(die == 4) charisma += 1;
		else if(die == 5) wisdom += 1;
		else{
			std::cout << "ERROR: in GENERATE funtion\n\tinvalid ability score die roll\n";
			return -1;
		}
	}
	if(lvl > 9){
		die = (rand() % 6);
		if(die == 0) strength += 1;
		else if(die == 1) dexterity += 1;
		else if(die == 2) intelligence += 1;
		else if(die == 3) constitution += 1;
		else if(die == 4) charisma += 1;
		else if(die == 5) wisdom += 1;
		else{
			std::cout << "ERROR: in GENERATE funtion\n\tinvalid ability score die roll\n";
			return -1;
		}
	}
	if(lvl > 14){
		strength += 1;
		dexterity += 1;
		intelligence +=1;
		constitution += 1;
		charisma += 1;
		wisdom +=1;
	}
	if(lvl > 19){
		die = (rand() % 6);
		if(die == 0) strength += 1;
		else if(die == 1) dexterity += 1;
		else if(die == 2) intelligence += 1;
		else if(die == 3) constitution += 1;
		else if(die == 4) charisma += 1;
		else if(die == 5) wisdom += 1;
		else{
			std::cout << "ERROR: in GENERATE funtion\n\tinvalid ability score die roll\n";
			return -1;
		}
	}
	if(lvl > 24){
		die = (rand() % 6);
		if(die == 0) strength += 1;
		else if(die == 1) dexterity += 1;
		else if(die == 2) intelligence += 1;
		else if(die == 3) constitution += 1;
		else if(die == 4) charisma += 1;
		else if(die == 5) wisdom += 1;
		else{
			std::cout << "ERROR: in GENERATE funtion\n\tinvalid ability score die roll\n";
			return -1;
		}
	}
	if(lvl > 29){
		strength += 1;
		dexterity += 1;
		intelligence +=1;
		constitution += 1;
		charisma += 1;
		wisdom +=1;
	}

//**AC, Fort, Will***//
	AC = 10 + ( (dexterity - 10) / 2 );
	fortitude = 10 + ( (constitution - 10) / 2 );
	will = 10 + ( (wisdom - 10) / 2 );

//**catch DC**//
	catchDC = 20 + (lvl / 3);

	return 0;
}

void Pokemon::outputBase(){
	std::cout << "--------------------\n" 
		 << name << std::endl
		 << "--------------------\n" 
		 << "Index: " << index << std::endl
		 << "Type: " << type << std::endl
		 << "Ability: " << ability << std::endl
		 << "Hidden Ability: " << hiddenAbility << std::endl
		 << "Height: " << height / 12 << "'" << height % 12 << "\"" << std::endl
		 << "Weight: " << weight << " lbs" << std::endl
		 << "Size: " << size << std::endl << std::endl

		 << "Strength: " << strength << std::endl
		 << "Dexterity: " << dexterity << std::endl
		 << "Intelligence: " << intelligence << std::endl
		 << "Constitution: " << constitution << std::endl
		 << "Charsima: " << charisma << std::endl
		 << "Wisdom: " << wisdom << std::endl << std::endl

		 << "Movement Speed: " << speed << std::endl << std::endl;

	if(hitDie == 1 || hitDie == 2 || hitDie == 3)
		std::cout << "Hit Die: 1d12 + " << hitDie << std::endl << std::endl;

	else if(hitDie > 3 && hitDie < 13)
		std::cout << "Hit Die: 1d" << hitDie << std::endl << std::endl;

	std::cout << "Moves\nLvl:   Name:\n";
	for(int i = 0; i < numMoves; i++)
		std::cout << moves[i].level << " ---- " << moves[i].name << std::endl;
	std::cout << "--------------------\n";
	std::cout << std::endl;
}

void Pokemon::outputAll(){
	std::cout << "--------------------\n" 
		 << name << std::endl
		 << "--------------------\n" 
		 << "Index: " << index << std::endl
		 << "Type: " << type << std::endl
		 << "Ability: " << ability << std::endl
		 << "Hidden Ability: " << hiddenAbility << std::endl << std::endl

		 << "Nature: " << nature << std::endl
		 << "Gender: " << gender << std::endl
		 << "Height: " << height / 12 << "'" << height % 12 << "\"" << std::endl
		 << "Weight: " << weight << " lbs" << std::endl
		 << "Size: " << size << std::endl
		 << "Level: " << level << std::endl 
		 << "Catch DC: " << catchDC << std::endl << std::endl

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
		std::cout << "Hit Die: 1d12 + " << hitDie << std::endl
			 << "HP: " << HP << std::endl;
	else if(hitDie > 3 && hitDie < 13)
		std::cout << "Hit Die: 1d" << hitDie << std::endl
			 << "HP: " << HP << std::endl << std::endl;
	else{
		std::cout << "ERROR: in GENERATE funtion\n\tinvalid hitDie value\n";
		return;
	}

	std::cout << "Moves\nLvl:   Name:\n";
	for(int i = 0; i < numMoves; i++)
		std::cout << moves[i].level << " ---- " << moves[i].name << std::endl;
	std::cout << "--------------------\n";
	std::cout << std::endl;
}

int Pokemon::inputBase(){

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "Name: ";
	getline(std::cin, name);

	std::cout << "Index: ";
	std::cin >> index;
	if(index < 1){
		std::cout << "ERROR: in INPUTBASE function\n\tinvalid index value\n\n";
		return -1;
	}
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Type: ";
	getline(std::cin, type);

	std::cout << "Ability: ";
	getline(std::cin, ability);

	std::cout << "Hidden Ability: ";
	getline(std::cin, hiddenAbility);

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

	std::cout << "Insert Moves:\nEnter level, then name\n";
	addMoves(std::cin);

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	return 0;
}

/*void Pokemon::resize(){
	arrSize += 5;
	
}*/

void Pokemon::addMoves(std::istream& ins){
	//if(numMoves == arrSize) resize();

	bool done = false;
	while(!done){
		ins >> moves[numMoves].level;
		if(moves[numMoves].level == 0) done = true; //stop reading new moves on an input of 0
		if(!done){

			if(ins == std::cin){ //if reading from the console and not a file,
								 //the move levels need to be converted
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

			ins.clear();
			ins.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			getline(ins, moves[numMoves].name);
			numMoves++;
		}
	}
	std::cout << std::endl;
}

#endif
