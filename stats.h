#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Pokemon{
	public:
		void inputStats(std::istream& ins);
		void generate(const int& lvl);
		void outputAll(std::ostream& outs);

	private:
		//Base scores
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

void Pokemon::inputStats(std::istream& ins){
	double data;

	//calculating Hit Die
	ins >> data;
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
	ins >> data;
	strength = ( (data + 15) / 7.5 ) + 0.5;

	//calculating Dexterity
	ins >> data;
	dexterity = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Intelligence
	ins >> data;
	intelligence = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Constitution
	ins >> data;
	constitution = ( (data + 30) / 8.333 ) + 0.5;

	//calculating Charisma
	charisma = (strength + intelligence) / 2;

	//calculating Wisdom
	wisdom = (dexterity + constitution) / 2;

	//calculating Movement Speed
	ins >> data;
	speed = ( (data + 1.5) / 13.5 ) + 0.5;
	if(speed == 0) speed = 1; //minimum 1 speed
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
	outs << "Level: " << level << std::endl << std::endl
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
			 << "HP: " << HP << std::endl;
}
