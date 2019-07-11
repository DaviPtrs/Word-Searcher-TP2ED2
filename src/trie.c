#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/word.h"
#include "../include/trie.h"
#define tamNODE 26


nodet_t* newNode()
{
    nodet_t* cell = (nodet_t *) malloc(sizeof(nodet_t));
    cell -> wordFlag = 0;
    for(int i = 0; i < tamNODE; i++)
    {
        cell ->filho[i] = NULL;
    }
    cell->word = NULL;

    return cell;
    
}

void insertWordTrie(nodet_t **raiz, word_t *item)
{
    nodet_t* aux = *raiz; // para percorrer a árvore
    if((aux == NULL) || (item == NULL)){
        printf("Nó ou item nulo na função insertWordTrie\n");
        exit(1);
    }
    char* frase = item->fill;
    int Nloops = strlen(frase);

    for(int i = 0; i < Nloops; i++)
    {
        if(aux->filho[tolower(frase[i]) - 'a'] == NULL)
            aux ->filho[tolower(frase[i]) - 'a'] = newNode();

        aux = aux->filho[tolower(frase[i]) - 'a'];

    }
    aux -> wordFlag = 1;
    if(aux->word == NULL){
        aux->word = item;
    }else{
        word_t *elem = aux->word;
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

word_t *searchWordTrie(nodet_t *raiz, word_t *item)
{
    char *frase = item->fill;

    if((raiz == NULL) || (item == NULL))
        return NULL; // Árvore vazia

    nodet_t* aux = raiz;
    int nloops = strlen(frase);

    for(int i = 0; i < nloops; i++)
    {
        aux = aux ->filho[frase[i] - 'a']; 
        if(aux == NULL)
            return NULL; // o prefixo *frase - 'a' não foi inserido na árvore
    
    }

    if(aux->wordFlag == 0){
        return NULL;
    }else{
        return aux->word;
    }
}           

int haveChild(nodet_t *raiz)
{
    if(raiz != NULL){
        for(int i = 0; i < tamNODE; i++)
            if(raiz->filho[i] != NULL)
                return 1;
    }
    return 0;
}

void printSubTrie(nodet_t *raiz, int *contador, char *palavra)
{
    for(int i = 0; i < tamNODE; i++)
    {
        if(raiz->filho[i] != NULL)
        {
            palavra[*contador] = (char) (i) + 'a';
            (*contador)++;

            if(raiz->filho[i]->wordFlag == 1)
            {
                palavra[(*contador)] = '\0';
                print_word_full(raiz->filho[i]->word);
            }

            printSubTrie(raiz->filho[i], contador, palavra);
            (*contador) = (*contador) - 1; 
        }
    }
}

void printTrie(nodet_t *raiz)
{   
    int contador = 0;
    char palavra[TAMPAL] = {"\0"};
    nodet_t *aux = raiz;
    if(aux == NULL)
        return;

    printSubTrie(raiz, &contador, palavra);
}

void freeNode(nodet_t *raiz)
{
    if(raiz != NULL){
        for(int i = 0; i < tamNODE; i++){
            if(raiz->filho[i] != NULL)
                freeNode(raiz->filho[i]);
        }
    }

    if(raiz->wordFlag == 1){
        if(raiz->word != NULL){
            freeFileList(&raiz->word->ocrs);
            free_word(raiz->word);
            raiz->word = NULL;
        }
    }
    free(raiz);
    raiz = NULL;
}

void freeTrie(nodet_t *raiz)
{
    freeNode(raiz);
    raiz = NULL;
}
