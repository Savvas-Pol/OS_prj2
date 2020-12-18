#ifndef HASHTABLE_H__
#define	HASHTABLE_H__


typedef struct hashtable{

	char* process;		//process name
	int pno;			//page number
	int t;				//time of insertion
	int fno;			//frame number
	struct hashtable* next;	//pointer to next bucket node

}hashtable;



#endif