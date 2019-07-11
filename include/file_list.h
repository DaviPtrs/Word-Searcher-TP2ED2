#ifndef FILELIST_H_
#define FILELIST_H_
#include "int_list.h"

/*
Define a estrutura que as informações de cada palavra em um arquivo
path = indica o nome do arquivo
pos = lista encadeada com os valores de ocorrencias no arquivo
*/
typedef struct{
	const char *path;
	intlist_t pos;
} file_t;

typedef struct{
	file_t *files;
	int ini, end, size;
} filelist_t;

/*
Cria uma lista de arquivo contendo path e lista de posições
*/
filelist_t newFileList(int);

/* Faz a lista ficar vazia */
void emptiesFileList(filelist_t *);

/*Verifica se a lista esta vazia*/
int isEmptyFileList(filelist_t *);

/*
Procura se já existe um elemento com o mesmo path na lista
Retorna o ponteiro para celula se encontrar
Retorna NULL caso contrário
*/
file_t *searchFileInList(filelist_t *, file_t *);

/* Insere x apos o ultimo elemento da lista */
void InsertFileList(filelist_t *, file_t *);

/*Imprime a lista*/
void printFileList(filelist_t *);

/*Quantidade de elementos na lista*/
int sizeFileList(filelist_t *);

/*
Percore a lista liberando a memória
alocada por cada celula
*/
void freeFileList(filelist_t *);


#endif /* LISTAENC_H_ */


