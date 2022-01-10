#include "lista.h"

void Swap(Block *a, Block *b){
	Item aux;
	aux = a->data;
	a->data = b->data;
	b->data = aux;
}

void FLVazia(Lista *l){
	l->first = (Block*) malloc (sizeof(Block));
	l->last  = l->first;
	l->first->prox = NULL;
}

void LInsert(Lista *l, Item d){
	l->last->prox = (Block*) malloc (sizeof(Block));
	l->last = l->last->prox;
	l->last->data = d;
	l->last->prox = NULL;
}

void LRemove(Lista *l, Item d){
	Block *aux, *tmp;

	if(l->first == l->last || l == NULL || l->first->prox == NULL){
		printf("LISTA VAZIA!\n");
		return;
	}
	
	aux = l->first;
	while(aux->prox != NULL){
		if (aux->prox->data.val != d.val)
			aux = aux->prox;
		else{
			tmp = aux;
			aux = aux->prox;
			tmp->prox = aux->prox;
			free(aux);
			aux = NULL;
		}
	}
}


void LImprime(Lista *l){
	Block *aux;

	aux = l->first->prox;
	while(aux != NULL){
		printf("%d\n", aux->data.val);
		aux = aux->prox;
	}
}
