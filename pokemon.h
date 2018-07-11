//*********************************************************//
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
//		-non-random generate function
//
//*********************************************************//

#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <math.h>

struct move{
	int level;
	std::string name;
};

class Pokemon{
	public:
		void temporary();

		Pokemon();
		void outputFile(std::ostream& fout);
		void inputFile(std::istream& fin);
		int generate(const int& lvl); //-1 return value signals errors
		void outputBase(std::ostream& outs);
		void outputAll(std::ostream& outs);
		int inputBase();

		//accessor function
		int getIndex(){return index;}
		std::string getName(){return name;}

	private:
		void addMoves(std::istream& ins);
		void moveSort();

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

		//base stats
		int hp;
		int attack;
		int defense;
		int spAttack;
		int spDefense;
		int spd;

		//Base ability scores
		int hitDie;
		int strength;
		int dexterity;
		int intelligence;
		int constitution;
		int charisma;
		int wisdom;
		int speed;
		std::string evolution;
		double genderRatio;

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
		int powerPoints;
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
	std::string evolution = "";
	genderRatio = 0.0;

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
		 << hitDie << std::endl
		 << evolution << std::endl
		 << genderRatio << std::endl
		 << hp << std::endl
		 << attack << std::endl
		 << defense << std::endl
		 << spAttack << std::endl
		 << spDefense << std::endl
		 << spd << std::endl;

	for(int i = 0; i <= numMoves; i++)
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

		fin.clear();
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		getline(fin, evolution);
		fin >> genderRatio;

		fin >> hp;
		fin >> attack;
		fin >> defense;
		fin >> spAttack;
		fin >> spDefense;
		fin >> spd;

		addMoves(fin);
}

