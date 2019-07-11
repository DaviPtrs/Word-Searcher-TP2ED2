#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "include/word.h"
#include "include/word_list.h"
#include "include/hash_table.h"

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length){
    size_t i = 0;
    uint32_t hash = 0;
    while(i != length){
        hash += key[i++];
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

uint32_t hash_word(word_t *word){
    if(word != NULL){
        int length = strlen(word->fill);
        char *string = convertWordLower(word);
        uint32_t hash = jenkins_one_at_a_time_hash((uint8_t *)string, length);
        free(string);
        return hash;
    }
    printf("Palavra inválida na função hash_word");
    exit(1);
}

hash_t *newHashTable(int size){
    hash_t *new;
    new = malloc(sizeof(hash_t));
    new->table = malloc(sizeof(wordlist_t) * size);
    new->size = size;

    for(int i = 0; i<size; i++){
        emptiesWordList(&new->table[i]);
    }
    return new;
}

int getHashTableIndex(word_t *item, int size){
    if((item != NULL) && (size > 0)){
        uint32_t hash = hash_word(item);
        int index = ((unsigned) hash) % size;
        return index;
    }else{
        return -1;
    }
}

wordlist_t *getHashTablePos(hash_t *hashTable, word_t *item){
    if((hashTable != NULL) && (item != NULL)){
        int index = getHashTableIndex(item, hashTable->size);
        wordlist_t *pos = &hashTable->table[index];
        return pos;
    }else{
        printf("Tabela e/ou items NULOS na função getHashTablePos!\n");
        return NULL;
    }
}

void insertHashTable(hash_t *hashTable, word_t *item){
    if((hashTable != NULL) && (item != NULL)){
        wordlist_t *pos = getHashTablePos(hashTable, item);
        InsertWordList(item, pos);
    }else{
        printf("Tabela e/ou items NULOS na função insertHashTable!\n");
    }
}

word_t *searchInHashTable(hash_t *hashTable, word_t *item){
    if((hashTable != NULL) && (item != NULL)){
        wordlist_t *pos = getHashTablePos(hashTable, item);
        return searchWordInList(pos, item);
    }else{
        printf("Tabela e/ou items NULOS na função searchHashTable!\n");
        return NULL;
    }
}

void freeHashTable(hash_t *hashTable){
    if(hashTable != NULL){
        int size = hashTable->size;
        for(int i = 0; i<size; i++){
            freeWordList(&hashTable->table[i]);
        }
        free(hashTable->table);
        free(hashTable);
    }
}

void printHashTable(hash_t *hashTable){
    if(hashTable != NULL){
        int size = hashTable->size;
        for(int i = 0; i<size; i++){
            if(!emptyWordList(&hashTable->table[i])){
                printf(">>>>>>>>Pos %d<<<<<<<<\n", i);
                printWordListFull(&hashTable->table[i]);
            }
        }
    }
}

int emptyHashTable(hash_t *hashTable){
    if(hashTable != NULL){
        int size = hashTable->size;
        for(int i = 0; i<size; i++){
            if(!emptyWordList(&hashTable->table[i])){
                return 0;
            }
        }
        return 1;
    }else{
        return -1;
    }
}

float conflictRate(hash_t *hashTable){
    if((hashTable != NULL) && !emptyHashTable(hashTable)){
        int size = hashTable->size;
        int wCount = 0;
        int cCount = 0;
        for(int i = 0; i<size; i++){
            wordlist_t *pos = &hashTable->table[i];
            int c = sizeWordList(pos);
            wCount += c;
            if(c > 1)
                cCount += (c-1);
        }
        printf("\nTamanho da tabela: %d\n", size);
        printf("Total de palavras %d\n", wCount);
        printf("Total de conflitos %d\n", cCount);
        float res = ((float)cCount / (float)wCount) * 100;
        return res;
    }else{
        return -1;
    }
}

int defHashTableSize(int num){
	//Retorna o primeiro número, de base 2, maior do que size
	for(int i = 1; ; i *= 2){
		if(i>num){
			return i;
		}
	}
}
