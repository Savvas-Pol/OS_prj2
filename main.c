#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int main(int argc, char** argv){
	
	/*	---	DECLARATIONS	---	*/

	int frames, q, max;
	int reads = 0, writes = 0, faults = 0, hits = 0;
	char* alg;

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



	return 0;
	
}