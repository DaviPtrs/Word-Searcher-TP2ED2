//Modulo que define a tad para tratar arquivos de texto
#include <stdint.h>
#include "word.h"
#include "word_list.h"
#ifndef HASHTABLE_H
#define HASHTABLE_H

/*
Define a tabela hash como contendo um vetor 
de Lista Encadeada e o tamanho do mesmo
*/
typedef struct{
    wordlist_t *table;
    int size;
}hash_t;

/*
Algoritmo de hash para string
Retorna um unsigned int de 32 bits
*/
uint32_t jenkins_one_at_a_time_hash(const uint8_t*, size_t);

/*
Transforma o objeto word em hash
*/
uint32_t hash_word(word_t *);

/*
Retorna uma tabela hash vazia e do tamanho especificado
*/
hash_t *newHashTable(int );

/*
Retorna o índice baseado no item e no tamanho da tabela
*/
int getHashTableIndex(word_t *, int);

/*
Retorna a lista que corresponde à posição dada
pela função getHashTableIndex
*/
wordlist_t *getHashTablePos(hash_t *, word_t *);

/*
Insere o objeto word na tabela dada
*/
void insertHashTable(hash_t *, word_t *);

/*
Procura o elemento dado na tabela
Retorna o elemento inserido caso seja encontrado
Retorna NULL caso contrário
*/
word_t *searchInHashTable(hash_t *, word_t *);

/*
Libera todos os elementos alocados na tabela
*/
void freeHashTable(hash_t *);

/*
Imprime os elementos da tabela
*/
void printHashTable(hash_t *);

/*
Retorna o índice de conflitos medido de 0 a 100
*/
float conflictRate(hash_t *);

/*
Verifica se nenhum item foi inserido na tabela
Retorna 1 se estiver vazia, 0 caso contrário
Retorna -1 se a tabela for NULA
*/
int emptyHashTable(hash_t *);

/*
Define o tamanho da tabela com base no número de palavras
*/
int defHashTableSize(int);

#endif
