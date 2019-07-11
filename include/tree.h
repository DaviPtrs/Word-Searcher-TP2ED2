#include "word.h"
#ifndef TREE_H_
#define TREE_H_
/**
Contem um inteiro e dois apontadores (esquerda/direita)
*/
typedef struct NO NO;
typedef NO* ArvBin;
struct NO{
	word_t *word;
	NO *Esq, *Dir;
};

/*
Inicializa a árvore e deixa a raiz NULL
retorna raiz alocada e apontada para NULL
*/
ArvBin* new_bTree();

/*
Insere a palavra na árvore

Retorna: 1 em caso de sucesso. 
*/
int insert_bTree(ArvBin*, word_t *);

/*
Pesquisa uma palavra a partir da árvore raiz
retorna um ponteiro para a palavra caso encontre
retorna NULL caso contrário
*/
word_t *searchword_bTree(ArvBin *, word_t *);

/*
Verifica se a árvore está vazia
*/
int isEmptybTree(ArvBin *);

/* 
Imprime em pre-ordem 
*/ 
void print_preOrderbTree(ArvBin *);

/* 
Imprime em-ordem 
*/ 
void print_inOrderbTree(ArvBin *);

/* 
Imprime em pós-ordem 
*/ 
void print_postOrderbTree(ArvBin *);

/*
Libera a árvore binária da memória
*/
void free_bTree(ArvBin *);

#endif

