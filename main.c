#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define SIZE 4096

int main(int argc, char** argv){
	
	/*	---	DECLARATIONS	---	*/

	int frames, q, max;
	int reads = 0, writes = 0, faults = 0, hits = 0;

	char* alg, *token, *pno;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	FILE *fileA, *fileB;

	/*	------------	*/

	//	get command line arguments
	if(argc == 5){
		alg = malloc(strlen(argv[1]));
		strcpy(alg, argv[1]);
		frames = atoi(argv[2]);
		q = atoi(argv[3]);
		max = atoi(argv[4]);
	}
	else{
		printf("Wrong arguments!!!\n");
		return -1;
	}

	//	open files
	if(!(fileA = fopen("bzip.trace", "r"))){
		printf("Error in opening bzip.trace\n");
		return -1;
	}
	if(!(fileB = fopen("gcc.trace", "r"))){
		printf("Error in opening gcc.trace\n");
		return -1;
	}

	//create hashtable


	pno = malloc(5);								// first 5 characters are page number
	//read files
	while ((read = getline(&line, &len, fileA)) != -1){					//line by line in bzip.trace
		token = strtok(line, " \n");									//word by word

		// memory address
		strncpy(pno, token, 5);
		
		token = strtok(NULL, " \n");
		// R or W
	}

	if(!(strcmp(alg, "LRU"))){


	}else{
		printf("2nd chance\n");
	}

	return 0;
	
}