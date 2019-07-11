#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "../include/file.h"
#include "../include/word.h"
#include "../include/file_list.h"

word_t *wordInput(){
	char word[80];
	if(scanf("%s", &word) == 1){
	    return new_word(word);
    }else{
        getchar();
        return NULL;
    }
}

word_t *new_word(char *word){
    word_t *new;
    if((word != NULL) || (word[0] != '\0')){
        new = malloc(sizeof(word_t));
        int tam = strlen(word) + 1;

        new->fill = malloc(sizeof(char) * tam);
        strcpy(new->fill, word);

    }else{
        new = NULL;
        printf("Palavra inválida na função new_word!\n");
    }

    return new;
}

word_t *backup_word(word_t *origin){
    word_t *new;
    
    new = malloc(sizeof(word_t));
    int tam = strlen(origin->fill) + 1;

    new->fill = malloc(sizeof(char) * tam);
    strcpy(new->fill, origin->fill);
    file_t *originFile = &origin->ocrs.files[0];

    setOcrWord(new, originFile->path, originFile->pos.Primeiro->num, origin->ocrs.size);

    return new;
}

void restoreWord(word_t **elem, word_t *backup){
	if((*elem)->fill == NULL){
		*elem = backup;
	}
}

//Função lê o arquivo retornando as palavras
//Fecha o arquivo e retorna NULL quando não houverem
//mais palavras a serem lidas
word_t *word_from_file(FILE *__file, int *pos){
    char word[TAMPAL] = {"\0"}; 
    if(read_word(__file, word, pos)){
        return new_word(word);
    }else{
        close_file(__file);
        return NULL;
    }
}

int compare_words(word_t *w1, word_t *w2){
    if((w1 == NULL) || (w2 == NULL)){
        printf("Palavra inválida na funçao compare_words!\n");
        exit(1);
    }
    else{
        return strcasecmp(w1->fill, w2->fill); // < 0 se w1 < w2
    }                                          // = 0 se w1 == w2
                                               // > 0 se w1 > w2
}

void print_word(word_t *obj){
    if(obj != NULL){
        printf("%s\n", obj->fill);
    }
}

void print_word_full(word_t *obj){
    if(obj != NULL){
        printf("%s\n", obj->fill);
        printFileList(&obj->ocrs);
    }
}

word_t *free_word(word_t *obj){
    if(obj != NULL){
        if(obj->fill != NULL){}
            free(obj->fill);
        free(obj);
        obj = NULL;
    }
    return obj;
}

void setOcrWord(word_t *obj, const char *path, int pos, int size){ 
    obj->ocrs = newFileList(size);
    filelist_t *list = &obj->ocrs;
    file_t new;
    new.path = path;
    emptiesIntList(&new.pos);
    InsertIntList(&new.pos, pos);
    InsertFileList(list, &new);
}

char *convertWordLower(word_t *word){
    int length = strlen(word->fill);
    char *string = malloc(sizeof(char) * length);
    for(int i = 0; i<length; i++){
        string[i] = tolower(word->fill[i]);
    }

    return string;
}
