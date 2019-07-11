#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/file_list.h"

filelist_t newFileList(int size){
	filelist_t new;
	new.files = malloc(sizeof(file_t) * size);
	new.size = size;
	emptiesFileList(&new);

	return new;
}

void emptiesFileList(filelist_t *list){
	if(list != NULL){
		list->ini = list->end = -1;
	}
}

int isEmptyFileList(filelist_t *list){
	return ((list->ini == -1) && (list->end == -1));
}

file_t *searchFileInList(filelist_t *list, file_t *item){
	for(int i = list->ini; i<=list->end; i++){
		file_t *elem = &list->files[i];
		if(!strcmp(elem->path, item->path)){
			return elem;
		}
	}
	return NULL;
}

void InsertFileList(filelist_t *list, file_t *item){
	if(isEmptyFileList(list)){ 
		list->ini++;
		list->end++;
		list->files[0] = *item;
	}else{
		if((list->end + 1) == list->size){
			printf("Lista de arquivos cheia!");
		}else{
			list->end++;
			list->files[list->end] = *item;
		}
	}
}

void printFileList(filelist_t *list){
	if(!isEmptyFileList(list)){
		for(int i = list->ini; i<=list->end; i++){
			printf("%s ", list->files[i].path);
			printIntList(&(list->files[i]).pos);
			printf("\n");
		}
	}
}

int sizeFileList(filelist_t *list){
	return (list->end - list->ini + 1);
}

void freeFileList(filelist_t *list){
	if(list != NULL){
		if(list->files != NULL){
			for(int i = list->ini; i<=list->end; i++){
				if(list->files[i].pos.Primeiro != NULL){
					freeIntList(&list->files[i].pos);
				}
			}
			list->files->path = NULL;
			free(list->files);
			list->files = NULL;
		}
	}
}
