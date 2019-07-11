//Modulo que define a tad para tratar arquivos de texto
#include <stdio.h>
#include "file_list.h"

#ifndef WORD_H
#define WORD_H

/*
Define a estrutura que compõe cada palavra
Fill = vetor de char com a palavra
ocrNum = quantidade de ocorrências da palavra
*/
typedef struct{
    char* fill;
    filelist_t ocrs;
} word_t;

/*
Retorna ponteiro para estrutura word_t
baseado na string passada por parâmetro
*/
word_t *new_word(char *);

/*
Retorna ponteiro para word_t
de uma palavra dado um arquivo
*/
word_t *word_from_file(FILE *, int *);

/*
Retorna menor que zero se w1 < w2
maior que zero se w1 > w2
igual a zero se se w1 == w2
Funciona em case ignore
*/
int compare_words(word_t *, word_t *);

/*
Printa a palavra dado ponteiro para word_t
*/
void print_word(word_t *);

/*
Printa a palavra e o número de ocorrências
dado ponteiro para word_t
*/
void print_word_full(word_t *);

/*
Libera a memória alocada por um ponteiro
da estrutura word_t
*/
word_t *free_word(word_t *);

/*
Seta a posição de ocorrência de uma palavra num arquivo
size = Quantidade de arquivos lidos
*/
void setOcrWord(word_t *, const char *, int, int);

/*
Lê a entrada do usuário
*/
word_t *wordInput();

/*
Dada a palavra, retorna a string da palavra 
com os caracteres convertidos para minúsculo
*/
char *convertWordLower(word_t *);

#endif
