#include <stdio.h>
#include <stdlib.h>
#include "../include/int_list.h"

void emptiesIntList(intlist_t *list){
	if(list != NULL){
		list->Primeiro = NULL;
		list->Ultimo = NULL;
	}
}

int emptyIntList(intlist_t *list){
	return ((list->Primeiro == NULL) && (list->Ultimo == NULL));
}

void InsertIntList(intlist_t *list, int item){
	if(emptyIntList(list)){
		list->Primeiro = (intcel_t *) malloc(sizeof(intcel_t));
		list->Ultimo = list->Primeiro;
		list->Ultimo->num = item; 
		list->Ultimo->Prox = NULL;
	}else{
		list->Ultimo->Prox = (intcel_t *) malloc(sizeof(intcel_t));
		list->Ultimo = list->Ultimo->Prox;
		list->Ultimo->num = item;
		list->Ultimo->Prox = NULL;
	}
}

void printIntList(intlist_t *list){
	intcel_t *pos;
	pos = list->Primeiro;
	if(!emptyIntList(list)){
		while(pos!=NULL){
			printf("%d", pos->num);
			pos = pos->Prox;
			if(pos == NULL){
				printf("\n");
			}else{
				printf(", ");
			}
		}
	}
}

int sizeIntList(intlist_t *list){
	int i = 0;
	for(intcel_t *elem = list->Primeiro; elem != NULL; elem = elem->Prox){
		i++;
	}
	return i;
}

void freeIntList(intlist_t *list){
	intcel_t * backup;
	while(list->Primeiro != NULL){
		backup = list->Primeiro;
		list->Primeiro = list->Primeiro->Prox;
		free(backup);
	}
	list->Ultimo = NULL;
	
}
