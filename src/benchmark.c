#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/file.h"
#include "include/word.h"
#include "include/word_list.h"
#include "include/tree.h"
#include "include/AVL.h"
#include "include/trie.h"
#include "include/hash_table.h"
#include "include/benchmark.h"

typedef struct {
	double insTime;
	int noSearchs;
	double searchTime;
} outTime;

outTime zeroFillOutTime(int nSearch){
	outTime new;
	new.insTime = new.searchTime = 0;
	new.noSearchs = nSearch;

	return new;
}

void printOutTime(outTime elem){
	printf("Inserção, N, Busca\n");
	printf("%f, %d, %f\n", elem.insTime, elem.noSearchs, elem.searchTime);
}

outTime useListb(char const *argv[], int nSearch, int size, word_t ** words){
	wordlist_t list;
	outTime tList = zeroFillOutTime(nSearch);
	clock_t t;

	emptiesWordList(&list);

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		FILE *text = open_read_file(path);
		word_t *tempWord;
		
		int pos;
		
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);

			t = clock();
			InsertWordList(tempWord, &list);
			t = clock() - t; 
			tList.insTime += ((double)t)/CLOCKS_PER_SEC;
		}
	}
	
	word_t *elem = NULL;
	for(int i = 0; i<nSearch; i++){
		elem = words[i];

		t = clock();
		searchWordInList(&list, elem);
		t = clock() - t; 
		tList.searchTime += ((double)t)/CLOCKS_PER_SEC;
	}
	
	freeWordList(&list);
	return tList;
}

outTime useTreeb(char const *argv[], int nSearch, int size, word_t ** words){ //busca bugada
	ArvBin *tree = new_bTree();
	outTime tTree = zeroFillOutTime(nSearch);
	clock_t t;
	
	for(int i = 1; i<=size; i++){
		const char* path = argv[i];
		FILE *text = open_read_file(path);
		word_t *tempWord;

		int pos;
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);
			t = clock();
			insert_bTree(tree, tempWord);
			t = clock() - t; 
			tTree.insTime += ((double)t)/CLOCKS_PER_SEC;
		}
	}

	word_t *elem = NULL;
	for(int i = 0; i<nSearch; i++){
		elem = words[i];

		t = clock();
		searchword_bTree(tree, elem);
		t = clock() - t; 
		tTree.searchTime += ((double)t)/CLOCKS_PER_SEC;

	}

	free_bTree(tree);
	return tTree;
}

outTime useAVLb(char const *argv[], int nSearch, int size, word_t ** words){
	ArvAVL *avl = new_AVL();
	outTime tAVL = zeroFillOutTime(nSearch);
	clock_t t;

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		FILE *text = open_read_file(path);
		word_t *w;

		int pos;
		while((w = word_from_file(text, &pos)) != NULL){
			setOcrWord(w, path, pos, size);

			t = clock();
			insert_AVL(avl, w);
			t = clock() - t; 
			tAVL.insTime += ((double)t)/CLOCKS_PER_SEC;
		}
	}

	word_t *elem = NULL;
	for(int i = 0; i<nSearch; i++){
		elem = words[i];

		t = clock();
		searchWord_AVL(avl, elem);
		t = clock() - t; 
		tAVL.searchTime += ((double)t)/CLOCKS_PER_SEC;
	}

	free_AVL(avl);
	return tAVL;
}

outTime useTrieb(char const *argv[], int nSearch, int size, word_t ** words){
	nodet_t *trie = newNode();
	outTime tTrie = zeroFillOutTime(nSearch);
	clock_t t;

	for(int i = 1; i<=size; i++){
		const char *path = argv[i];
		FILE *text = open_read_file(path);
		word_t *w;

		int pos;
		while((w = word_from_file(text, &pos)) != NULL){
			setOcrWord(w, path, pos, size);

			t = clock();
			insertWordTrie(&trie, w);
			t = clock() - t; 
			tTrie.insTime += ((double)t)/CLOCKS_PER_SEC;
		}
	}

	word_t *elem = NULL;
	for(int i = 0; i<nSearch; i++){
		elem = words[i];

		t = clock();
		searchWordTrie(trie, elem);
		t = clock() - t; 
		tTrie.searchTime += ((double)t)/CLOCKS_PER_SEC;

	}
	
	freeTrie(trie);
	return tTrie;
}

outTime useHashTableb(char const *argv[], int nSearch, int size, word_t ** words){
	word_t *tempWord;
	int cWords = 0;
	outTime tHash = zeroFillOutTime(nSearch);
	clock_t t;

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
		FILE *text = open_read_file(path);
	
		int pos;
		while((tempWord = word_from_file(text, &pos)) != NULL){
			setOcrWord(tempWord, path, pos, size);

			t = clock();
			insertHashTable(hashTable, tempWord);
			t = clock() - t; 
			tHash.insTime += ((double)t)/CLOCKS_PER_SEC;
		}
	}
	word_t *elem = NULL;
	for(int i = 0; i<nSearch; i++){
		elem = words[i];

		t = clock();
		searchInHashTable(hashTable, elem);
		t = clock() - t; 
		tHash.searchTime += ((double)t)/CLOCKS_PER_SEC;
	}
	
	freeHashTable(hashTable);
	return tHash;
}

void avaliaDesempenho(char const *argv[], int nSearch, int size){
	word_t **aux = malloc(sizeof(word_t *) * nSearch);
	for(int i = 0; i<nSearch; i++){
		aux[i] = wordInput();
	}

	printf("=-=-=-=-=Lista Encadeada=-=-=-=-=\n");
	printOutTime(useListb(argv, nSearch, size, aux));

	printf("=-=-=-=-=Árvore Binária-=-=-=-=-=\n");
	printOutTime(useTreeb(argv, nSearch, size, aux));

	printf("=-=-=-=-=-=Árvore AVL-=-=-=-=-=-=\n");
	printOutTime(useAVLb(argv, nSearch, size, aux));

	printf("=-=-=-=-Árvore Prefixada=-=-=-=-=\n");
	printOutTime(useTrieb(argv, nSearch, size, aux));

	printf("=-=-=-=-=-=Tabela Hash=-=-=-=-=-=\n");
	printOutTime(useHashTableb(argv, nSearch, size, aux));

	for(int i = 0; i<nSearch; i++){
		free_word(aux[i]);
	}
	free(aux);
}
