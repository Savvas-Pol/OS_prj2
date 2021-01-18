#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

int hash_function(unsigned char *str, int buckets){

    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % buckets;
}

Node* hash_search(Node** ht, int pos, char* pno, int process){	// search node with this pno and process

	Node* temp = ht[pos];

	while(temp != NULL){
		if(!strcmp(temp->pno, pno)){
			if(temp->process == process)
				return temp;
		}
		temp = temp->next;
	}
	return temp;
}

void hash_insert(Node** ht, int pos, char* pno, int t, int process, char * token){	// insert in hashtable

	Node* new;
	Node* temp = ht[pos];

	new = (Node*)malloc(sizeof(Node));

	new->process = process;
	new->pno = (char*)malloc(strlen(pno));
	strcpy(new->pno, pno);
	new->t = t;
	new->referenced = 0;
	new->flag = 0;
	new->next = NULL;

	if(!strcmp(token, "W"))
		new->dirty = 1;
	else
		new->dirty = 0;

	if(ht[pos] == NULL)
		ht[pos] = new;
	else{
		while(temp != NULL){
			if(temp->next == NULL){
				temp->next = new;
				return;
			}
			else
				temp = temp->next;
		}
	}

}

void hash_delete(Node** ht, int pos, char* pno, int process){

	Node* temp = ht[pos], *temp2;
	int first = 1;					// flag to check if we are in first node

	while(temp != NULL){
		if(!strcmp(temp->pno, pno)){
			if(temp->process == process){
				if(first)
					ht[pos] = temp->next;
				else
					temp2->next = temp->next;

				free(temp->pno);
				free(temp);
				return;
			}
		}
		temp2 = temp;
		temp = temp->next;
		first = 0;
	}
}

Node* search_min(Node** ht, int buckets){	// search node with min t in hashtable

	int i, min = 2147483647;	//max int value

	Node* min_t, *temp;

	for(i = 0; i < buckets; i++){
		temp = ht[i];

		while(temp != NULL){
			if(temp->t < min){
				min = temp->t;
				min_t = temp;
			}
			temp = temp->next;
		}
	}
	return min_t;
}