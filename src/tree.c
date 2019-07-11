#include <stdio.h>
#include <stdlib.h>
#include "../include/tree.h"
#include "include/file_list.h"

ArvBin* new_bTree(){
    ArvBin *new = malloc(sizeof(ArvBin));
    if(new != NULL)
        *new = NULL;
    else
        printf("Alocação de nova árvore falhou!\n");
    return new;
}

int isEmptybTree(ArvBin *raiz){
    if(raiz == NULL){
        printf("Arvore nula na função isEmptybTree!\n");
        exit(1);
    }else{
        return ((*raiz) == NULL);
    }
}

int insert_bTree(ArvBin* raiz, word_t *item){
    if(isEmptybTree(raiz)){
        (*raiz) = malloc(sizeof(NO));
        (*raiz)->Dir = (*raiz)->Esq = NULL;
        (*raiz)->word = item;
        return 1;
    }else{
        int comp = compare_words(item, (*raiz)->word);
        if(comp > 0){
            insert_bTree(&(*raiz)->Dir, item);
        }
        else if(comp < 0){
            insert_bTree(&(*raiz)->Esq, item);
        }else{//Caso se for igual
            word_t *elem = ((*raiz)->word);
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
            return 1;
        }
    }
    return 0;
}

word_t *searchword_bTree(ArvBin *raiz, word_t *item){
    if(isEmptybTree(raiz))
        return NULL;
    
    NO* atual = (*raiz);
    int comp = compare_words(item, atual->word);
    if(comp == 0){
        return (*raiz)->word;
    }else{
        if(comp > 0){
            searchword_bTree(&(atual->Dir), item);
        }else{
            searchword_bTree(&(atual->Esq), item);
        }
    }
}

void free_node(NO* no){
    if (no == NULL){
        return;
    }
    free_node(no->Dir);
    free_node(no->Esq);
    freeFileList(&no->word->ocrs);
    free_word(no->word);
    free(no);
}

void free_bTree(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    free_node(*raiz);
    free(raiz);
}

void print_preOrderbTree(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        print_word_full((*raiz)->word);
        print_preOrderbTree(&((*raiz)->Esq));
        print_preOrderbTree(&((*raiz)->Dir));
    }
}

void print_inOrderbTree(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        print_preOrderbTree(&((*raiz)->Esq));
        print_word_full((*raiz)->word);
        print_preOrderbTree(&((*raiz)->Dir));
    }
}

void print_postOrderbTree(ArvBin *raiz){
    if(raiz == NULL){
        return;
    }
    if(*raiz != NULL){
        print_preOrderbTree(&((*raiz)->Esq));
        print_preOrderbTree(&((*raiz)->Dir));
        print_word_full((*raiz)->word);
    }
}

