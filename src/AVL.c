#include <stdio.h>
#include <stdlib.h>
#include "../include/AVL.h"

ArvAVL* new_AVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void free_nodeb(struct NOb* no){
    if(no == NULL)
        return;
    free_nodeb(no->esq);
    free_nodeb(no->dir);
    freeFileList(&no->word->ocrs);
    free_word(no->word);
    free(no);
    no = NULL;
}

void free_AVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    free_nodeb(*raiz);
    free(raiz);
}

int heightNode(struct NOb* no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int nodeBalanceFactor(struct NOb* no){
    return labs(heightNode(no->esq) - heightNode(no->dir));
}

int getGreater(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int isEmpty_AVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int nodeNums_AVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = nodeNums_AVL(&((*raiz)->esq));
    int alt_dir = nodeNums_AVL(&((*raiz)->dir));

    return(alt_esq + alt_dir + 1);
}

int heightAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;

    int alt_esq = heightAVL(&((*raiz)->esq));
    int alt_dir = heightAVL(&((*raiz)->dir));

    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void print_preOrderAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        print_word_full((*raiz)->word);
        print_preOrderAVL(&((*raiz)->esq));
        print_preOrderAVL(&((*raiz)->dir));
    }
}

void print_inOrderAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        print_inOrderAVL(&((*raiz)->esq));
        print_word_full((*raiz)->word);
        print_inOrderAVL(&((*raiz)->dir));
    }
}

void print_postOrderAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        print_postOrderAVL(&((*raiz)->esq));
        print_postOrderAVL(&((*raiz)->dir));
        print_word_full((*raiz)->word);
    }
}

word_t *searchWord_AVL(ArvAVL *raiz, word_t *item){
    if(raiz == NULL)
        return NULL;
    struct NOb* atual = *raiz;
    while(atual != NULL){
        int comp = compare_words(item, atual->word);
        if(comp == 0){
            return atual->word;
        }
        if(comp > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }

    return NULL;
}

void LLrot(ArvAVL *A){
    struct NOb *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = getGreater(heightNode((*A)->esq),heightNode((*A)->dir)) + 1;
    B->altura = getGreater(heightNode(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RRrot(ArvAVL *A){
    struct NOb *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = getGreater(heightNode((*A)->esq),heightNode((*A)->dir)) + 1;
    B->altura = getGreater(heightNode(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void LRrot(ArvAVL *A){
    RRrot(&(*A)->esq);
    LLrot(A);
}

void RLrot(ArvAVL *A){
    LLrot(&(*A)->dir);
    RRrot(A);
}

int insert_AVL(ArvAVL *raiz, word_t *item){
    int res;
    if(*raiz == NULL){
        struct NOb *novo;
        novo = (struct NOb*)malloc(sizeof(struct NOb));
        if(novo == NULL)
            return 0;

        novo->word = item;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NOb *atual = *raiz;
    int comp = compare_words(item, atual->word);
    if(comp < 0){
        if((res = insert_AVL(&(atual->esq), item)) == 1){
            if(nodeBalanceFactor(atual) >= 2){
                if(compare_words(item,(*raiz)->esq->word) < 0){
                    LLrot(raiz);
                }else{
                    LRrot(raiz);
                }
            }
        }
    }else{
        if(comp > 0){
            if((res = insert_AVL(&(atual->dir), item)) == 1){
                if(nodeBalanceFactor(atual) >= 2){
                    if(compare_words((*raiz)->dir->word, item) < 0){
                        RRrot(raiz);
                    }else{
                        RLrot(raiz);
                    }
                }
            }
        }else{//caso seja igual
			word_t *elem = atual->word;
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
    atual->altura = getGreater(heightNode(atual->esq),heightNode(atual->dir)) + 1;

    return res;
}