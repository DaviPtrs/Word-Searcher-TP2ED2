#include <stdio.h>
#include <stdlib.h>
#include "include/file_list.h"
#include "../include/word_list.h"


void emptiesWordList(wordlist_t *list){
	if(list != NULL){
		list->Primeiro = list->Ultimo = NULL;
	}
}

int emptyWordList(wordlist_t *list){
	return ((list->Primeiro == NULL) && (list->Ultimo == NULL));
}

void InsertWordList(word_t *item, wordlist_t *list){
	if(emptyWordList(list)){
		list->Primeiro = (wordcel_t *) malloc(sizeof(wordcel_t));
		list->Ultimo = list->Primeiro;
		list->Ultimo->word = item; 
		list->Ultimo->Prox = NULL;
	}else{
		word_t *elem = searchWordInList(list, item);
		if(elem == NULL){
			list->Ultimo->Prox = (wordcel_t *) malloc(sizeof(wordcel_t));
			list->Ultimo = list->Ultimo->Prox;
			list->Ultimo->word = item;
			list->Ultimo->Prox = NULL;
		}else{
			file_t *file = searchFileInList(&elem->ocrs,&item->ocrs.files[0]);
			if(file == NULL){
				InsertFileList(&elem->ocrs, &item->ocrs.files[0]);
				free(item->ocrs.files);
				free_word(item);
			}else{
				InsertIntList(&file->pos, item->ocrs.files[0].pos.Primeiro->num);
				freeFileList(&item->ocrs);
				free_word(item);
			}
		}
	}	
}

word_t *searchWordInList(wordlist_t *list, word_t *item){
	wordcel_t * pos;
	word_t *word;
	pos = list->Primeiro;
	if(!emptyWordList(list)){
		while(pos!=NULL){	
			word = pos->word;
			int comp = compare_words(word, item);
			if(comp == 0){
				return pos->word;
			}
			pos = pos->Prox;
		}
	}
	return NULL;
}

void printWordList(wordlist_t *list){
	wordcel_t * pos;
	word_t *word;
	pos = list->Primeiro;
	if(!emptyWordList(list)){
		while(pos!=NULL){	
			word = pos->word;
			print_word(word);
			pos = pos->Prox;
		}
	}
}

void printWordListFull(wordlist_t *list){
	wordcel_t * pos;
	word_t *word;
	pos = list->Primeiro;
	if(!emptyWordList(list)){
		while(pos!=NULL){	
			word = pos->word;
			print_word_full(word);
			pos = pos->Prox;
		}
	}
}

int sizeWordList(wordlist_t *list){
	int i = 0;
	for(wordcel_t * elem = list->Primeiro; elem != NULL; elem = elem->Prox){
		i++;
	}
	return i;
}

void freeWordList(wordlist_t *list){
	wordcel_t * backup;

	while(list->Primeiro != NULL){
		backup = list->Primeiro;
		list->Primeiro = list->Primeiro->Prox;
		freeFileList(&backup->word->ocrs);
		free_word(backup->word);
		free(backup);
	}
}
