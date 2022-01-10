#ifndef LISTA_H 
#define LISTA_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Item Item;
typedef struct Block Block;
typedef struct Lista Lista;

struct Item{
	int val;
	char *nome;
	char *aux;
};

struct Block{
	Item data;
	Block *prox;
};

struct Lista{
	Block *first;
	Block *last;
};


void FLVazia(Lista *l);
void LInsert(Lista *l, Item d);
void LRemove(Lista *l, Item d);
void Swap(Block *a, Block *b);
void LImprime(Lista *l);

#endif