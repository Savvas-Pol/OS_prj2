#ifndef HASHTABLE_H__
#define	HASHTABLE_H__


typedef struct node{

	int process;		//0 for bzip, 1 for gcc 
	char* pno;			//page number
	int t;				//time of insertion
	// int fno;			//frame number
	int referenced;
	struct node* next;	//pointer to next bucket node

}node;

int hash_function(unsigned char *str, int buckets);

int hash_search(node** ht, int pos, char* pno, int process);
void hash_insert(node** ht, int pos, char* pno, int t, int process);

node* search_min(node** ht, int buckets);

#endif