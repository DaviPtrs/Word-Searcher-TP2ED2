#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "include/output.h"
#include "include/benchmark.h"

int main(int argc, char const *argv[]){
	if(argc < 3){
		instructions();
		return 1;
	}
	int nFile = 0;
	for(int i = 1; i<argc; i++){
		if(!isdigit(argv[i][0])){
			nFile++;
		}
	}
	
	int opc = atoi(argv[nFile+1]);
	int flag = 0;
	if(argc == (nFile + 3))
		flag = atoi(argv[nFile + 2]);

	switch (opc){
	case 0:
		useList(argv, flag, nFile);
		break;
	case 1:
		useTree(argv, flag, nFile);
		break;
	case 2:
		useAVL(argv, flag, nFile);
		break;
	case 3:
		useTrie(argv, flag, nFile);
		break;
	case 4:
		useHashTable(argv, flag, nFile);
		break;
	case 5:
		avaliaDesempenho(argv, flag, nFile);
		break;
	default:
		instructions();
		return 1;
		break;
	}
	
	return 0;
}
