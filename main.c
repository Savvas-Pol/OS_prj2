#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

#define SIZE 4096
#define HASHNODES 100

// ./main LRU 10 100 10000

int main(int argc, char** argv){
	
	/*	---	DECLARATIONS	---	*/

	int frames, q, max, i, j, t, count, pos, pos2, process, min;
	int reads = 0, writes = 0, faults = 0, hits = 0;

	char* alg, *token, *pno;
	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	Node* node, *min_t;

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
	Node** ht = (Node**)malloc(HASHNODES*sizeof(Node*));
	for(i = 0; i < HASHNODES; i++){
		ht[i] = NULL;
	}

	t = 0;			// time
	i = 0;			// counter for max 
	count = 0;		// counter for frames

	pno = (char*)malloc(6);		// first 5 characters are the page number

	while(i < max){
		j = 0;	// counter for switching between files
		while(j < q){
			process = 0;	//bzip
			if(i == max)
				break;

			if((read = getline(&line, &len, fileA)) != -1){	//line by line in bzip.trace
				token = strtok(line, " \n");	//word by word

				// memory address
				strncpy(pno, token, 5);

				// R or W
				token = strtok(NULL, " \n");
				
				pos = hash_function(pno, HASHNODES);
				if(!(node = hash_search(ht, pos, pno, process))){	//search if already exists
					faults++;
					reads++;

					if(count < frames){		// check if there is enough memory
						hash_insert(ht, pos, pno, t, process, token);	// insert at the end of current bucket
						count++;
					}
					else{	//page replacement
						min_t = search_min(ht, HASHNODES);

						if(min_t->dirty == 1)
							writes++;

						if(!strcmp(alg, "LRU")){	//LRU
							page_replacement(min_t, HASHNODES, pos, process, pno, t, token, ht);
						}
						else{	//2nd chance
							if((min_t->referenced == 1) && (min_t->flag == 0)){
								min_t->referenced = 0;
								min_t->flag = 1;
								min_t->t = t;				//give 2nd chance
							}
							else{
								page_replacement(min_t, HASHNODES, pos, process, pno, t, token, ht);
							}
						}
					}
				}else{
					hits++;
					if (!strcmp(token, "W"))
						node->dirty = 1;

					if (!strcmp(alg, "LRU"))
						node->t = t;
					else		//2nd chance
						node->referenced = 1;
				}

				j++;
				i++;
				t++;
			}
		}
		if(i == max)
			break;

		j = 0;		// counter for switching between files

		while(j < q){
			process = 1;	//gcc
			if(i == max)
				break;

			if((read = getline(&line, &len, fileB)) != -1){		//line by line in gcc.trace
				token = strtok(line, " \n");	//word by word

				// memory address
				strncpy(pno, token, 5);
				
				// R or W
				token = strtok(NULL, " \n");

				pos = hash_function(pno, HASHNODES);
				if(!(node = hash_search(ht, pos, pno, process))){	//search if already exists
					faults++;
					reads++;

					if(count < frames){		// check if there is enough memory
						hash_insert(ht, pos, pno, t, process, token);	// insert at the end of current bucket
						count++;
					}
					else{	//page replacement
						min_t = search_min(ht, HASHNODES);
						if(min_t->dirty == 1)
							writes++;

						if(!strcmp(alg, "LRU")){	//LRU
							page_replacement(min_t, HASHNODES, pos, process, pno, t, token, ht);
						}
						else{	//2nd chance
							if((min_t->referenced == 1) && (min_t->flag == 0)){
								min_t->referenced = 0;
								min_t->flag = 1;
								min_t->t = t;				//give 2nd chance
							}
							else{
								page_replacement(min_t, HASHNODES, pos, process, pno, t, token, ht);
							}
						}
					}
				}else{
					hits++;
					if (!strcmp(token, "W"))
						node->dirty = 1;

					if (!strcmp(alg, "LRU"))
						node->t = t;
					else		//2nd chance
						node->referenced = 1;
				}

				j++;
				i++;
				t++;
			}
		}
		if(i == max)
			break;
	}

	//print stats
	printf("STATISTICS FOR %s\n", alg);
	printf("\nTotal writes: %d\n", writes);
	printf("Total reads: %d\n", reads);
	printf("Total faults: %d\n", faults);
	printf("Total hits: %d\n", hits);
	printf("\nTotal entries checked: %d\n", max);
	printf("Frames: %d\n", frames);

	return 0;
	
}