//*********************************************************
//
//	Jacob Ramsey
//	B.S.C.S, Russ College of Engineering, Ohio University
//	jakeramsey202@gmail.com
//	February 18, 2018
//
//	Class: list.h
//
//	Summary: This class is to be used with "pokemon.h".
//		It is a container class to create and manipulate
//		large lists of pokemon.
//
//*********************************************************

#ifndef LIST_H
#define LIST_H

#include "pokemon.h"
#include <string>
#include <algorithm>

struct node{
	Pokemon data;
	node* link;
};

class list{
	public:
		int temporary(node*& cursor);
		void temporary1(node*& cursor);
		std::string tempAdvance(node*& cursor);

		list(){head = NULL;}
		void add(Pokemon newPokemon);
		void consoleOutputBase();
		void fileInput(std::istream& fin);
		int fileOutput(std::ostream& fout);
		int findName(const std::string target, Pokemon& canvas);
		int deletePokemon(std::string target);
		int size();
		void prevStageMoves();

	private:
		node* head;
};

void list::add(Pokemon newPokemon){
	if(head == NULL){ //if the list is empty
		head = new node;
		head -> data = newPokemon;
		head -> link = NULL;
		return;
	}
	else{ //list is not empty
		if(newPokemon.getIndex() < head -> data.getIndex()){ //front of the list
			node* tmp = head;
			head = new node;
			head -> data = newPokemon;
			head -> link = tmp;
			return;
		}
		else{
			node* prev = head;
			node* next = head -> link;
			while(next != NULL && newPokemon.getIndex() > next -> data.getIndex()){
			//not at the end and still searching
				prev = prev -> link;
				next = next -> link;
			}
			if(newPokemon.getIndex() == prev -> data.getIndex()){
				std::cout << "A pokemon with that index already exists\n\n";
				return;
			}
			if(next!= NULL && newPokemon.getIndex() == next -> data.getIndex()){
				std::cout << "A pokemon with that index already exists\n\n";
				return;
			}
			prev -> link = new node;
			prev -> link -> data = newPokemon;
			prev -> link -> link = next;
			return;
		}
	}
}

void list::consoleOutputBase(){
	if(head == NULL){
		std::cout << "Pokedex is empty, nothing to display\n\n";
		return;
	}
	else{
		node* cursor = head;
		while(cursor != NULL){
			cursor -> data.outputBase(std::cout);
			cursor = cursor -> link;
		}
		return;
	}
}

void list::fileInput(std::istream& fin){
	while(!fin.eof()){
		Pokemon input;
		input.inputFile(fin);
		if(!fin.eof()) add(input);
	}
	return;
}

int list::fileOutput(std::ostream& fout){
	if(head == NULL){
		std::cout << "\nNothing to save\n\n";
		return -1;
	}
	else{
		node* cursor = head;
		while(cursor != NULL){
			cursor -> data.outputFile(fout);
			cursor = cursor -> link;
		}
		return 0;
	}
}

int list::findName(const std::string target, Pokemon& canvas){
	if(head == NULL) return -1; //empty list

	node* cursor = head;
	while(cursor != NULL){ //while not at the end
		if(
			(cursor -> data.getName()).substr(1) == target.substr(1)
			&& tolower(cursor -> data.getName()[0]) == tolower(target[0])
		)
		{ //found
			canvas = cursor -> data;
			return 0;
		}
		else cursor = cursor -> link; //advance
	}
	return -1; //not found
}

int list::deletePokemon(const std::string target){
	if(head == NULL) return -1; //empty list

	if(head -> data.getName() == target){ //found at the front of the list
		node* tmp = head;
		head = head -> link;
		delete tmp;
		return 0;
	}

	node* cursor = head -> link;
	node* prev = head;
	while(cursor != NULL){ //while not at the end
		if(cursor -> data.getName() == target){ //found
			prev -> link = cursor -> link;
			delete cursor;
			return 0;
		}
		cursor = cursor -> link; //advance
		prev = prev -> link;
	}
	return -1; //not found
}

int list::size(){
        if(head == NULL) return 0; //empty list

	int size = 0;
        node* cursor = head;
        while(cursor != NULL){ //while not at the end
		size++;
		cursor = cursor -> link;
        }
	return size;
}

void list::prevStageMoves(){
	if(head == NULL) return; //empty list

	node* sourceCursor = head;
	Pokemon source, target;
	while(sourceCursor != NULL){ //iterate through entire pokedex
		source = sourceCursor -> data;
//		source.outputBase(std::cout);

		evolution* evolutions = source.getEvos();
		if(evolutions[0].evoName != "None" && evolutions[0].evoName != "none"){
			int index = 0;
			while(evolutions[index].evoName.length() > 0){ //iterate through every evolution
				std::string targetName = evolutions[index].evoName;
				std::string targetRequirement = evolutions[index].evoRequirement;
//std::cout << source.getName() << ":" << targetName << ":" << targetRequirement << std::endl;

				node* targetCursor = head;
				while(targetCursor != NULL){ //iterate through entire pokemon for evolution
					if(targetCursor -> data.getName() == targetName){
						int numberMoves;
						move* sourceMoves = source.getMoves(numberMoves);
//targetCursor -> data.outputBase(std::cout);
						for(int i = 0; i <= numberMoves; i++){ //iterate through entire source move list
							move newMove = sourceMoves[i];
							newMove.name += "(" + source.getName() + ")";
//std::cout << "adding " << newMove.name << ":" << newMove.level << std::endl;
							targetCursor -> data.addMove(newMove);
//std::cout << sourceMoves[i].name << std::endl;
						}
//target = targetCursor -> data;
//std::cout << target.getName() << std::endl;
					}
					targetCursor = targetCursor -> link;
				}

				index++;
			}
		}

		sourceCursor = sourceCursor -> link;
	}
}

std::string list::tempAdvance(node*& cursor){
//std::cout << "0" << std::flush;
	if(cursor ->link != NULL){
		cursor = cursor -> link;
//std::cout << "1" << std::flush;
	}
	else{
		cursor = head;
//std::cout << "2" << std::flush;
	}
	return cursor -> data.getName();
}

void list::temporary1(node*& cursor){
	cursor = head;
}

int list::temporary(node*& cursor){
//	node* tmp = head;
	if(cursor != NULL){
		cursor -> data.temporary();
		cursor = cursor -> link;
		return 0;
	}
	else{
		std::cout << "end of list\n";
		return -1;
	}
}



#endif
