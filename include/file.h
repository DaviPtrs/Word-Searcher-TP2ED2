//Modulo que define a tad para tratar arquivos de texto
#include <stdio.h>
#ifndef FILE_H
#define FILE_H
#define TAMPAL 80

/*
Lê uma palavra do arquivo passado como parâmetro,
armazenando-a no segundo parâmetro
*Segundo parâmetro precisa ser um vetor de char estático de tamanho 80
*/
int read_word(FILE *, char *, int *);

/*
Retorna um arquivo na função "read"
dando um path válido
*/
FILE *open_read_file(const char *);

/*
Conta o número de palavras no arquivo
Retorna o número de espaços seguidos de alfanuméricos + 1
*/
int countWordsInFile(FILE *);

/*
Fecha o arquivo (??)
*/
void close_file(FILE *);

#endif
