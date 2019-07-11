#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/file.h"
#include "include/word.h"
#include "include/word_list.h"
#include "include/tree.h"
#include "include/AVL.h"
#include "include/hash_table.h"
#include "include/trie.h"
#include "../include/output.h"

void instructions(){
	system("cat instructions.txt");
}

void useList(char const *argv[], int nSearch, int size){
	wordlist_t list;

	emptiesWordList(&list);

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		printf("Abrindo arquivo %s\n", path);
		FILE *text = open_read_file(path);
		word_t *tempWord;

		printf("Inserindo elementos...\n");
		
		int pos;
		
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);
			InsertWordList(tempWord, &list);
		}
	}
	
	word_t *elem = NULL;
	word_t *result = NULL;

	if(nSearch > 0){
		for(int i = 0; i<nSearch; i++){
			printf("Pesquisar > ");
			elem = wordInput();
			result = searchWordInList(&list, elem);
			if(result == NULL){
				printf("Palavra %s não encontrada!\n", elem->fill);
			}else{
				printf("\n");
				print_word_full(result);
			}
			free_word(elem);
		}
	}else{
		printWordListFull(&list);//printa o resultado da lista
	}
	freeWordList(&list);
}

void useTree(char const *argv[], int nSearch, int size){ //busca bugada
	ArvBin *tree = new_bTree();
	
	for(int i = 1; i<=size; i++){
		const char* path = argv[i];
		printf("Abrindo arquivo %s\n", path);
		FILE *text = open_read_file(path);
		printf("Inserindo elementos...\n");
		word_t *tempWord;

		int pos;
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);
			insert_bTree(tree, tempWord);
		}
	}

	word_t *elem = NULL;
	word_t *result = NULL;

	if(nSearch > 0){
		for(int i = 0; i<nSearch; i++){
			printf("Pesquisar > ");
			elem = wordInput();
			result = searchword_bTree(tree, elem);
			if(result == NULL){
				printf("Palavra %s não encontrada!\n", elem->fill);
			}else{
				printf("\n");
				print_word_full(result);
			}
			free_word(elem);
		}
	}else{
		print_preOrderbTree(tree);//printa o resultado da árvore
	}

	free_bTree(tree);
}

void useAVL(char const *argv[], int nSearch, int size){
	ArvAVL *avl = new_AVL();

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		printf("Abrindo arquivo %s\n", path);
		FILE *text = open_read_file(path);
		word_t *w;

		printf("Inserindo elementos...\n");
		int pos;
		while((w = word_from_file(text, &pos)) != NULL){
			setOcrWord(w, path, pos, size);		
			insert_AVL(avl, w);			
		}
	}

	word_t *elem = NULL;
	word_t *result = NULL;

	if(nSearch > 0){
		for(int i = 0; i<nSearch; i++){
			printf("Pesquisar > ");
			elem = wordInput();			
			result = searchWord_AVL(avl, elem);
			if(result == NULL){
				printf("Palavra %s não encontrada!\n", elem->fill);
			}else{
				printf("\n");
				print_word_full(result);
			}
			free_word(elem);
		}
	}else{
		print_preOrderAVL(avl);//printa o resultado da árvore
	}

	free_AVL(avl);

}

void useTrie(char const *argv[], int nSearch, int size){
	nodet_t *trie = newNode();

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		printf("Abrindo arquivo %s\n", path);
		FILE *text = open_read_file(path);
		word_t *w;

		printf("Inserindo elementos...\n");
		int pos;
		while((w = word_from_file(text, &pos)) != NULL){
			setOcrWord(w, path, pos, size);
			insertWordTrie(&trie, w);
		}
	}

	word_t *elem = NULL;
	word_t *result = NULL;

	if(nSearch > 0){
		for(int i = 0; i<nSearch; i++){
			printf("Pesquisar > ");
			elem = wordInput();
			result = searchWordTrie(trie, elem);
			if(result == NULL){
				printf("Palavra %s não encontrada!\n", elem->fill);
			}else{
				printf("\n");
				print_word_full(result);
			}
			free_word(elem);
		}
	}else{
		printTrie(trie);
	}

	freeTrie(trie);
}

void useHashTable(char const *argv[], int nSearch, int size){
	word_t *tempWord;
	int cWords = 0;

	printf("Criando tabela hash...\n");
	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		FILE *text = open_read_file(path);
		cWords += countWordsInFile(text);
		close_file(text);
	}

	int sizeTable = defHashTableSize(cWords);
	hash_t *hashTable = newHashTable(sizeTable);

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		printf("Abrindo arquivo %s\n", path);
		FILE *text = open_read_file(path);
	
		printf("Inserindo elementos...\n");
		int pos;
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);
			insertHashTable(hashTable, tempWord);
		}
	}
	word_t *elem = NULL;
	word_t *result = NULL;

	if(nSearch > 0){
		for(int i = 0; i<nSearch; i++){
			printf("Pesquisar > ");
			elem = wordInput();
			result = searchInHashTable(hashTable, elem);
			if(result == NULL){
				printf("Palavra %s não encontrada!\n", elem->fill);
			}else{
				printf("\n");
				print_word_full(result);
			}
			free_word(elem);
		}
	}else{
		printHashTable(hashTable);
		printf("\nA tabela teve %.2f de conflitos\n", conflictRate(hashTable));
	}

	freeHashTable(hashTable);
}
