#ifndef LISTAENC_H_
#define LISTAENC_H_
#include "word.h"

typedef struct wordcel wordcel_t;
struct wordcel {
  word_t *word;
  wordcel_t * Prox;
};

typedef struct {
  wordcel_t * Primeiro, *Ultimo;
} wordlist_t;

/* Faz a lista ficar vazia */
void emptiesWordList(wordlist_t *);

/*Verifica se a lista esta vazia*/
int emptyWordList(wordlist_t *);

/* Insere x apos o ultimo elemento da lista */
void InsertWordList(word_t *, wordlist_t *);

/*
Pesquisa uma palavra na lista
retorna um ponteiro para a palavra caso encontre
retorna NULL caso contrário
*/
word_t *searchWordInList(wordlist_t *, word_t *);

/*Imprime a lista
Só palavras*/
void printWordList(wordlist_t *);

/*Imprime a lista
Palavras e número de ocorrências*/
void printWordListFull(wordlist_t *);

/*Quantidade de elementos na lista*/
int sizeWordList(wordlist_t *);

/*
Percore a lista liberando a memória
alocada por cada celula
*/
void freeWordList(wordlist_t *);


#endif 
