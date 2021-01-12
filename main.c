#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define SIZE 4096
#define HASHNODES 20

int main(int argc, char** argv){
	
	/*	---	DECLARATIONS	---	*/

	int frames, q, max, i, j, t, count, pos, process, min;
	int reads = 0, writes = 0, faults = 0, hits = 0;

	char* alg, *token, *pno;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	node* min_t;

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
	node** ht = (node**)malloc(HASHNODES*sizeof(node*));
	for(i = 0; i < HASHNODES; i++){
		ht[i] = (node*)malloc(sizeof(node));
		ht[i] = NULL;
	}

	t = 0;				// time
	i = 0;				// counter for max 
	count = 0;			// counter for frames

	pno = malloc(5);								// first 5 characters are the page number

	while(i < max){
		j = 0;				// counter for switching between files

		while(j < q){
			process = 0;			//bzip
			if(i == max)
				break;
			if((read = getline(&line, &len, fileA)) != -1){					//line by line in bzip.trace
				
				token = strtok(line, " \n");									//word by word

				// memory address
				strncpy(pno, token, 5);

				token = strtok(NULL, " \n");
				// R or W

				pos = hash_function(pno, HASHNODES);
				if(!hash_search(ht, pos, pno, process)){		//search if already exists
					faults++;
					if(!strcmp(token, "W")){
						if(count < frames){
							hash_insert(ht, pos, pno, t, process);		// insert at the end of current bucket
							count++;
							printf("Count: %d\n", count);
						}
						else{			//page replacement
							if(!strcmp(alg, "LRU")){	//LRU

								writes++;
								min_t = search_min(ht, HASHNODES);

								min_t->process = process;
								strcpy(min_t->pno, pno);
								min_t->t = t;
								min_t->referenced = 0;
							}
							// else{						//2nd chance

							// }
						}
					}
				}else
					hits++;

				j++;
				i++;
				t++;
			}
		}
		if(i == max)
			break;

		j = 0;				// counter for switching between files

		while(j < q){
			process = 1;			//gcc
			if(i == max)
				break;
			if((read = getline(&line, &len, fileB)) != -1){					//line by line in gcc.trace
				
				token = strtok(line, " \n");									//word by word

				// memory address
				strncpy(pno, token, 5);
				// printf("%d gcc %d : %s ",  i, j, pno);
				token = strtok(NULL, " \n");
				// R or W
				// printf("%s \n",  token);
				j++;
				i++;
				t++;
			}
		}
		if(i == max)
			break;
	}

	// printf("%d\n", min);
	// node* temp;
	// for(i = 0; i < HASHNODES; i++){
	// 	temp = ht[i];
	// 	if(temp == NULL)
	// 		printf("ht[%d] is NULL\n", i);
	// 	while(temp != NULL){
	// 		printf("ht[%d] pno: %s t = %d\n",i, temp->pno, temp->t);
	// 		temp = temp->next;
	// 	}
	// }

	//print stats
	printf("\nTotal writes: %d\n", writes);
	printf("Total reads: %d\n", reads);
	printf("Total faults: %d\n", faults);
	printf("Total hits: %d\n", hits);
	printf("Frames: %d\n", frames);

	return 0;
	
}