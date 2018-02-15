#ifndef LIST_H
#define LIST_H

#include "pokemon.h"

struct node{
	Pokemon data;
	node* next;
};

class list{
	public:
		void add();

	private:
		node* head;
};

#endif
