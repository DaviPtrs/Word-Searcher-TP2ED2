#include "file.h"
#ifndef TRI_H
#define TRI_H

typedef struct nodet_t nodet_t;
struct nodet_t
{
    int wordFlag;
    nodet_t *filho[TAMPAL];
    word_t *word;
};

/*
Retorna ponteiro para um nó alocado, com seus campos inicializados com NULL ou 0
*/
nodet_t* newNode();

/*
Insere o elemento na árvore prefixa
*/
void insertWordTrie(nodet_t **, word_t *);

/*
Procura a palavra na arvore prefixa
Retorna o ponteiro caso exista
Retorna NULL caso contrário
*/
word_t *searchWordTrie(nodet_t *, word_t *);

/*
Retorna se existem filhos no NÓ dado
*/
int haveChild(nodet_t *);

/*
Printa a árvore em pré ordem
*/
void printTrie(nodet_t *);

/*
Libera a árvore a partir do nó raiz
*/
void freeTrie(nodet_t *);

#endif