#ifndef HASHTABLE_H__
#define	HASHTABLE_H__

typedef struct Node{

	int process;		//0 for bzip, 1 for gcc 
	char* pno;			//page number
	int t;				//time of insertion
	int dirty;
	int referenced;
	int flag;			//flag to check if current entry is given a 2nd chance
	struct Node* next;	//pointer to next bucket node

}Node;

int hash_function(unsigned char *str, int buckets);

Node* hash_search(Node** ht, int pos, char* pno, int process);
void hash_insert(Node** ht, int pos, char* pno, int t, int process, char * token);
void hash_delete(Node** ht, int pos, char* pno, int process);

Node* search_min(Node** ht, int buckets);

#endif