int Pokemon::generate(const int& lvl){
	srand(time(NULL));

	level = lvl;
	if(lvl > 30 || lvl < 1){
		std::cout << "ERROR: in GENERATE funtion\n\tinvalid lvl value\n";
		return -1;
	}

//**Ability**//
	if(ability.find("/") != std::string::npos){
		int pos = ability.find("/");
		int die = rand() % 2;

		if(die == 0) ability = ability.substr(0, pos);
		else ability = ability.substr(pos + 1);
	}

//**Size change**//
	int die;
	die = (rand() % 100);
	if(die == 99) die = 20;
	else die = (rand() % 20) + 1;

	if(die != 10 && die != 20){
		height = height * (1.0 + (static_cast<double>(die - 10) / 100.0));
		weight = weight * (1.0 + (static_cast<double>(die - 10) / 100.0))
						* (1.0 + (static_cast<double>(die - 10) / 100.0))
						* (1.0 + (static_cast<double>(die - 10) / 100.0));

//		if(height < 6) size = "Fine";
//		else if(height < 12) size = "Dimunitive";
//		else if(height < 24) size = "Tiny";
//		else if(height < 48) size = "Small";
//		else if(height < 96) size = "Medium";
//		else if(height < 192) size = "Large";
//		else if(height < 384) size = "Huge";
//		else if(height < 768) size = "Gargantuan";
//		else size = "Colossal";
	}
	if(die == 20){
		height = height * 2;
		weight = weight * 8;
		if(hitDie == 1) hitDie = 3;
		else if(hitDie == 2) hitDie = 3;
		else if(hitDie == 3);
		else if(hitDie == 12) hitDie = 2;
		else if(hitDie == 10) hitDie = 1;
		else hitDie += 4;

                if(size == "Small") size = "Medium(Xtra)";
                else if(size == "Medium") size = "Large(Xtra)";
                else if(size == "Large") size = "Huge(Xtra)";
                else if(size == "Huge") size = "Gargantuan(Xtra)";
                else if(size == "Gargantuan") size = "Colossal(Xtra)";
		else if(size == "Colossal") size = "Colossal(Xtra)";
                else{
			std::cout << "Invalid size\n";
			return -1;
		}

//		if(height < 6) size = "Fine(Xtra)";
//		else if(height < 12) size = "Dimunitive(Xtra)";
//		else if(height < 24) size = "Tiny(Xtra)";
//		else if(height < 48) size = "Small(Xtra)";
//		else if(height < 96) size = "Medium(Xtra)";
//		else if(height < 192) size = "Large(Xtra)";
//		else if(height < 384) size = "Huge(Xtra)";
//		else if(height < 768) size = "Gargantuan(Xtra)";
//		else size = "Colossal(Xtra)";
	}

	//Rounding Weight
	weight = int((weight*10) + 0.5);
	weight /= 10;

//*******generating HP*//
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

	for(int i = 2; i <= lvl; i++){ //will run (lvl - 1) times
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

//****Power Points***//
	powerPoints = 20;
	for(int i = 1; i <= lvl; i++){


		if(i == 4 || i == 7 || i == 11 || i == 14 || i == 17 || i == 21 || i == 24 || i == 27){
			die = (rand() % 8) + 1;
			//rerolls the die until 4 or greater is rolled
			while(die < 4){
				die = (rand() % 8) + 1;
			}
			powerPoints += die;
		}
	}

//*nature and gender*//
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
		if(speed < 2) speed = 2;
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
		if(speed < 2) speed = 2;
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
		if(speed < 2) speed = 2;
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
		if(speed < 2) speed = 2;
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

	if(genderRatio == 0.0) gender = 'X';
	else if(genderRatio == 1) gender = 'M';
	else if(genderRatio == -1) gender = 'F';
	else{
		die = (rand() % 1000) + 1;
		if(die < (int)genderRatio) gender = 'M';
		else if(die > (int)genderRatio) gender = 'F';
		else{
			die = (rand() % 2);
			if(die == 0) gender = 'M';
			else gender = 'F';
		}
	}


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
	AC = 10 + floor( double(dexterity - 10) / 2 );
	fortitude = 10 + floor( double(constitution - 10) / 2 );
	will = 10 + floor( double(wisdom - 10) / 2 );

//**catch DC**//
	catchDC = 20 + (lvl / 3);

//**Moves**//
	int cursor = 0;
	while(cursor <= numMoves && moves[cursor].level <= lvl) cursor++;
	numMoves = cursor - 1;
	//if(numMoves < 0) numMoves = 0;

	return 0;
}

void Pokemon::outputBase(std::ostream& outs){
	outs << "--------------------\n"
		 << name << std::endl
		 << "--------------------\n"
		 << "Index: " << index << std::endl
		 << "Type: " << type << std::endl
		 << "Ability: " << ability << std::endl
		 << "Hidden Ability: " << hiddenAbility << std::endl
		 << "Height: " << height / 12 << "'" << height % 12 << "\"" << std::endl
		 << "Weight: " << weight << " lbs" << std::endl
		 << "Size: " << size << std::endl;

		if(genderRatio == 0) outs << "Gender Ratio: Genderless\n\n";
		if(genderRatio == 1) outs << "Gender Ratio: 100% Male, 0% Female\n\n";
		else if(genderRatio == -1) outs << "Gender Ratio: 0% Male, 100% Female\n\n";
		else{
			double genderR = int(genderRatio);
			genderR /= 10;
			outs << "Gender Ratio: " << genderR << "% Male, ";
			genderR = genderRatio - int(genderRatio);
			genderR *= 100;
			outs << genderR << "% Female\n\n";
		}

		std::string evo = evolution;
		int pos = evo.find(">");
		outs << "Evolution\n" << evo.substr(1, pos-1) << std::endl;
		evo = evo.substr(pos+1);
		while (evo.length() > 0){
			pos = evo.find(">");
			outs << evo.substr(1, pos-1) << std::endl;
			evo = evo.substr(pos+1);
		}
		outs << std::endl;

		outs << "Strength: " << strength << " (" << floor(double(strength - 10)/2.0) << ")" << std::endl
		 << "Dexterity: " << dexterity << " (" << floor(double(dexterity - 10)/2.0) << ")" << std::endl
		 << "Intelligence: " << intelligence << " (" << floor(double(intelligence - 10)/2.0) << ")" << std::endl
		 << "Constitution: " << constitution << " (" << floor(double(constitution - 10)/2.0) << ")" << std::endl
		 << "Charsima: " << charisma << " (" << floor(double(charisma - 10)/2.0) << ")" << std::endl
		 << "Wisdom: " << wisdom << " (" << floor(double(wisdom - 10)/2.0) << ")" << std::endl << std::endl

		 << "Movement Speed: " << speed << std::endl;

	if(hitDie == 1 || hitDie == 2 || hitDie == 3)
		outs << "Hit Die: 1d12 + " << hitDie << std::endl << std::endl;

	else if(hitDie > 3 && hitDie < 13)
		outs << "Hit Die: 1d" << hitDie << std::endl << std::endl;

	outs << "Moves\nLvl:    Name:\n";
	for(int i = 0; i <= numMoves; i++){
		outs << moves[i].level;
		if(moves[i].level < 10) outs << " ";
		outs << " ---- " << moves[i].name << std::endl;
	}
	outs << "--------------------\n";
	outs << std::endl << std::endl;
}

void Pokemon::outputAll(std::ostream& outs){
	outs << "--------------------\n"
		 << name << std::endl
		 << "--------------------\n";

		outs << "Level: " << level << std::endl
		 << "Catch DC: " << catchDC << std::endl << std::endl

		 << "Index: " << index << std::endl
		 << "Type: " << type << std::endl
		 << "Ability: " << ability << std::endl
		 << "Hidden Ability: " << hiddenAbility << std::endl
		 << "Height: " << height / 12 << "'" << height % 12 << "\"" << std::endl
		 << "Weight: " << weight << " lbs" << std::endl
		 << "Size: " << size << std::endl
		 << "Gender: " << gender << std::endl
		 << "Nature: " << nature << std::endl << std::endl;

		std::string evo = evolution;
		int pos = evo.find(">");
		outs << "Evolution\n" << evo.substr(1, pos-1) << std::endl;
		evo = evo.substr(pos+1);
		while (evo.length() > 0){
			pos = evo.find(">");
			outs << evo.substr(1,pos-1) << std::endl;
			evo = evo.substr(pos+1);
		}
		outs << std::endl;

                outs << "Strength: " << strength << " (" << floor(double(strength - 10)/2.0) << ")" << std::endl
                 << "Dexterity: " << dexterity << " (" << floor(double(dexterity - 10)/2.0) << ")" << std::endl
                 << "Intelligence: " << intelligence << " (" << floor(double(intelligence - 10)/2.0) << ")" << std::endl
                 << "Constitution: " << constitution << " (" << floor(double(constitution - 10)/2.0) << ")" << std::endl
                 << "Charsima: " << charisma << " (" << floor(double(charisma - 10)/2.0) << ")" << std::endl
                 << "Wisdom: " << wisdom << " (" << floor(double(wisdom - 10)/2.0) << ")" << std::endl << std::endl

		 << "AC: " << AC << std::endl
		 << "Fortitude: " << fortitude << std::endl
		 << "Will: " << will << std::endl
		 << "Movement Speed: " << speed << std::endl;

//	if(hitDie == 1 || hitDie == 2 || hitDie == 3)
//		outs << "Hit Die: 1d12 + " << hitDie << std::endl
//			 << "HP: " << HP << std::endl << std::endl;
//	else if(hitDie > 3 && hitDie < 13)
//		outs << "Hit Die: 1d" << hitDie << std::endl
//			 << "HP: " << HP << std::endl << std::endl;
//	else{
//		std::cout << "ERROR: in OUTPUTALL funtion\n\tinvalid hitDie value\n";
//		return;
//	}

	outs << "Hit Dice: " << level << "d";
        if(hitDie == 1 || hitDie == 2 || hitDie == 3) outs << "12 + " << level * hitDie;
	else outs << hitDie;
	outs << "\nHP: " << HP << "\n"
		<< "Power Points: " << powerPoints << "\n\n";


	outs << "Moves\nLvl:    Name:\n";
	for(int i = 0; i <= numMoves; i++){
		outs << moves[i].level;
		if(moves[i].level < 10) outs << " ";
		outs << " ---- " << moves[i].name << std::endl;
	}
	outs << "--------------------\n";
	outs << std::endl;
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

	evolution = "";
	std::string evolutionTemp;
	int levelTemp;
	char inputTemp;

	bool doneTemp = false;
	while(!doneTemp){
        	std::cout << "Is this a level based evolution?(y/n): ";
        	std::cin >> inputTemp;
        	if(inputTemp == 'y'){

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                	std::cout << "Input evolution: ";
                	getline(std::cin, evolutionTemp);
			std::cout << "Input level: ";
			std::cin >> levelTemp;

			if(levelTemp < 4) levelTemp = 1;
			else if(levelTemp < 6) levelTemp = 2;
			else if(levelTemp < 9) levelTemp = 3;
			else if(levelTemp < 11) levelTemp = 4;
			else if(levelTemp < 14) levelTemp = 5;
			else if(levelTemp < 16) levelTemp = 6;
			else if(levelTemp < 19) levelTemp = 7;
			else if(levelTemp < 21) levelTemp = 8;
			else if(levelTemp < 24) levelTemp = 9;
			else if(levelTemp < 26) levelTemp = 10;
			else if(levelTemp < 29) levelTemp = 11;
			else if(levelTemp < 31) levelTemp = 12;
			else if(levelTemp < 34) levelTemp = 13;
			else if(levelTemp < 36) levelTemp = 14;
			else if(levelTemp < 39) levelTemp = 15;
			else if(levelTemp < 41) levelTemp = 16;
			else if(levelTemp < 44) levelTemp = 17;
			else if(levelTemp < 46) levelTemp = 18;
			else if(levelTemp < 49) levelTemp = 19;
			else if(levelTemp < 51) levelTemp = 20;
			else if(levelTemp < 56) levelTemp = 21;
			else if(levelTemp < 61) levelTemp = 22;
			else if(levelTemp < 66) levelTemp = 23;
			else if(levelTemp < 71) levelTemp = 24;
			else if(levelTemp < 76) levelTemp = 25;
			else if(levelTemp < 81) levelTemp = 26;
			else if(levelTemp < 86) levelTemp = 27;
			else if(levelTemp < 91) levelTemp = 28;
			else if(levelTemp < 96) levelTemp = 29;
			else if(levelTemp < 101) levelTemp = 30;

			std::stringstream ss;
			ss << levelTemp;

                        evolution += "<" + evolutionTemp + ": Lvl " + ss.str() + ">";
        	}
        	else if(inputTemp == 'n'){

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	        	std::cout << "Input evolution: ";
			getline(std::cin, evolutionTemp);
			evolution += "<" + evolutionTemp + ">";
		}
		else std::cout << "Invalid Choice\n\n";

		std::cout << "Are you done with evolutions?(y/n): ";
		std::cin >> inputTemp;
		if(inputTemp == 'y') doneTemp = true;
//		else evolution += " ";
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "Type: ";
	getline(std::cin, type);

	std::cout << "Ability: ";
	getline(std::cin, ability);

	std::cout << "Hidden Ability: ";
	getline(std::cin, hiddenAbility);

	int tmp;
	std::cout << "Height(5 4 = 5'4\"): ";
	std::cin >> tmp >> height;
	tmp = tmp * 12;
	height += tmp;

	std::cout << "Weight: ";
	std::cin >> weight;

	std::cout << "\nEnter size\n"
		<< "Small is up to 2x2 ft -- Medium is 2x2 ft to 5x5 ft -- Large is 5x5 ft to 10x10 ft\n"
		<< "Huge is 10x10 ft to 15x15 ft -- Gargantuan is 15x15 ft to 20x20 ft -- Colossal is 20x20ft and up\n"
		<< "(s for Small, m for Medium, l for Large, h for Huge, g for Gargantuan, c for Colossal): ";
	char sizeInput;
	std::cin >> sizeInput;
	if(sizeInput == 's') size = "Small";
	else if(sizeInput == 'm') size = "Medium";
	else if(sizeInput == 'l') size = "Large";
	else if(sizeInput == 'h') size = "Huge";
	else if(sizeInput == 'g') size = "Gargantuan";
	else if(sizeInput == 'c') size = "Colossal";
	else{
		std::cout << "Invalid Size\n";
		return -1;
	}
	std::cout << std::endl;

//	if(height < 6) size = "Fine";
//	else if(height < 12) size = "Dimunitive";
//	else if(height < 24) size = "Tiny";
//	else if(height < 48) size = "Small";
//	else if(height < 96) size = "Medium";
//	else if(height < 192) size = "Large";
//	else if(height < 384) size = "Huge";
//	else if(height < 768) size = "Gargantuan";
//	else size = "Colossal";

//	std::cout << "Input gender ratio for " << name << " in the following format: 50.50\n > ";
	std::cout << "Gender ratio(ex. 875.125)\n"
		<< "(0 for genderless, 1 for all male, and -1 for all female): ";
	std::cin >> genderRatio;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

//	double data;

	//calculating Hit Die
	std::cout << "\nHP: ";
	std::cin >> hp;
	if(hp < 40)
		hitDie = 4; //1d4
	else if(hp < 60)
		hitDie = 6; //1d6
	else if(hp < 80)
		hitDie = 8; //1d8
	else if(hp < 100)
		hitDie = 10; //1d10
	else if(hp < 120)
		hitDie = 12; //1d12
	else if(hp < 160)
		hitDie = 1; //1d12 + 1
	else if(hp < 200)
		hitDie = 2; //1d12 + 2
	else
		hitDie = 3; //1d12 + 3

	//calculating Strength
	std::cout << "Attack: ";
	std::cin >> attack;
	strength = attack * 0.1167 + 6.5;

	//calculating Dexterity
	std::cout << "Defense: ";
	std::cin >> defense;
	dexterity = defense * 0.1167 + 6.5;

	//calculating Intelligence
	std::cout << "Special Attack: ";
	std::cin >> spAttack;
	intelligence = spAttack * 0.1167 + 6.5;

	//calculating Constitution
	std::cout << "Special Defense: ";
	std::cin >> spDefense;
	constitution = spDefense * 0.1167 + 6.5;

	//calculating Charisma
	charisma = (strength + intelligence) / 2;

	//calculating Wisdom
	wisdom = (dexterity + constitution) / 2;

	//minimum score of 3
	if(strength < 3) strength = 3;
	if(dexterity < 3) dexterity = 3;
	if(intelligence < 3) intelligence = 3;
	if(constitution < 3) constitution = 3;
	if(charisma < 3) charisma = 3;
	if(wisdom < 3) wisdom = 3;

	//calculating Movement Speed
	std::cout << "Speed: ";
	std::cin >> spd;
	speed = spd * 0.05 + 3.5;
	if(speed < 2) speed = 2; //minimum 2 speed

	std::cout << "\nInsert Moves:\nEnter level, then name\n";
	addMoves(std::cin);
	std::cout << std::endl;

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}

/*void Pokemon::resize(){
	arrSize += 5;

}*/

void Pokemon::addMoves(std::istream& ins){
	//if(numMoves == arrSize) resize();

	if(ins == std::cin){
	//this section of code will read in all the text copied from bulbapedia
	//and find the names and levels of each move

		std::cout << "\nBe sure to add moves with numbers in the\n"
				  << "name and moves learned upon evolution manually.\n"
				  << "They will not read in correctly.\n\n";

		std::string line;
		bool copyDone = false;

		ins.clear();
		ins.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		while(!copyDone){
			int cursor = 0;

			getline(ins, line);

			if(line == "0") copyDone = true;

			else{
				//find the location of the move category
				//this will be used as a reference point
				//for locating the name and level
				cursor = line.find("Status", 0);
				if(cursor < 0){
					cursor = line.find("Special", 0);
					if(cursor < 0) cursor = line.find("Physical", 0);
				}

				if(cursor > 0){

					cursor--;
					cursor--;
					while( isalpha(line[cursor]) ) cursor--;
					cursor--; //found the end of the name

					int cursor2 = cursor;
					while( isalpha(line[cursor]) ) cursor--;
					//if the name is one word, this is the beginning
					//if the name is multiple words, this is only the beginning of the last word

					if(isalpha(line[cursor - 1])){
						cursor--;
						while( isalpha(line[cursor]) ) cursor--;

						if(isalpha(line[cursor - 1]))
							while( isalpha(line[cursor]) ) cursor--;

					}

					if(line[cursor - 1] != 'A' && line[cursor - 1] !='.'){
						moves[numMoves].name = line.substr(cursor + 1, cursor2 - cursor);

						cursor2 = cursor;
						cursor--;
						while(isdigit(line[cursor])) cursor--;

						moves[numMoves].level = std::atoi(line.substr(cursor + 1, cursor2 - cursor).c_str());

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
						if(moves[numMoves].name != "Evo.") numMoves++;
					}
				}
			}
		}
	}

	bool done = false;
	while(!done){
		ins >> moves[numMoves].level;
		if(moves[numMoves].level == 0){
			done = true; //stop reading new moves on an input of 0
			numMoves--;
		}
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
			if(moves[numMoves].name != "Evo.") numMoves++;
		}
	}
	moveSort();
	//std::cout << std::endl;
}

void Pokemon::moveSort(){
	for(int i = 0; i < numMoves; i++){
		for(int j = i + 1; j <= numMoves; j++){
			if(moves[i].level > moves[j].level){
				move tmp = moves[i];
				moves[i] = moves[j];
				moves[j] = tmp;
			}
		}
	}
}

void Pokemon::temporary(){

/*	if(strength < 3) strength = 3;
	if(dexterity < 3) dexterity = 3;
	if(intelligence < 3) intelligence = 3;
	if(constitution < 3) constitution = 3;
	if(charisma < 3) charisma = 3;
	if(wisdom < 3) wisdom = 3;
*/


/*	std::cout << "(ignore HP) input stats for " << name << std::endl;



	double data;

	//calculating Strength
	std::cout << "Attack: ";
	std::cin >> data;
	strength = data * 0.1167 + 6.5;

	//calculating Dexterity
	std::cout << "Defense: ";
	std::cin >> data;
	dexterity = data * 0.1167 + 6.5;

	//calculating Intelligence
	std::cout << "Special Attack: ";
	std::cin >> data;
	intelligence = data * 0.1167 + 6.5;

	//calculating Constitution
	std::cout << "Special Defense: ";
	std::cin >> data;
	constitution = data * 0.1167 + 6.5;

	//calculating Charisma
	charisma = (strength + intelligence) / 2;

	//calculating Wisdom
	wisdom = (dexterity + constitution) / 2;

	//calculating Movement Speed
	std::cout << "Speed: ";
	std::cin >> data;
	speed = data * 0.05 + 3.5;
	//if(speed == 0 || speed == 1) speed = 2; //minimum 1 speed

			std::cout << "\nStrength: " << strength << std::endl
			 << "Dexterity: " << dexterity << std::endl
			 << "Intelligence: " << intelligence << std::endl
			 << "Constitution: " << constitution << std::endl
			 << "Charsima: " << charisma << std::endl
			 << "Wisdom: " << wisdom << std::endl
			 << "Movement Speed: " << speed << std::endl << std::endl;
*/



//	std::cin.clear();
//	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

/*	evolution = "";
	std::string evolutionTemp;
	int levelTemp;
	char inputTemp;

	bool doneTemp = false;
	while(!doneTemp){
        	std::cout << name << ": Is this a level based evolution?(y/n)\n > ";
        	std::cin >> inputTemp;
        	if(inputTemp == 'y'){

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                	std::cout << "Input evolution\n > ";
                	getline(std::cin, evolutionTemp);
			std::cout << "Input level\n > ";
			std::cin >> levelTemp;

			if(levelTemp < 4) levelTemp = 1;
			else if(levelTemp < 6) levelTemp = 2;
			else if(levelTemp < 9) levelTemp = 3;
			else if(levelTemp < 11) levelTemp = 4;
			else if(levelTemp < 14) levelTemp = 5;
			else if(levelTemp < 16) levelTemp = 6;
			else if(levelTemp < 19) levelTemp = 7;
			else if(levelTemp < 21) levelTemp = 8;
			else if(levelTemp < 24) levelTemp = 9;
			else if(levelTemp < 26) levelTemp = 10;
			else if(levelTemp < 29) levelTemp = 11;
			else if(levelTemp < 31) levelTemp = 12;
			else if(levelTemp < 34) levelTemp = 13;
			else if(levelTemp < 36) levelTemp = 14;
			else if(levelTemp < 39) levelTemp = 15;
			else if(levelTemp < 41) levelTemp = 16;
			else if(levelTemp < 44) levelTemp = 17;
			else if(levelTemp < 46) levelTemp = 18;
			else if(levelTemp < 49) levelTemp = 19;
			else if(levelTemp < 51) levelTemp = 20;
			else if(levelTemp < 56) levelTemp = 21;
			else if(levelTemp < 61) levelTemp = 22;
			else if(levelTemp < 66) levelTemp = 23;
			else if(levelTemp < 71) levelTemp = 24;
			else if(levelTemp < 76) levelTemp = 25;
			else if(levelTemp < 81) levelTemp = 26;
			else if(levelTemp < 86) levelTemp = 27;
			else if(levelTemp < 91) levelTemp = 28;
			else if(levelTemp < 96) levelTemp = 29;
			else if(levelTemp < 101) levelTemp = 30;

			std::stringstream ss;
			ss << levelTemp;

                        evolution += "<" + evolutionTemp + ": Lvl " + ss.str() + ">";
        	}
        	else if(inputTemp == 'n'){

			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	        	std::cout << "Input evolution\n > ";
			getline(std::cin, evolutionTemp);
			evolution += "<" + evolutionTemp + ">";
		}
		else std::cout << "Invalid Choice\n\n";

		std::cout << "Are you done with evolutions?(y/n)\n > ";
		std::cin >> inputTemp;
		if(inputTemp == 'y') doneTemp = true;
//		else evolution += " ";
	}

	std::cout << "Evolution: " << evolution << std::endl;

	std::cout << "Input gender ratio for " << name << " in the following format: 875.125\n"
		<< "(0 for genderless, 1 for all male, and -1 for all female)\n > ";
	std::cin >> genderRatio;
	std::cout << "Gender ratio: " << genderRatio << std::endl;

	std::cout << "HP: ";
	std::cin >> hp;

	std::cout << "Attack: ";
	std::cin >> attack;

	std::cout << "Defense: ";
	std::cin >> defense;

	std::cout << "Special Attack: ";
	std::cin >> spAttack;

	std::cout << "Special Defense: ";
	std::cin >> spDefense;

	std::cout << "Speed: ";
	std::cin >> spd;
	std::cout << std::endl;
*/

        std::cout << "Enter size for " << name << std::endl
		<< "Height: " << height/12 << "' " << height%12 << "\"" << std::endl
		<< "Small is up to 2x2 ft -- Medium is 2x2 ft to 5x5 ft -- Large is 5x5 ft to 10x10 ft\n"
		<< "Huge is 10x10 ft to 15x15 ft -- Gargantuan is 15x15 ft to 20x20 ft -- Colossal is 20x20ft and up\n"
		<< "(s for Small, m for Medium, l for Large, h for Huge, g for Gargantuan, c for Colossal): ";
	char sizeInput;
	std::cin >> sizeInput;

	if(sizeInput == 's') size = "Small";
	else if(sizeInput == 'm') size = "Medium";
	else if(sizeInput == 'l') size = "Large";
	else if(sizeInput == 'h') size = "Huge";
	else if(sizeInput == 'g') size = "Gargantuan";
	else if(sizeInput == 'c') size = "Colossal";
	else{
		std::cout << "Invalid Size\n";
	}
	std::cout << "Size: " << size << std::endl;
}

#endif
