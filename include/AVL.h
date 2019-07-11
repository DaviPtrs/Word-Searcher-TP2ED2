#include "word.h"
#ifndef AVL_H_
#define AVL_H_

typedef struct NOb* ArvAVL;
struct NOb{
    word_t *word;
    int altura;
    struct NOb *esq;
    struct NOb *dir;
};

/*
Retorna um ponteiro de ponteiro pro primeiro NÓ
*/
ArvAVL* new_AVL();

/*
Libera todos os nós e o ponteiro da raiz
*/
void free_AVL(ArvAVL *);

/*
Insere a palavra na árvore, fazendo em seguida,
as rotações necessarias para balancear a árvore
*/
int insert_AVL(ArvAVL *, word_t *);

/*
Verifica se a árvore é nula ou aponta para um nó nulo
*/
int isEmpty_AVL(ArvAVL *);

/*
Conta a altura de nós de uma raiz
*/
int heightAVL(ArvAVL *);

/*
Conta o total de nós na árvore inteira
*/
int nodeNums_AVL(ArvAVL *);

/*
Pesquisa a palavra na árvore
Retorna o ponteiro para a palavra encontrada e 
libera a palavra referência
Retorna NULL caso contrário
*/
word_t *searchWord_AVL(ArvAVL *, word_t *);

/*
Printa a palavra e seu número de ocorrências em pré ordem
*/
void print_preOrderAVL(ArvAVL *);

/*
Printa a palavra e seu número de ocorrências em ordem
*/
void print_inOrderAVL(ArvAVL *);

/*
Printa a palavra e seu número de ocorrências em pós ordem
*/
void print_postOrderAVL(ArvAVL *);

#endif