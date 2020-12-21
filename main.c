#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define SIZE 4096

int main(int argc, char** argv){
	
	/*	---	DECLARATIONS	---	*/

	int frames, q, max, i, j, t;
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
	hashtable** ht = (hashtable**)malloc(20*sizeof(hashtable*));
	for(i = 0; i < 20; i++){
		ht[i] = (hashtable*)malloc(sizeof(hashtable));
	}

	t = 0;				// time
	i = 0;				// counter for max 

	pno = malloc(5);								// first 5 characters are the page number

	while(i < max){
		j = 0;				// counter for switching between files

		while(j < q){
			if(i == max)
				break;
			if((read = getline(&line, &len, fileA)) != -1){					//line by line in bzip.trace
				
				token = strtok(line, " \n");									//word by word

				// memory address
				strncpy(pno, token, 5);
				printf("%d bzip %d : %s\n",  i, j, pno);
				token = strtok(NULL, " \n");
				// R or W

				j++;
				i++;
			}
		}
		if(i == max)
			break;

		j = 0;				// counter for switching between files
		
		while(j < q){
			if(i == max)
				break;
			if((read = getline(&line, &len, fileB)) != -1){					//line by line in gcc.trace
				
				token = strtok(line, " \n");									//word by word

				// memory address
				strncpy(pno, token, 5);
				printf("%d gcc %d : %s\n",  i, j, pno);
				token = strtok(NULL, " \n");
				// R or W

				j++;
				i++;
			}
		}
		if(i == max)
			break;

		if(!(strcmp(alg, "LRU"))){


		}else{
			printf("2nd chance\n");
		}
	}

	//print stats
	printf("\nTotal writes: %d\n", writes);
	printf("Total reads: %d\n", reads);
	printf("Total faults: %d\n", faults);
	printf("Total hits: %d\n", hits);
	printf("Frames: %d\n", frames);

	return 0;
	
}