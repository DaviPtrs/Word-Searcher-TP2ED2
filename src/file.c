#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/file.h"
#define TAMPAL 80

void close_file(FILE *__file){
    if(__file != NULL){
        fclose(__file);
    }
}

FILE *open_read_file(const char *path){
    if (path == NULL){
        printf("Função open_file precisa de um caminho válido!\n");
        exit(1);
    }
    FILE *__file;
    if((__file = fopen(path, "r")) == NULL){
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }
    return __file;
}

int countWordsInFile(FILE *__file){
    char c;
    int i = 1;
    int flag = 0;
    while((c = fgetc(__file)) != EOF){
        if((flag == 1) && isalpha(c)){
            i++;
            flag = 0;
        }
        if(!isalpha(c))
            flag = 1;
    }
    i++;
    rewind(__file);
    return i;

}

int read_word(FILE *__file, char *word, int *pos){
    char c;
    int szWrd = TAMPAL - 1;

    while((c = fgetc(__file)) != EOF){
        if(isalpha(c))
            break;
    }

    if(c == EOF){
        return 0;
    }
    else{
        *pos = ftell(__file);
        word[0] = c;
    }
    
    for(int i = 1; i<szWrd; i++){
        if(((c = fgetc(__file)) != EOF) && isalpha(c)){
            word[i] = c;
        }else{
            word[i] = '\0';
            break;
        }
    }

    return 1; 
}

