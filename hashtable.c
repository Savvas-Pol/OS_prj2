#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int hash_function(unsigned char *str, int buckets){

    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash%buckets;
}

int hash_search(node** ht, int pos, char* pno, int process){

	int found = 0;
	node* temp = ht[pos];

	while(temp != NULL && found == 0){
		if(!strcmp(temp->pno, pno)){
			if(temp->process == process)
				found = 1;
		}
		temp = temp->next;
	}
	// if(found == 0)
	// 	printf("%s NOT FOUND pos:%d\n", pno, pos);
	// else
	// 	printf("%s FOUND pos:%d\n", pno, pos);

	return found;
}

void hash_insert(node**ht, int pos, char* pno, int t, int process){

	node* new;
	node* temp = ht[pos];

	new = (node*)malloc(sizeof(node));

	new->process = process;
	new->pno = malloc(strlen(pno));
	strcpy(new->pno, pno);
	new->t = t;
	new->referenced = 0;
	new->next = NULL;

	if(ht[pos] == NULL)
		ht[pos] = new;
	else{
		while(temp != NULL){
			if(temp->next == NULL){
				temp->next = new;
				break;
			}
			else
				temp = temp->next;
		}
	}

}