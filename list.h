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

struct node{
	Pokemon data;
	node* link;
};

class list{
	public:
void temporary1();

		list(){head = NULL;}
		void add(Pokemon newPokemon);
		void consoleOutputBase();
		void fileInput(std::istream& fin);
		int fileOutput(std::ostream& fout);
		int findName(const std::string target, Pokemon& canvas);
		int deletePokemon(std::string target);

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
			cursor -> data.outputBase();
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
		if(cursor -> data.getName() == target){ //found
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

void list::temporary1(){
	node* tmp = head;
	while(tmp != NULL){
		tmp -> data.temporary();
		tmp = tmp -> link;
	}
	std::cout << "end of list\n";
}

#endif
