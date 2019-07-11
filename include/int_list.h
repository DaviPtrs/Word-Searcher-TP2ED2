#ifndef INTLIST_H_
#define INTLIST_H_

typedef struct intcel intcel_t;
struct intcel{
	int num;
	intcel_t *Prox;
};

typedef struct {
	intcel_t *Primeiro, *Ultimo;
} intlist_t;

/* 
Faz a lista ficar vazia 
*/
void emptiesIntList(intlist_t *);

/*
Verifica se a lista esta vazia
*/
int emptyIntList(intlist_t *);

/* 
Insere x apos o ultimo elemento da lista 
*/
void InsertIntList(intlist_t *, int);

/*
Imprime a lista
*/
void printIntList(intlist_t *);

/*
Quantidade de elementos na lista
*/
int sizeIntList(intlist_t *);

/*
Percore a lista liberando a memória
alocada por cada celula
*/
void freeIntList(intlist_t *);


#endif 
