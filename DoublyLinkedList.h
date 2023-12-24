#pragma once
#include "Enemy.h"

struct Node{
	Enemy val;
	Node *prev, *next;
	Node(): val(), prev(NULL), next(NULL){}
	Node(Enemy e): val(e), prev(NULL), next(NULL){}
};

void del(Node *n){
	n->prev->next = n->next;
	n->next->prev = n->prev;
	delete n;
}

void insert(Node *n, Node *nd){
	nd->next = n;
	nd->prev = n->prev;
	n->prev->next = nd;
	n->prev = nd;
}
